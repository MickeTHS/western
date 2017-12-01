#include "wst_scene.h"

namespace wst {

    bool sort_layers(Scene_layer* a, Scene_layer* b) { return (a->z_index() < b->z_index()); }
    
    Scene_layer::Scene_layer(const std::string& id, bool load_now) {
        _id = id;
        _z_index = 0;

        if (load_now) {
            load();
        }
    }
    
    void Scene_layer::load() {
        //TODO: load from file

        // some mockups?

    }

    std::string Scene_layer::id() { return _id; }

    void Scene_layer::render(double delta, sf::RenderTarget* target) {
        for (size_t i = 0; i < _render_objects.size(); ++i) {
            _render_objects[i]->render(delta, target);
        }
    }

    void Scene_layer::set_keep_in_view(bool keep) {
        _keep_in_view = keep;
    }

    void Scene_layer::set_rect(int left, int top, int width, int height) {
        _rect = Rect(left, top, width, height);
    }
    
    void Scene_layer::add_render_obj(Screen_render_obj* obj) {
        obj->set_parent(this);
        add(obj);
        _render_objects.push_back(obj);
    }

    float Scene_layer::pan_multiplier() { return _pan_multiplier; }
    void Scene_layer::set_pan_multiplier(float mult) { _pan_multiplier = mult; }


    void Scene_layer::set_z_index(int index) { _z_index = index; }
    int Scene_layer::z_index() { return _z_index; }

    Scene::Scene() {

    }

    void Scene::add_layer(Scene_layer* layer) {
        layer->set_parent(this);
        add(layer);
        _layers.push_back(layer);
    }

    Scene_layer* Scene::layer(const std::string& id) {
        for (size_t i = 0; i < _layers.size(); ++i) {
            if (_layers[i]->id() == id) {
                return _layers[i];
            }
        }

        return NULL;
    }

    Rect Scene::clipping_rect() { return _clipping_rect; }
    void Scene::set_clipping_rect(Rect rect) { _clipping_rect = rect; }
        
    Rect Scene::rect() { return _view_rect; }
    void Scene::set_rect(Rect rect) { _view_rect = rect; }
    
    void Scene::order_layers() {
        std::sort(_layers.begin(), _layers.end(), sort_layers);
    }

    void Scene::render(double delta, sf::RenderTarget* target) {
        for (size_t i = 0; i < _layers.size(); ++i) {
            _layers[i]->render(delta, target);
        }
    }

}