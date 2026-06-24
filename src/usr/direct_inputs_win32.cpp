// direct_inputs_win32.cpp
#include "direct_inputs.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include <string>

// Map your keysym constants to Windows VK codes
static UINT keysymToVK(unsigned int keysym)
{
    switch(keysym)
    {
        case 0x0077: return 'W';           // KEY_w
        case 0x0061: return 'A';           // KEY_a
        case 0x0073: return 'S';           // KEY_s
        case 0x0064: return 'D';           // KEY_d
        case 0xFF52: return VK_UP;         // KEY_UP
        case 0xFF54: return VK_DOWN;       // KEY_DOWN
        case 0xFF51: return VK_LEFT;       // KEY_LEFT
        case 0xFF53: return VK_RIGHT;      // KEY_RIGHT
        case 0x0020: return VK_SPACE;      // KEY_SPACE
        case 0xFF1B: return VK_ESCAPE;     // KEY_ESCAPE
        case 0xFFE9: return VK_LMENU;     // KEY_ALT_L
        case 0xFFEA: return VK_RMENU;     // KEY_ALT_R
        case 0xFF50: return VK_HOME;       // KEY_HOME
        case 0xFF57: return VK_END;        // KEY_END
        case 0xFF0D: return VK_RETURN;     // KEY_RETURN
        case 0xFFBE: return VK_F1;         // KEY_F1
        case 0xFFC0: return VK_F3;         // KEY_F3
        default:     return 0;
    }
}

static HWND g_clickedWindow = nullptr;
static HHOOK g_mouseHook = nullptr;

static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode >= 0 && wParam == WM_LBUTTONDOWN)
    {
        auto* ms = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
        g_clickedWindow = WindowFromPoint(ms->pt);
        PostQuitMessage(0);
        return 1; // eat the click
    }
    // Re-apply crosshair on every move so target windows can't reset it via WM_SETCURSOR
    if(nCode >= 0 && wParam == WM_MOUSEMOVE)
        SetCursor(LoadCursor(nullptr, IDC_CROSS));
    return CallNextHookEx(g_mouseHook, nCode, wParam, lParam);
}

namespace dir_inp
{
    long get_window_via_click()
    {
        Sleep(300); // same delay as the X11 version

        // Show a crosshair so the user knows to click a target window
        HCURSOR oldCursor = SetCursor(LoadCursor(nullptr, IDC_CROSS));

        g_clickedWindow = nullptr;
        g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, nullptr, 0);
        if(!g_mouseHook)
        {
            SetCursor(oldCursor);
            return 0;
        }

        MSG msg;
        while(GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        UnhookWindowsHookEx(g_mouseHook);
        g_mouseHook = nullptr;
        SetCursor(oldCursor); // restore whatever was set before

        return reinterpret_cast<long>(g_clickedWindow);
    }

    void send_key_to_window(long window_id, unsigned int key, bool press)
    {
        HWND hwnd = reinterpret_cast<HWND>(window_id);
        UINT vk = keysymToVK(key);
        if(!vk) return;

        UINT msg = press ? WM_KEYDOWN : WM_KEYUP;
        LPARAM lParam = (MapVirtualKey(vk, MAPVK_VK_TO_VSC) << 16) | 1;
        if(!press)
            lParam |= (1 << 30) | (1 << 31); // previous key state + transition

        PostMessage(hwnd, msg, vk, lParam);
    }

    void send_mouse_click(long window_id, int x, int y, unsigned int button, bool press)
    {
        HWND hwnd = reinterpret_cast<HWND>(window_id);
        UINT msg;
        WPARAM wParam = 0;

        if(button == 1) // MOUSE_LEFT
            msg = press ? WM_LBUTTONDOWN : WM_LBUTTONUP;
        else if(button == 2) // MOUSE_MIDDLE
            msg = press ? WM_MBUTTONDOWN : WM_MBUTTONUP;
        else // MOUSE_RIGHT
            msg = press ? WM_RBUTTONDOWN : WM_RBUTTONUP;

        LPARAM lParam = MAKELPARAM(x, y);
        PostMessage(hwnd, msg, wParam, lParam);
    }

    void send_mouse_move(long, int, int) {}

    MousePos get_mouse_pos_in_window(long window_id)
    {
        HWND hwnd = reinterpret_cast<HWND>(window_id);
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);
        return {pt.x, pt.y};
    }

    bool is_key_pressed(unsigned int keysym)
    {
        UINT vk = keysymToVK(keysym);
        if(!vk) return false;
        return (GetAsyncKeyState(vk) & 0x8000) != 0;
    }

    std::vector<bool> poll_keys(const std::vector<unsigned int>& keysyms)
    {
        std::vector<bool> states(keysyms.size(), false);
        for(size_t i = 0; i < keysyms.size(); i++)
        {
            UINT vk = keysymToVK(keysyms[i]);
            if(vk)
                states[i] = (GetAsyncKeyState(vk) & 0x8000) != 0;
        }
        return states;
    }

    int get_pid_via_shell(const std::string&) { return 0; }
    int get_pid_from_window(long) { return 0; }
}
