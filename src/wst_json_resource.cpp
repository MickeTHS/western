#include "wst_json_resource.h"

#include <stdio.h>
#include <stdlib.h>

namespace wst {
    Json_resource::Json_resource() {
        _id = "none";
    }

    Json_resource::Json_resource(const string& filepath) {
        _id = filepath;
        load(filepath);
    }

    string Json_resource::id() {
        return _id;
    }

    bool Json_resource::load(const string& filepath) {
        _filename = filepath;

        return Json_resource::load_file(filepath, json);
    }
    
    bool Json_resource::load_file(const string& filepath, json11::Json& json) {
        
        FILE *f = fopen(filepath.c_str(), "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  //same as rewind(f);

        char *content = (char*)malloc(fsize + 1);
        fread(content, fsize, 1, f);
        fclose(f);
        content[fsize] = 0;

        std::string err;
        json = json11::Json::parse(content, err);
        LOG("load_file: %s\n", json["id"].string_value().c_str());
        free(content);

        if (!err.empty()) {
            TRACE("load err: %s", err.c_str());
            return false;
        }

        return true;

    }
}