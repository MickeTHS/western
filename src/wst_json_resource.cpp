#include "wst_json_resource.h"

#include <stdio.h>
#include <stdlib.h>

namespace wst {
    Json_resource::Json_resource() {}

    Json_resource::Json_resource(const string& filepath) {
        load(filepath);
    }

    bool Json_resource::load(const string& filepath) {
        _filename = filepath;

        FILE *f = fopen(filepath.c_str(), "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  //same as rewind(f);

        char *content = (char*)malloc(fsize + 1);
        fread(content, fsize, 1, f);
        fclose(f);

        std::string err;
        json = json11::Json::parse(content, err);

        if (!err.empty()) {
            TRACE("load err: %s", err.c_str());
            return false;
        }

        return true;
    }
}