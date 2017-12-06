#include "wst_environment.h"

namespace wst {

    Environment::Environment() : Screen_render_obj(), Json_resource() {

    }

    bool Environment::init() {
        if (!Json_resource::init()) {
            LOG("  error: failed to init Environment '%s'\n", _filename.c_str());
            return false;
        }

        LOG("  init Environment '%s'...\n", _object_id.c_str());
        if (json.is_null()) {
            LOG("   error: json is null\n");
            return false;
        }

        if (!valid_string(json, "type")) { return false; }
        if (!valid_string(json, "data")) { return false; }

        if (!json["repeat_x"].is_null() && !json["repeat_x"].is_bool()) {
            LOG("   error: optional element \"repeat_x\" must be true or false\n");
            return false;
        }

        if (!json["repeat_y"].is_null() && !json["repeat_y"].is_bool()) {
            LOG("   error: optional element \"repeat_y\" must be true or false\n");
            return false;
        }

        bool repeat_x = json["repeat_x"].bool_value();
        bool repeat_y = json["repeat_y"].bool_value();
        _data = json["data"].string_value();
        _type = json["type"].string_value();
        

        LOG("   Environment: '%s', type: '%s'\n", _data.c_str(), _type.c_str());

        return true;
    }

    Resource_type Environment::type() {
        return RES_ANIMATION;
    }
}