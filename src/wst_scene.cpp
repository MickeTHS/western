#include "wst_scene.h"

namespace wst {

    bool sort_layers(Scene_layer* a, Scene_layer* b) { return (a->z_index() < b->z_index()); }
    
    Scene_layer::Scene_layer(const std::string& id, bool load_now) {
        _id = id;
        _z_index = 0;
        _fill_prop = FillScene_No;

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

    // this is the clipping rect we get from the parent scene
    // this is so we know how to fill the view
    void Scene_layer::set_rect(int left, int top, int width, int height) {
        _rect = Rect(left, top, width, height);
    }

    void Scene_layer::set_rect(Rect r) {
        _rect = r;
    }
    
    void Scene_layer::add_render_obj(Screen_render_obj* obj) {
        obj->set_parent(this);
        add(obj);
        _render_objects.push_back(obj);
    }

    float Scene_layer::pan_multiplier() { 
        return _pan_multiplier;
    }

    void Scene_layer::set_pan_multiplier(float mult) { 
        _pan_multiplier = mult;
    }

    void Scene_layer::set_z_index(int index) { 
        _z_index = index;
    }
    
    int Scene_layer::z_index() { 
        return _z_index;
    }

    Size Scene_layer::size() {
        return _parent->size();
    }

    Scene::Scene() {

    }

    void Scene::add_layer(Scene_layer* layer) {
        layer->set_parent(this);
        add(layer);
        _layers.push_back(layer);

        update_children();
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

    void Scene::set_clipping_rect(Rect rect) { 
        _clipping_rect = rect;
        _size = rect.size;
        update_children();
    }

    // update the layers part of this scene
    void Scene::update_children() {
        for (size_t i = 0; i < _layers.size(); ++i) {
            _layers[i]->set_rect(_clipping_rect);
        }
    }

    Rect Scene::rect() { return _view_rect; }
    
    void Scene::set_rect(Rect rect) {
        _view_rect = rect;
        //_size = rect.size;
        update_children();
    }
    
    void Scene::order_layers() {
        std::sort(_layers.begin(), _layers.end(), sort_layers);
    }

    void Scene::render(double delta, sf::RenderTarget* target) {
        for (size_t i = 0; i < _layers.size(); ++i) {
            _layers[i]->render(delta, target);
        }
    }

    Size Scene::size() {
        return _clipping_rect.size;
    }
}