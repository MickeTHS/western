#pragma once

#include "wst_screenrenderobj.h"

#include <memory>
#include <vector>
#include <string>

using namespace std;

namespace wst {
    struct Asset_handler {
        
        Asset_handler(Asset_handler const&) = delete;
        Asset_handler& operator=(Asset_handler const&) = delete;

        static std::shared_ptr<Asset_handler> instance()
        {
            static std::shared_ptr<Asset_handler> s{new Asset_handler};
            return s;
        }

        shared_ptr<Screen_render_obj> get_by_id(const string& id);

    private:
        Asset_handler() {}

        vector<shared_ptr<Screen_render_obj>> _objects;
    };
}