#include "wst_asset_manager.h"

namespace wst {
    shared_ptr<Json_resource> Asset_manager::get_by_id(const string& id) {
        for (auto obj : _objects) {
            if (obj->id() == id) {
                return obj;
            }
        }

        return nullptr;
    }

    shared_ptr<Json_resource> Asset_manager::create_asset(const string& id, const string& filepath) {
        return nullptr;
    }

}