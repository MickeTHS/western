#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace wst {
  struct Animation_frame {
    Animation_frame(const std::string& path);
    sf::Drawable& drawable();

    sf::Texture tex;
    sf::Sprite sprite;
  };

  struct Animation_frames {
    Animation_frames(const std::string& prefix_path, int num_frames);
    Animation_frames();

    void load(const std::string& prefix_path, int num_frames);

    Animation_frame* next();
    Animation_frame* current();

  private:
    std::vector<Animation_frame*> _frames;
    int _current_frame;

  };

}
