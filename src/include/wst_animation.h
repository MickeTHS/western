#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "wst_types.h"

using namespace std;

namespace wst {

    struct Animation_frame : public Pos_graph_node {
        Animation_frame(sf::Texture& tex, int x, int y, int w, int h);
        
        sf::Sprite &drawable();

        sf::Texture tex;
        sf::Sprite sprite;

        Size orig_size;
    };

    struct Animation_frames : public Pos_graph_node {
        Animation_frames();

        bool load_map(const string& fullpath, int f_width, int f_height, int num_frames);
        
        shared_ptr<Animation_frame> next();
        shared_ptr<Animation_frame> current();

        void set_tex_repeat(bool repeat);
        void set_size(Size size) override;
        void set_reversed(bool reverse);
    private:
        vector<shared_ptr<Animation_frame>> _frames;
        int _current_frame;
        bool _repeat;
        bool _reversed;
    };
}
