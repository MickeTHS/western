#pragma once

#include <string>

#include "wst_trace.h"
#include "wst_screenrenderobj.h"
#include "wst_json_resource.h"


namespace wst {
    struct Environment : public Screen_render_obj, public Json_resource {
        Environment();

        bool init();
        Resource_type type();
        

        string _data;
        string _type;
    };

}