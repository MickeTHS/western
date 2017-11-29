#include "config.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

struct AnimationFrame {
  AnimationFrame(const std::string& path) {
    if (!tex.loadFromFile(path)) {
      std::cout << "unable to load " << path << std::endl;
      exit(0);
    }
  }

  sf::Texture tex;
};

struct AnimationFrames {
  AnimationFrames(const std::string& prefix_path, int num_frames) {
    for (int i = num_frames-1; i >= 0; --i) {
      _frames.push_back(new AnimationFrame(prefix_path + std::to_string(i) + ".png"));
    }
    _current_frame = 0;
  }

  AnimationFrame* current() {
    AnimationFrame* f = _frames[_current_frame];

    _current_frame++;

    if (_current_frame >= _frames.size()) {
      _current_frame = 0;
    }

    return f;
  }

  std::vector<AnimationFrame*> _frames;
  int _current_frame;

};

int main(int argc, char* argv[]) {

  /* Code adapted from the SFML 2 "Window" example */

  std::string _resource_path = "resources/";

  cout << "Version " << western_VERSION_MAJOR << "." << western_VERSION_MINOR << endl;

  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "western alpha");
  
  AnimationFrames frames(_resource_path + "walk", 8);

  sf::Sprite sprite;

  sf::Clock clock; // starts the clock

  while (App.isOpen()) {
    sf::Event Event;
    while (App.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed) {
        App.close();
      }
    }

    sf::Time elapsed1 = clock.getElapsedTime();
    if (elapsed1.asMilliseconds() > 150) {
      sprite.setTexture(frames.current()->tex);  
      clock.restart();
    }

    App.draw(sprite);
    App.display();
  }
}
