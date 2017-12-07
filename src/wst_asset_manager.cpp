#include "wst_asset_manager.h"

#include "wst_player_character.h"
#include "wst_npc.h"
#include "wst_environment.h"

namespace wst {
    string Asset_manager::ROOT_FOLDER = "";

    shared_ptr<Json_resource> Asset_manager::get_by_object_id(const string& id) {
        for (auto obj : _objects) {
            if (obj->object_id() == id) {
                return obj;
            }
        }

        return nullptr;
    }

    void Asset_manager::load_file_async(const string& id, const string& filepath, json11::Json json) {
        TRACE("ASYNC reading json file %s\n", filepath.c_str());

        if (!Json_resource::load_file(filepath, json)) {
            LOG("error: ASYNC cant load file %s\n", filepath.c_str());
            return;
        }

        if (!json["type"].is_string()) {
            LOG("error: ASYNC '%s' missing \"type\" element\n", filepath.c_str());
            return;
        }

        if (!json["object_id"].is_string()) {
            LOG("error: ASYNC '%s' missing \"object_id\" element\n", filepath.c_str());
            return;
        }

        string type = json["type"].string_value();
        shared_ptr<Json_resource> res = nullptr;

        if (type == "player") {
            res = make_shared<Player_character>();
        }
        else if (type == "npc") {
            res = make_shared<NPC>();
        }
        else if (type == "environment") {
            res = make_shared<Environment>();
        }

        if (res == nullptr) {
            LOG("error: ASYNC %s has unrecognized type \"%s\"\n", type.c_str());
            return;
        }


        res->set_json(json);
        res->init();

        _objects.push_back(res);
    }

    void Asset_manager::create_asset_async(const string& id, const string& filepath) {

        shared_ptr<Json_resource> res = get_by_object_id(id);

        if (res != nullptr) {
            return;
        }
     
        //std::function<void(Asset_manager*, const string& id, const string& filepath, json11::Json json)> fn(std::mem_fn(&Asset_manager::asset_loaded));

        json11::Json json;
        thread reader(&Asset_manager::load_file_async, this, id, filepath, json);
    }

    shared_ptr<Json_resource> Asset_manager::create_asset(const string& id, const string& filepath) {
        TRACE("creating asset: %s\n", id.c_str());

        shared_ptr<Json_resource> res = get_by_object_id(id);

        if (res != nullptr) {
            return res;
        }

        json11::Json json;

        TRACE("reading json file %s\n", filepath.c_str());
        
        if (!Json_resource::load_file(filepath, json)) {
            LOG("error: cant load file %s\n", filepath.c_str());
            return nullptr;
        }

        if (!json["type"].is_string()) {
            LOG("error: '%s' missing \"type\" element\n", filepath.c_str());
            return nullptr;
        }

        if (!json["object_id"].is_string()) {
            LOG("error: '%s' missing \"object_id\" element\n", filepath.c_str());
            return nullptr;
        }

        string type = json["type"].string_value();

        if (type == "player") {
            res = make_shared<Player_character>();
        }
        else if (type == "npc") {
            res = make_shared<NPC>();
        }
        else if (type == "environment") {
            res = make_shared<Environment>();
        }

        if (res == nullptr) {
            LOG("error: %s has unrecognized type \"%s\"\n", type.c_str());
            return nullptr;
        }

        res->set_json(json);
        res->init();

        _objects.push_back(res);

        return res;
    }

}