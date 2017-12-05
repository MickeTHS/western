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

    void Json_resource::set_json(json11::Json jsondata) {
        json = jsondata;
    }

    bool Json_resource::parse(const char* data) {
        std::string err;
        json = json11::Json::parse(data, err);

        if (!err.empty()) {
            TRACE("load err: %s", err.c_str());
            return false;
        }

        return true;
    }

    bool Json_resource::valid_string(json11::Json& j, const char* name) {
        if (!j[name].is_string()) {
            LOG("element \"%s\" is missing or not a string\n", name);
            return false;
        }

        return true;
    }

    
    bool Json_resource::valid_bool(json11::Json& j, const char* name) {
        if (!j[name].is_bool()) {
            LOG("element \"%s\" is missing or not a boolean (true or false)\n", name);
            return false;
        }

        return true;
    }

    bool Json_resource::valid_int(json11::Json& j, const char* name) {
        if (!j[name].is_number()) {
            LOG("element \"%s\" is missing or not an integer\n", name);
            return false;
        }

        return true;
    }

    bool Json_resource::valid_array(json11::Json& j, const char* name) {
        if (!j[name].is_array()) {
            LOG("element \"%s\" is missing or not an array\n", name);
            return false;
        }

        return true;
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
        
        free(content);

        if (!err.empty()) {
            TRACE("load err: %s", err.c_str());
            return false;
        }

        return true;

    }
}