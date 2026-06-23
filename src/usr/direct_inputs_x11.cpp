// direct_inputs.cpp
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "direct_inputs.hpp"

#include <array>
#include <memory>
#include <cstdio>
#include <string>

namespace dir_inp
{
    long get_window_via_click()
    {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(
            popen("sleep 0.3 && xdotool selectwindow 2>/dev/null", "r"), pclose);
        if (!pipe) return 0;
        if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            result = buffer.data();
        return result.empty() ? 0 : std::stol(result);
    }

    void send_key_to_window(long window_id, unsigned int key, bool press)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return;

        Window target = static_cast<Window>(window_id);

        XKeyEvent event = {};
        event.type        = press ? KeyPress : KeyRelease;
        event.display     = display;
        event.window      = target;
        event.root        = DefaultRootWindow(display);
        event.subwindow   = None;
        event.time        = CurrentTime;
        event.keycode     = XKeysymToKeycode(display, key);
        event.same_screen = True;

        XSendEvent(display, target, True,
                   press ? KeyPressMask : KeyReleaseMask,
                   reinterpret_cast<XEvent*>(&event));
        XFlush(display);
        XCloseDisplay(display);
    }

    void send_mouse_click(long window_id, int x, int y, unsigned int button, bool press)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return;

        Window target = static_cast<Window>(window_id);

        XButtonEvent event = {};
        event.type        = press ? ButtonPress : ButtonRelease;
        event.display     = display;
        event.window      = target;
        event.root        = DefaultRootWindow(display);
        event.subwindow   = None;
        event.time        = CurrentTime;
        event.x           = x;  // relative to target window
        event.y           = y;
        event.button      = button;
        event.same_screen = True;

        XSendEvent(display, target, True,
                   press ? ButtonPressMask : ButtonReleaseMask,
                   reinterpret_cast<XEvent*>(&event));
        XFlush(display);
        XCloseDisplay(display);
    }

    void send_mouse_move(long window_id, int x, int y)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return;

        Window target = static_cast<Window>(window_id);

        XMotionEvent event = {};
        event.type        = MotionNotify;
        event.display     = display;
        event.window      = target;
        event.root        = DefaultRootWindow(display);
        event.subwindow   = None;
        event.time        = CurrentTime;
        event.x           = x;
        event.y           = y;
        event.same_screen = True;

        XSendEvent(display, target, True, PointerMotionMask,
                   reinterpret_cast<XEvent*>(&event));
        XFlush(display);
        XCloseDisplay(display);
    }

    //local space get mouse coords
    MousePos get_mouse_pos_in_window(long window_id)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return {0, 0};

        Window target = static_cast<Window>(window_id);
        Window root_ret, child_ret;
        int root_x, root_y, win_x, win_y;
        unsigned int mask;

        XQueryPointer(display, target, &root_ret, &child_ret,
                      &root_x, &root_y, &win_x, &win_y, &mask);

        XCloseDisplay(display);
        return {win_x, win_y};
    }

    bool is_key_pressed(unsigned int keysym)
    {
        Display* display = XOpenDisplay(nullptr);
        if (!display) return false;

        KeyCode kc = XKeysymToKeycode(display, keysym);
        char keys[32];
        XQueryKeymap(display, keys);
        XCloseDisplay(display);

        return (keys[kc / 8] >> (kc % 8)) & 1;
    }

    std::vector<bool> poll_keys(const std::vector<unsigned int>& keysyms)
    {
        std::vector<bool> states(keysyms.size(), false);

        Display* display = XOpenDisplay(nullptr);
        if (!display) return states;

        char keys[32];
        XQueryKeymap(display, keys);

        for (size_t i = 0; i < keysyms.size(); i++)
        {
            KeyCode kc = XKeysymToKeycode(display, keysyms[i]);
            states[i] = (keys[kc / 8] >> (kc % 8)) & 1;
        }

        XCloseDisplay(display);
        return states;
    }
}
