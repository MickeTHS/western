#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "wst_types.h"

namespace wst {

    struct Animation_frame : public Pos_graph_node {
        Animation_frame(const std::string &path);
        sf::Sprite &drawable();

        sf::Texture tex;
        sf::Sprite sprite;

        Size orig_size;
    };

    struct Animation_frames : public Pos_graph_node {
        Animation_frames(const std::string &prefix_path, int num_frames);
        Animation_frames();

        void load(const std::string &prefix_path, int num_frames);

        Animation_frame *next();
        Animation_frame *current();

        void set_tex_repeat(bool repeat);
        void set_size(Size size) override;
        void set_reversed(bool reverse);
    private:
        std::vector<Animation_frame *> _frames;
        int _current_frame;
        bool _repeat;
        bool _reversed;
    };
}
