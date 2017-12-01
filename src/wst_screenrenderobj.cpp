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
}