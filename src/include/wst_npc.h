#pragma once

#include <string>

#include "wst_json_resource.h"
#include "wst_screenrenderobj.h"
#include "wst_trace.h"

using namespace std;

namespace wst {
    struct NPC : public Screen_render_obj, public Json_resource {
        NPC();

        string object_id();

        bool init();
        Resource_type type();

    private:
        
        string _type;
        string _animation;
        string _data;
        int _num_frames;
    };
}