#include "wst_screenrenderobj.h"

namespace wst {
    Screen_render_obj::Screen_render_obj(const std::string& prefix_path, int num_frames) {
        load(prefix_path, num_frames);
        _timer = 0;
    }

    Screen_render_obj::Screen_render_obj() {
        _timer = 0;
    }

    void Screen_render_obj::load(const std::string& prefix_path, int num_frames) {
        _frames.load(prefix_path, num_frames);

        sf::IntRect rect = _frames.current()->drawable().getTextureRect();

        _size.w = rect.width;
        _size.h = rect.height;
    }

    void Screen_render_obj::render(double delta, sf::RenderTarget* target) {
        //std::cout << "delta: " << delta << " timer: " << _timer << std::endl;
        
        _timer += delta;

        if (_timer > 0.100) {
            _frames.next();
            _timer = 0;
        }
        
        Pos p = abs_pos();

        _frames.current()->drawable().setPosition((float)p.x, (float)p.y);

        target->draw(_frames.current()->drawable());
    }

    void Screen_render_obj::set_fill(FillScene prop) { 
        _fill_prop = prop; 
    }

    FillScene Screen_render_obj::get_fill() { 
        return _fill_prop; 
    }

    void Screen_render_obj::update() {
        if (_fill_prop == FillScene_Repeat_x) {
            Pos parent_pos      = _parent->pos();
            Size parent_size    = _parent->size();
        }
    }

}