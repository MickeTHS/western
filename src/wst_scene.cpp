#include "wst_scene.h"

namespace wst {
    
    Scene_layer::Scene_layer(const std::string& id, bool load_now) {
        _id = id;

        if (load_now) {
            load();
        }
    }
    
    void Scene_layer::load() {
        //TODO: load from file

        // some mockups?

        if (_id == "backdrop") {

        }

        if (_id == "ground1") {
            
        }

        if (_id == "frontpan") {

        }

        if (_id == "sky") {

        }

    }

    void Scene_layer::set_keep_in_view(bool keep) {
        _keep_in_view = keep;
    }

    void Scene_layer::set_rect(int left, int top, int width, int height) {
        _rect = Rect(left, top, width, height);
    }
    
    void Scene_layer::add_render_obj(Screen_render_obj* obj) {
        _render_objects.push_back(obj);
    }


    void Scene_layer::set_z_index(int index) { _z_index = index; }
    int Scene_layer::z_index() { return _z_index; }

    Scene::Scene() {}

    void Scene::add_layer(Scene_layer* layer) {
        _layers.push_back(layer);
    }
}