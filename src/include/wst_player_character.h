#pragma once

#include <string>
#include "wst_screenrenderobj.h"
#include "wst_json_resource.h"
#include "wst_trace.h"
#include "wst_types.h"

namespace wst {
    struct Player_character : public Screen_render_obj, public Json_resource {
        Player_character(const std::string& prefix_path, int num_frames);
        Player_character();
        
        bool init() override;
        Resource_type type() override;

    private:
        
    };
};