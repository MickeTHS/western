#include "wst_player_character.h"

namespace wst {
    Player_character::Player_character(const std::string& prefix_path, int num_frames) : Screen_render_obj(prefix_path, num_frames) {}

    Player_character::Player_character() : Screen_render_obj() {

    }
}