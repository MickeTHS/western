#include "wst_scene.h"
#include "wst_trace.h"

namespace wst {

    bool sort_layers(Scene_layer* a, Scene_layer* b) { return (a->z_index() < b->z_index()); }

    Frame::Frame(int time, const string& object_id, const string& action) {
        _time       = time;
        _object_id  = object_id;
        _action     = action;
    }
    
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
        if (_parent == NULL) {
            return _size;
        }

        return _parent->size();
    }

    Scene::Scene(const string& filepath) : Json_resource(filepath) {
        _clipping_rect.size = Size(0,0);
        _clipping_rect.topleft = Pos(0,0);
    }

    Resource_type Scene::type() {
        return _type;
    }

    bool Scene::init() {

        LOG("reading json file '%s'...\n", _filename.c_str());

        if (!valid_string(json, "type")) { return false; }
        if (!valid_bool(json, "skippable")) { return false; }
        if (!valid_string(json, "next_scene")) { return false; }
        if (!valid_array(json, "assets")) { return false; }
        if (!valid_array(json, "frames")) { return false; }
    
        if (json["type"] == "cinematic") { _type = RES_CINEMATIC; }
        else { _type = RES_SCENE; }

        _skippable  = json["skippable"].bool_value();
        _next_scene = json["next_scene"].string_value();

        auto assets = json["assets"].array_items();

        for (size_t i = 0; i < assets.size(); ++i) {
            if (!valid_string(assets[i], "object_id")) { return false; }
            if (!valid_string(assets[i], "file")) { return false; }
            
            
            string asset_id = assets[i]["object_id"].string_value();
            string filepath = assets[i]["file"].string_value();
        }

        auto frames = json["frames"].array_items();

        for (size_t i = 0; i < frames.size(); ++i) {
            if (!valid_int(frames[i], "time")) { return false; }
            if (!valid_string(frames[i], "object_id")) { return false; }
            if (!valid_string(frames[i], "action")) { return false; }
            if (!valid_array(frames[i], "pos")) { return false; }
            
            int time = frames[i]["time"].int_value();
            string object_id = frames[i]["object_id"].string_value();
            string action = frames[i]["action"].string_value();
            int x = frames[i]["pos"][0].int_value();
            int y = frames[i]["pos"][1].int_value();

            TRACE("  Frame (%d): time: %d, object_id: %s, action: %s, x: %d, y: %d", i, time, object_id.c_str(), action.c_str(), x, y);
        }
        
        //_assets
        return true;
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