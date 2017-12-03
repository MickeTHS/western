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

        orig_size.w = sprite.getTextureRect().width;
        orig_size.h = sprite.getTextureRect().height;
    }

    sf::Sprite& Animation_frame::drawable() {
        return sprite;
    }

    Animation_frames::Animation_frames(const std::string& prefix_path, int num_frames) {
        load(prefix_path, num_frames);
        _reversed = false;
    }

    Animation_frames::Animation_frames() {
        _current_frame = 0;
        _reversed = false;
    }

    void Animation_frames::load(const std::string& prefix_path, int num_frames) {
        for (int i = num_frames-1; i >= 0; --i) {
            Animation_frame *f = new Animation_frame(prefix_path + std::to_string(i) + ".png");

            f->set_parent(this);
            _frames.push_back(f);
            //_frames.push_back(new Animation_frame(prefix_path + std::to_string(i) + ".png"));
        }
        _current_frame = 0;
    }

    Animation_frame* Animation_frames::current() {
        Animation_frame* f = _frames[_current_frame];

        return f;
    }

    void Animation_frames::set_tex_repeat(bool repeat) {
        for (size_t i = 0; i < _frames.size(); ++i) {
            //std::cout << "setting repeat" << _parent->pos().x << " " << _parent->pos().y << " " << _parent->size().w << " " << _parent->size().h << std::endl;
            _frames[i]->tex.setRepeated(repeat);
            //_frames[i]->sprite.setTextureRect(sf::IntRect(_parent->pos().x, _parent->pos().y, _parent->size().w, _parent->size().h));
            //_frames[i]->sprite.setTextureRect(sf::IntRect(0,0,800,300));
        }
    }

    void Animation_frames::set_reversed(bool reverse) {
        _reversed = reverse;
    }

    Animation_frame* Animation_frames::next() {
        Animation_frame* f = _frames[_current_frame];

        if (_reversed) {
            _current_frame--;

            if (_current_frame <= 0) {
                _current_frame = _frames.size()-1;
            }
        }
        else {
            _current_frame++;

            if (_current_frame >= _frames.size()) {
                _current_frame = 0;
            }
        }

        

        return f;
    }

    void Animation_frames::set_size(Size size) {
        for (size_t i = 0; i < _frames.size(); ++i) {
            _frames[i]->sprite.setTextureRect(sf::IntRect(0, 0, size.w, size.h));
            _frames[i]->set_size(size);
        }
    }
}
