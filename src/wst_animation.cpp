#include "wst_animation.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


namespace wst {
    Animation_frame::Animation_frame(const std::string& path) {
        if (!tex.loadFromFile(path)) {
            std::cout << "unable to load " << path << std::endl;
            exit(0);
        }

        sprite.setTexture(tex);
    }

    sf::Drawable& Animation_frame::drawable() {
        return sprite;
    }

    Animation_frames::Animation_frames(const std::string& prefix_path, int num_frames) {
        load(prefix_path, num_frames);
    }

    Animation_frames::Animation_frames() {
        _current_frame = 0;
    }

    void Animation_frames::load(const std::string& prefix_path, int num_frames) {
        for (int i = num_frames-1; i >= 0; --i) {
            _frames.push_back(new Animation_frame(prefix_path + std::to_string(i) + ".png"));
        }
        _current_frame = 0;
    }

    Animation_frame* Animation_frames::current() {
        Animation_frame* f = _frames[_current_frame];

        return f;
    }

    Animation_frame* Animation_frames::next() {
        Animation_frame* f = _frames[_current_frame];

        _current_frame++;

        if (_current_frame >= _frames.size()) {
            _current_frame = 0;
        }

        return f;
    }
}
