#pragma once

#include "wst_trace.h"

#include <functional>
#include <string>
#include "json11.h"
#include "wst_file_trigger.h"

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
        string object_id();
        bool load(const string& filepath);
        bool parse(const char* data);
        void set_json(json11::Json jsondata);

        bool valid_string   (json11::Json& j, const char* name, bool log_failure=true);
        bool valid_bool     (json11::Json& j, const char* name, bool log_failure=true);
        bool valid_int      (json11::Json& j, const char* name, bool log_failure=true);
        bool valid_array    (json11::Json& j, const char* name, bool log_failure=true);
        
        virtual bool init();
        virtual Resource_type type() = 0;

        static bool load_file(const string& filepath, json11::Json& json);
       
    protected:
        json11::Json json;
        string       _filename;
        string       _object_id;
    };
}