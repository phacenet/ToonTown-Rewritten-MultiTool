// direct_inputs.hpp
#pragma once
#include <vector>
#include <string>

namespace dir_inp
{
    // key constants (mirrors X11 keysyms, avoids including Xlib.h in headers)
    constexpr unsigned int KEY_w = 0x0077;
    constexpr unsigned int KEY_a = 0x0061;
    constexpr unsigned int KEY_s = 0x0073;
    constexpr unsigned int KEY_d = 0x0064;
    constexpr unsigned int MOUSE_LEFT   = 1;
    constexpr unsigned int MOUSE_MIDDLE = 2;
    constexpr unsigned int MOUSE_RIGHT  = 3;
    constexpr unsigned int KEY_UP     = 0xFF52;
    constexpr unsigned int KEY_DOWN   = 0xFF54;
    constexpr unsigned int KEY_LEFT   = 0xFF51;
    constexpr unsigned int KEY_RIGHT  = 0xFF53;
    constexpr unsigned int KEY_SPACE  = 0x0020;
    constexpr unsigned int KEY_ESCAPE = 0xFF1B;
    constexpr unsigned int KEY_ALT_L  = 0xFFE9;
    constexpr unsigned int KEY_ALT_R  = 0xFFEA;
    constexpr unsigned int KEY_HOME = 0xFF50; //for gags
    constexpr unsigned int KEY_END  = 0xFF57; //for toontasks
    constexpr unsigned int KEY_RETURN = 0xFF0D;
    constexpr unsigned int KEY_F3 = 0xFFC0;
    constexpr unsigned int KEY_F1 = 0xFFBE;
    constexpr unsigned int KEY_DELETE = 0xFFFF;

    long get_window_via_click();
    void send_key_to_window(long window_id, unsigned int key, bool press);

    void send_mouse_click(long window_id, int x, int y, unsigned int button, bool press);
    void send_mouse_move(long window_id, int x, int y);
    bool is_key_pressed(unsigned int keysym);

    //for getting mouse coords in localspace
    struct MousePos { int x; int y; };
    MousePos get_mouse_pos_in_window(long window_id);

    std::vector<bool> poll_keys(const std::vector<unsigned int>& keysyms);
}
