#pragma once

#include "wst_screenrenderobj.h"
#include "wst_json_resource.h"
#include "wst_file_trigger.h"

#include <memory>
#include <vector>
#include <string>
#include <thread>

using namespace std;

namespace wst {
    
    struct Asset_manager : public File_trigger {

        static string ROOT_FOLDER;
        
        Asset_manager(Asset_manager const&) = delete;
        Asset_manager& operator=(Asset_manager const&) = delete;

        static shared_ptr<Asset_manager> instance()
        {
            static shared_ptr<Asset_manager> s{new Asset_manager };
            return s;
        }

        shared_ptr<Json_resource> get_by_object_id(const string& id);

        shared_ptr<Json_resource> create_asset(const string& id, const string& filepath);
        void create_asset_async(const string& id, const string& filepath);

        //static void* async_asset_helper();

    private:
        Asset_manager() {}
        virtual void load_file_async(const string& id, const string& filepath, json11::Json json);
        
        vector<shared_ptr<Json_resource>> _objects;
    };
}