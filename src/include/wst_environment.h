#pragma once

#include <string>

#include "wst_trace.h"
#include "wst_screenrenderobj.h"
#include "wst_json_resource.h"


namespace wst {
    struct Environment : public Screen_render_obj, public Json_resource {
        Environment();

        bool init() override;
        Resource_type type() override;
        

        string _data;
        string _type;
    };

}