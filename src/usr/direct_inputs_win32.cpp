#include "direct_inputs.hpp"

namespace dir_inp
{
    long get_window_via_click() { return 0; }
    int get_pid_from_window(long) { return 0; }
    int get_pid_via_shell(const std::string&) { return 0; }
    void send_key_to_window(long, unsigned int, bool) {}
    void send_mouse_click(long, int, int, unsigned int, bool) {}
    void send_mouse_move(long, int, int) {}
    MousePos get_mouse_pos_in_window(long) { return {0, 0}; }
    bool is_key_pressed(unsigned int) { return false; }
    std::vector<bool> poll_keys(const std::vector<unsigned int>& k) { return std::vector<bool>(k.size(), false); }
}
