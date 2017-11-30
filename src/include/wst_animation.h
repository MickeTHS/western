#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


struct Wst_Animation_frame {
  Wst_Animation_frame(const std::string& path);

  sf::Texture tex;
};

struct Wst_Animation_frames {
  Wst_Animation_frames(const std::string& prefix_path, int num_frames);

  Wst_Animation_frame* current();

private:
  std::vector<Wst_Animation_frame*> _frames;
  int _current_frame;

};
