#include "wst_screenrenderobj.h"
#include "wst_trace.h"

namespace wst {
    
    Screen_render_obj::Screen_render_obj() {
        _timer = 0;
        _reversed = false;
        _frame_rate = 0.1;
    }

    void Screen_render_obj::load_map(const string& fullpath, int f_width, int f_height, int num_frames) {
        _name = fullpath;
        _frames.load_map(fullpath, f_width, f_height, num_frames);
        
        sf::IntRect rect = _frames.current()->drawable().getTextureRect();

        _size.w = rect.width;
        _size.h = rect.height;
        _orig_size.w = rect.width;
        _orig_size.h = rect.height;

        _valid = true;
    }

    string Screen_render_obj::name() {
        return _name;
    }

    void Screen_render_obj::set_name(const string& name) {
        _name = name;
    }


    void Screen_render_obj::set_framerate(double rate) {
        _frame_rate = rate;
    }

    void Screen_render_obj::render(double delta, sf::RenderTarget* target) {
        //std::cout << "delta: " << delta << " timer: " << _timer << std::endl;
        
        _timer += delta;

        if (_timer > _frame_rate) {
            _frames.next();
            _timer = 0;
        }
        
        Pos p = abs_pos();

        _frames.current()->drawable().setPosition((float)p.x, (float)p.y);

        target->draw(_frames.current()->drawable());
    }


    void Screen_render_obj::set_reversed(bool reverse) {
        _reversed = reverse;

        _frames.set_reversed(_reversed);
    }

    void Screen_render_obj::set_size(Size size) {
        _frames.set_size(size);
    }

    void Screen_render_obj::set_pos(Pos p) {
        if (_fill_prop == FillScene_Repeat_x) {
            if (!_valid) {
                return;
            }

            if (_pos.x > _parent->pos().x) {
                _pos.x = _parent->pos().x - _frames.current()->orig_size.w;
            }
            else if (_pos.x < _parent->pos().x - _frames.current()->orig_size.w) {
                _pos.x = _parent->pos().x;
            }
            else {
                _pos = p;
            }
        }
        else {
            _pos = p;
            _frames.set_pos(p);
        }
    }
}