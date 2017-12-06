/**
 * A Screen_render_obj is an object that is rendered on the screen
 * 
 * It should serve as the base class for all objects that is to be rendered,
 * no matter the size of complexity of the underlying object.
 * 
 * 
 * Every Screen_render_obj has an Animation_frame as the rendered sprite,
 * even if the object has no animation it still has an Animation_frame (but only 1)
 * to render itself.
 * 
 * To render, we must have a window to render to.
 * 
 * 
*/
#pragma once

#include <string>
#include <memory>

#include "wst_animation.h"
#include "wst_types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

namespace wst {

    struct Screen_render_obj : public Pos_graph_node {
        
        Screen_render_obj();

        void load_map(const string& fullpath, int f_width, int f_height, int num_frames);
        
        void render(double delta, sf::RenderTarget* target);

        string name();
        void set_name(const string& id);

        void update();

        void set_reversed(bool reverse);

        void set_framerate(double rate);
    private:
        Animation_frames    _frames;
        double              _timer;
        FillScene           _fill_prop;
        bool                _valid;
        bool                _reversed;
        double              _frame_rate;
        string              _name;
    };
}