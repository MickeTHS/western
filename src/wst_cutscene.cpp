#include "wst_cutscene.h"

namespace wst {
    Frame::Frame(int time, const string& object_id, const string& action) {
        _time       = time;
        _object_id  = object_id;
        _action     = action;
    }

    Cutscene::Cutscene(const string& filepath) : Json_resource(filepath) {
    
    }

    bool Cutscene::init() {
        /*"type":"cinematic",
    "skippable":true,
    "next_scene":"scene_0.json",
    "assets": [
        {
            "object_id":"somehorse",
            "file":"../characters/horse.json"
        }
    ],
    "frames": [
        {
            "time":0,
            "object_id":"somehorse",
            "action":"gallop",
            "pos":[-100,200]
        },
        {
            "time":10000,
            "object_id":"somehorse",
            "action":"stop",
            "pos":[200,200]
        }
    ]*/
        LOG("reading json file '%s'...\n", _filename.c_str());

        if (!json["type"].is_string()) {
            LOG("error: \"type\" must be \"cinematic\"");
            return false;
        }

        if (!json["skippable"].is_bool()) {
            LOG("error: \"skippable\" must be true or false");
            return false;
        }

        if (!json["next_scene"].is_string()) {
            LOG("error: \"next_scene\" must be a reference to a json file");
            return false;
        }

        if (!json["assets"].is_array()) {
            LOG("error: \"assets\" must be an array [] ");
            return false;
        }

        if (!json["frames"].is_array()) {
            LOG("error: \"frames\" must be an array [] of frame objects ");
            return false;
        }
        
        _type       = json["type"].string_value();
        _skippable  = json["skippable"].bool_value();
        _next_scene = json["next_scene"].string_value();

        auto assets = json["assets"].array_items();

        for (size_t i = 0; i < assets.size(); ++i) {
            if (!assets[i]["object_id"].is_string()) {
                LOG("error: asset index %d element \"object_id\" must be a string referencing an asset ", i);
                return false;
            }
            if (!assets[i]["file"].is_string()) {
                LOG("error: asset index %d element \"file\" must be the relative path to asset definition file ", i);
                return false;
            }
            
            string asset_id = assets[i]["object_id"].string_value();
            string filepath = assets[i]["file"].string_value();
            //string asset_id = 
            //_asset_ids.push_back(assets[i].string_value());
        }

        auto frames = json["frames"].array_items();

        for (size_t i = 0; i < frames.size(); ++i) {
            if (!frames[i]["time"].is_number()) {
                LOG("error: frame index %d element \"time\" must be a number (number of milliseconds since scene start) ", i);
                return false;
            }
            if (!frames[i]["object_id"].is_string()) {
                LOG("error: frame index %d element \"object_id\" must be a string referencing an asset or object ", i);
                return false;
            }
            if (!frames[i]["action"].is_string()) {
                LOG("error: frame index %d element \"action\" must be a string referencing an animation action ", i);
                return false;
            }
            if (!frames[i]["pos"].is_array()) {
                LOG("error: frame index %d element \"pos\" must be an array of x and y position [x,y] in scene_layer space ", i);
                return false;
            }

            int time = frames[i]["time"].int_value();
            string object_id = frames[i]["object_id"].string_value();
            string action = frames[i]["action"].string_value();
            int x = frames[i]["pos"][0].int_value();
            int y = frames[i]["pos"][1].int_value();

            TRACE("  Frame (%d): time: %d, object_id: %s, action: %s, x: %d, y: %d", i, time, object_id.c_str(), action.c_str(), x, y);
        }
        
        //_assets

        return true;
    }

    Resource_type Cutscene::type() {
        return RES_CINEMATIC;
    }
}