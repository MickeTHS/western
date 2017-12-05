#include "wst_asset_manager.h"

#include "wst_player_character.h"
#include "wst_npc.h"

namespace wst {
    shared_ptr<Json_resource> Asset_manager::get_by_id(const string& id) {
        for (auto obj : _objects) {
            if (obj->id() == id) {
                return obj;
            }
        }

        return nullptr;
    }

    shared_ptr<Json_resource> Asset_manager::create_asset(const string& id, const string& filepath) {
        shared_ptr<Json_resource> res = get_by_id(id);

        if (res != nullptr) {
            return res;
        }

        json11::Json json;
        
        if (!Json_resource::load_file(filepath, json)) {
            LOG("error: cant load file %s\n", filepath);
            return nullptr;
        }

        if (!json["type"].is_string()) {
            LOG("error: %s missing \"type\" element\n", filepath);
            return nullptr;
        }

        string type = json["type"].string_value();

        if (type == "player") {
            res = make_shared<Player_character>();
        }
        else if (type == "npc") {
            

            if (!json["id"].is_string()) {
                LOG("error: NPC '%s' has missing \"id\" element\n", filepath.c_str());
                return nullptr;
            }

            res = make_shared<NPC>(json["id"].string_value());
        }

        if (res == nullptr) {
            LOG("error: %s has unrecognized type \"%s\"\n", type.c_str());
            return false;
        }

        res->set_json(json);
        res->init();

        _objects.push_back(res);

        return res;
    }

}