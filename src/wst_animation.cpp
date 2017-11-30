#include "wst_animation.h"

Wst_Animation_frame::Wst_Animation_frame(const std::string& path) {
    if (!tex.loadFromFile(path)) {
        std::cout << "unable to load " << path << std::endl;
        exit(0);
    }
}


Wst_Animation_frames::Wst_Animation_frames(const std::string& prefix_path, int num_frames) {
    for (int i = num_frames-1; i >= 0; --i) {
        _frames.push_back(new Wst_Animation_frame(prefix_path + std::to_string(i) + ".png"));
    }
    _current_frame = 0;
}

Wst_Animation_frame* Wst_Animation_frames::current() {
    Wst_Animation_frame* f = _frames[_current_frame];

    _current_frame++;

    if (_current_frame >= _frames.size()) {
        _current_frame = 0;
    }

    return f;
  }