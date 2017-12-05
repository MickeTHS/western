#pragma once

#include "wst_trace.h"

#include <string>
#include "json11.h"

using namespace std;

namespace wst {
    enum Resource_type {
        RES_NONE = 0,
        RES_SCENE,
        RES_MAIN,
        RES_CINEMATIC,
        RES_GAMEDEF,
        RES_CHARACTER,
        RES_ANIMATION,
        MAX_RES_TYPES
    };

    struct Json_resource {
        Json_resource();
        Json_resource(const string& filename);
        string id();
        bool load(const string& filepath);
        bool parse(const char* data);
        void set_json(json11::Json jsondata);

        bool valid_string   (json11::Json& j, const char* name);
        bool valid_bool     (json11::Json& j, const char* name);
        bool valid_int      (json11::Json& j, const char* name);
        bool valid_array    (json11::Json& j, const char* name);
        
        virtual bool init() = 0;
        virtual Resource_type type() = 0;

        static bool load_file(const string& filepath, json11::Json& json);

    protected:
        json11::Json json;
        string       _filename;
        string       _id;
    };
}