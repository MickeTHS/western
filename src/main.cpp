#include "config.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

enum GameAction {
  NONE = 0,
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  DRAW_HOLSTER_WEAPON,
  UNCOCK_COCK_WEAPON,
  LOAD_WEAPON,
  UNLOAD_WEAPON,
  FIRE_WEAPON,
  MOUNT_DISMOUNT,
  INTERACT,
  LOOT,
  DROP,
  UNEQUIP_EQUIP,
  TALK,
  MAX_ACTION
};

void key_pressed(sf::Keyboard::Key key, GameAction& result) {
  switch(key) {
    case sf::Keyboard::Key::A:
      result = MOVE_LEFT;
      break;
    case sf::Keyboard::Key::S:
      result = MOVE_DOWN;
      break;
    case sf::Keyboard::Key::D:
      result = MOVE_RIGHT;
      break;
    case sf::Keyboard::Key::W:
      result = MOVE_UP;
      break;
    case sf::Keyboard::Key::Q:
      result = UNCOCK_COCK_WEAPON;
      break;
    case sf::Keyboard::Key::E:
      result = LOAD_WEAPON;
      break;
    case sf::Keyboard::Key::R:
      result = UNLOAD_WEAPON;
      break;
    case sf::Keyboard::Key::Return:
      result = INTERACT;
      break;
    case sf::Keyboard::Key::Space:
      result = MOUNT_DISMOUNT;
      break;
    case sf::Keyboard::Key::Tab:
      result = DRAW_HOLSTER_WEAPON;
      break;
    default:
      result = NONE;
      break;
  }
} 

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
  
  AnimationFrames frames(_resource_path + "exwalk", 8);

  sf::Sprite sprite;

  sf::Clock clock; // starts the clock

  GameAction action = NONE;
  GameAction prev_action = NONE;
  while (App.isOpen()) {
    sf::Event event;

    while (App.pollEvent(event)) {
      
      switch (event.type)
      {
        // window closed
        case sf::Event::Closed:
          App.close();
          break;

        // key pressed
        case sf::Event::KeyPressed:
          key_pressed(event.key.code, action);
          if (prev_action != action) {
            std::cout << "queued action: " << action << std::endl;
            prev_action = action;
          }
          break;
        default:
          break;
      }
    }

    sf::Time elapsed1 = clock.getElapsedTime();
    if (elapsed1.asMilliseconds() > 100) {
      sprite.setTexture(frames.current()->tex);  
      clock.restart();
    }

    App.draw(sprite);
    App.display();
  }
}
