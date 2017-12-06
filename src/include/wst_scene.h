#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "wst_animation.h"
#include "wst_worldobj.h"
#include "wst_screenrenderobj.h"
#include "wst_types.h"
#include "wst_json_resource.h"



namespace wst {
    struct Frame {
        Frame(int time, const string& object_id, const string& layer, const string& action, Pos p);

        int     _time;
        string  _object_id;
        string  _action;
        string  _layer;

        Pos     _pos;
    };
    
    struct Scene_layer : public Pos_graph_node {
        Scene_layer();
        Scene_layer(const string& id, bool load_now);

        void    set_keep_in_view(bool keep);
        void    set_rect(int left, int top, int width, int height);
        void    set_rect(Rect r);
        void    load();
        
        string id();

        void    set_z_index(int index);
        void    add_render_obj(shared_ptr<Screen_render_obj> obj);
        int     z_index();
        float   pan_multiplier();
        void    set_pan_multiplier(float mult);
        void    render(double delta, sf::RenderTarget* target);
        
    private:
        string     _id;

        // the order to draw the layers when grouped in a scene with multiple layers (pretty much always)
        int             _z_index;

        // determines if the the layer is kept in view when player has panned the view beyond its rect
        bool            _keep_in_view;

        // determines how fast the layer will move past as the player moves, 1.0f = follows player
        float           _pan_multiplier; 

        // the bounding rect of the layer
        Rect            _rect;

        FillScene       _fill_prop;


        vector<shared_ptr<Screen_render_obj>> _render_objects;
    };

    bool sort_layers(shared_ptr<Scene_layer> a, shared_ptr<Scene_layer> b);

    struct Scene : public Pos_graph_node, public Json_resource  {
        Scene(const string& filepath);

        bool init() override;
        Resource_type type() override;
        bool create();

        // this determines the size of the scene
        void set_rect(Rect rect);
        Rect rect();
        
        // clipping rect is the way we "clip" the scene. if we move the clipping rect it wont cause the scene to move,
        // rather it will cause the "lens" to move
        void set_clipping_rect(Rect rect);
        Rect clipping_rect();

        void order_layers();

        void add_layer(shared_ptr<Scene_layer> layer);
        shared_ptr<Scene_layer> layer(const std::string& id);
        void update_children();

        void render(double delta, sf::RenderTarget* target);

    private:
        Rect _view_rect;
        Rect _clipping_rect;

        bool    _skippable;
        string  _next_scene;
        
        Resource_type _type;
        
        vector<shared_ptr<Frame>>               _frames;
        vector<shared_ptr<Scene_layer>>         _layers;
        vector<shared_ptr<Screen_render_obj>>   _assets;
    };
}