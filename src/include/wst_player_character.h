#pragma once

#include <string>
#include "wst_screenrenderobj.h"

namespace wst {
    struct Player_character : public Screen_render_obj {
        Player_character(const std::string& prefix_path, int num_frames);
        Player_character();
        

    private:
        
    };
};