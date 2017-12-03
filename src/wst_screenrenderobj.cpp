#include "wst_screenrenderobj.h"

namespace wst {
    Screen_render_obj::Screen_render_obj(const std::string& prefix_path, int num_frames) {
        load(prefix_path, num_frames);
        _timer = 0;
        _reversed = false;
        _frame_rate = 0.1;
        
    }

    Screen_render_obj::Screen_render_obj() {
        _timer = 0;
        _reversed = false;
        _frame_rate = 0.1;
    }

    void Screen_render_obj::load(const std::string& prefix_path, int num_frames) {
        _frames.load(prefix_path, num_frames);
        _frames.set_parent(this);

        sf::IntRect rect = _frames.current()->drawable().getTextureRect();

        _size.w = rect.width;
        _size.h = rect.height;
        _valid = true;
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

    void Screen_render_obj::set_fill(FillScene prop) { 
        _valid = false;
        _fill_prop = prop;

    }

    FillScene Screen_render_obj::get_fill() { 
        return _fill_prop; 
    }

    void Screen_render_obj::update() {
        if (_fill_prop == FillScene_Repeat_x) {
            if (_parent == NULL) {
                std::cout << "parent null when attempting fillscene, illegal" << std::endl;
                return;
            }
            
            Pos parent_pos      = _parent->pos();
            Size parent_size    = _parent->size();

            Animation_frame* f = _frames.current();

            if (f == NULL) {
                std::cout << "animation frame is null " << std::endl;
                return;
            }
            
            Size target_size    = Size(parent_size.w, 0) + Size(f->orig_size.w, f->orig_size.h);

            set_size(target_size);

            std::cout << "target size: " << target_size.w << " " << target_size.h << std::endl; 

            _frames.set_tex_repeat(true);

            _valid = true;
        }
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
    }
}