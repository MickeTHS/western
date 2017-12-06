#include "wst_player_character.h"

namespace wst {
    Player_character::Player_character(const std::string& prefix_path, int num_frames) 
        :   Screen_render_obj(),
            Json_resource() {}

    Player_character::Player_character() : Screen_render_obj(), Json_resource() {

    }


    bool Player_character::init() { 
        if (!Json_resource::init()) {
            LOG("error: failed to init Player_character '%s'\n", _filename.c_str());
            return false;
        }

        LOG("init player character...\n");
        return true; 
    }

    Resource_type Player_character::type() { 
        return RES_CHARACTER; 
    }

}