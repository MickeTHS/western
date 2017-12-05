#pragma once

#include "wst_trace.h"

#include <string>
#include "json11.h"

using namespace std;

namespace wst {
    enum Resource_type {
        NONE = 0,
        SCENE,
        MAIN,
        CINEMATIC,
        GAMEDEF,
        CHARACTER,
        ANIMATION,
        MAX_RESOURCE_TYPES
    };

    struct Json_resource {
        Json_resource();
        Json_resource(const string& filename);
        bool load(const string& filepath);
        
        virtual bool init() = 0;
        virtual Resource_type type() = 0;

    protected:
        json11::Json json;
        string       _filename;
    };
}