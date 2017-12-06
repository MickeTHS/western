#include "wst_animation.h"

#include "wst_trace.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


namespace wst {
    Animation_frame::Animation_frame(sf::Texture& tex, int x, int y, int w, int h) {
        sprite.setTexture(tex);
        sprite.setTextureRect(sf::IntRect(x, y, w, h));

        orig_size.w = w;
        orig_size.h = h;
    }

    sf::Sprite& Animation_frame::drawable() {
        return sprite;
    }

    Animation_frames::Animation_frames() {
        _current_frame = 0;
        _reversed = false;
    }

    bool Animation_frames::load_map(const string& fullpath, int f_width, int f_height, int num_frames) {
        sf::Texture tex;
        tex.loadFromFile(fullpath);
        sf::Vector2u size = tex.getSize();

        int num_x = size.x / f_width;
        int num_y = size.y / f_height;
        int x = 0;
        int y = 0;

        for (int i = 0; i < num_frames; ++i) {
            shared_ptr<Animation_frame> f = make_shared<Animation_frame>(tex, x, y, f_width, f_height);
            
            x++;

            if (x > num_x) {
                x = 0;
                y++;
            }

            if (y > num_y) {
                LOG("error: animation map expected dimensions: %d, %d\n", num_x, num_y);
                return false;
            }

            _frames.push_back(f);
        }
        
        _current_frame = 0;

        return true;
    }

    shared_ptr<Animation_frame> Animation_frames::current() {
        return _frames[_current_frame];
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

    shared_ptr<Animation_frame> Animation_frames::next() {
        shared_ptr<Animation_frame> f = _frames[_current_frame];

        if (_reversed) {
            _current_frame--;

            if (_current_frame < 0) {
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
}
