#pragma once

#include "wst_screenrenderobj.h"
#include "wst_json_resource.h"

#include <memory>
#include <vector>
#include <string>


using namespace std;

namespace wst {
    
    struct Asset_manager {

        static string ROOT_FOLDER;
        
        Asset_manager(Asset_manager const&) = delete;
        Asset_manager& operator=(Asset_manager const&) = delete;

        static shared_ptr<Asset_manager> instance()
        {
            static shared_ptr<Asset_manager> s{new Asset_manager };
            return s;
        }

        shared_ptr<Json_resource> get_by_id(const string& id);

        shared_ptr<Json_resource> create_asset(const string& id, const string& filepath);

    private:
        Asset_manager() {}

        vector<shared_ptr<Json_resource>> _objects;
    };
}