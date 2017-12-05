#include "wst_npc.h"

#include "wst_trace.h"


namespace wst {
    NPC::NPC(const string& id) : Screen_render_obj(), Json_resource(), _object_id(id) {}

    string NPC::object_id() { return _object_id; }

    bool NPC::init() {
        LOG("init NPC '%s'...\n", _object_id.c_str());
        if (json.is_null()) {
            LOG("error: json is null...\n");
            return false;
        }

        if (!json["type"].is_string()) {
            LOG("error: \"type\" must be \"npc\"\n");
            return false;
        }

        if (!json["data"].is_string()) {
            LOG("error: \"data\" must be path to file\n");
            return false;
        }

        if (!json["animation"].is_string()) {
            LOG("error: \"animation\" must be a name of the animation\n");
            return false;
        }

        if (!json["num_frames"].is_number()) {
            LOG("error: \"num_frames\" must be integer ");
            return false;
        }

        _data       = json["data"].string_value();
        _animation  = json["animation"].string_value();
        _type       = json["type"].string_value();
        _num_frames = json["num_frames"].int_value();


        TRACE("NPC loaded: %s, %s, %s, %d\n", _data.c_str(), _animation.c_str(), _type.c_str(), _num_frames);

        return true;
    }

    Resource_type NPC::type() {
        return RES_CHARACTER;
    }
}