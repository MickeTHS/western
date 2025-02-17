#include "wst_scene.h"
#include "wst_trace.h"
#include "wst_asset_manager.h"

namespace wst {

    bool sort_layers(shared_ptr<Scene_layer> a, shared_ptr<Scene_layer> b) { return (a->z_index() < b->z_index()); }

    Frame::Frame(int time, const string& object_id, const string& layer, const string& action, Pos p) {
        _time       = time;
        _object_id  = object_id;
        _action     = action;
        _pos        = p;
        _layer      = layer;
    }
    Scene_layer::Scene_layer() {}

    Scene_layer::Scene_layer(const string& id, bool load_now) {
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

    string Scene_layer::id() { return _id; }

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
    
    void Scene_layer::add_render_obj(shared_ptr<Screen_render_obj> obj) {
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


    Scene::Scene(const string& filepath) : Json_resource(filepath) {
        _clipping_rect.size = Size(0,0);
        _clipping_rect.topleft = Pos(0,0);
    }

    Resource_type Scene::type() {
        return _type;
    }

    bool Scene::init() {
        if (!Json_resource::init()) {
            LOG("  error: failed to init Scene '%s'\n", _filename.c_str());
            return false;
        }

        LOG("  reading json file '%s'...\n", _filename.c_str());

        if (!valid_string(json, "type")) { return false; }
        if (!valid_bool(json, "skippable")) { return false; }
        if (!valid_string(json, "next_scene")) { return false; }
        if (!valid_array(json, "assets")) { return false; }
        if (!valid_array(json, "frames")) { return false; }
    
        if (json["type"] == "cinematic") { _type = RES_CINEMATIC; }
        else { _type = RES_SCENE; }

        TRACE("valid json '%s'...\n", _filename.c_str());

        _skippable  = json["skippable"].bool_value();
        _next_scene = json["next_scene"].string_value();

        auto assets = json["assets"].array_items();

        for (size_t i = 0; i < assets.size(); ++i) {
            if (!valid_string(assets[i], "object_id")) { return false; }
            if (!valid_string(assets[i], "file")) { return false; }
            if (!valid_string(assets[i], "type")) { return false; }

            string asset_id = assets[i]["object_id"].string_value();
            string filepath = assets[i]["file"].string_value();
            string type     = assets[i]["type"].string_value();

            TRACE("valid json asset: %s\n", asset_id.c_str());

            Asset_manager::instance()->create_asset(asset_id, Asset_manager::ROOT_FOLDER + filepath);
        }

        auto frames = json["frames"].array_items();

        for (size_t i = 0; i < frames.size(); ++i) {
            Pos p;
            if (!valid_int(frames[i], "time")) { return false; }
            if (!valid_string(frames[i], "object_id")) { return false; }
            if (!valid_string(frames[i], "layer")) { return false; }
            if (!valid_string(frames[i], "action", false)) { LOG("    Info: No action on frame\n"); }
            if (!valid_array(frames[i], "pos", false)) { LOG("    Info: No pos on frame\n"); }
            else { 
                p.x = frames[i]["pos"][0].int_value();
                p.y = frames[i]["pos"][1].int_value();
            }
            
            int time = frames[i]["time"].int_value();
            string object_id = frames[i]["object_id"].string_value();
            string action = frames[i]["action"].string_value();
            string layer = frames[i]["layer"].string_value();
            
            LOG("    Frame (%d): time: %d, object_id: %s, layer: %s, action: %s, x: %d, y: %d\n", i, time, object_id.c_str(), layer.c_str(), action.c_str(), p.x, p.y);

            shared_ptr<Frame> frame = make_shared<Frame>(time, object_id, layer, action, p);

            _frames.push_back(frame);
        }
        
        //_assets
        return true;
    }

    bool Scene::create() {
        // create assets

        // create layers

        for (auto f : _frames) {
            auto l = layer(f->_layer);

            if (l == nullptr) {
                l = make_shared<Scene_layer>(f->_layer, true);
                _layers.push_back(l);
            }

            
        }

        return true;
    }

    void Scene::add_layer(shared_ptr<Scene_layer> layer) {
        add(layer);
        _layers.push_back(layer);

        update_children();
    }

    shared_ptr<Scene_layer> Scene::layer(const string& id) {
        for (size_t i = 0; i < _layers.size(); ++i) {
            if (_layers[i]->id() == id) {
                return _layers[i];
            }
        }

        return nullptr;
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
}