#pragma once

#include <vector>
#include <string>

namespace wst {
    struct Rect {
        Rect() { left = 0; top = 0; width = 0; height = 0; }
        Rect(int left, int top, int width, int height) {
            this->left   = left;
            this->top    = top;
            this->width  = width;
            this->height = height;
        }

        int left, top, width, height;
    };

    struct Scene_layer {
        Scene_layer(const std::string& id, bool load_now);

        void set_keep_in_view(bool keep);
        void set_rect(int left, int top, int width, int height);
        void load();

        void set_z_index(int index);
        int z_index();
    private:
        std::string     _id;
        // the order to draw the layers when grouped in a scene with multiple layers (pretty much always)
        int             _z_index;

        // determines if the the layer is kept in view when player has panned the view beyond its rect
        bool            _keep_in_view;

        // determines how fast the layer will move past as the player moves, 1.0f = follows player
        float           _pan_multiplier; 

        // the bounding rect of the layer
        Rect            _rect;

    };

    struct Scene {
        Scene();

        void add_layer(Scene_layer* layer);

    private:
        std::vector<Scene_layer*> _layers;
    };
}