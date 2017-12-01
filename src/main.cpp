#include "config.h"
#include "wst_animation.h"
#include "wst_screenrenderobj.h"
#include "wst_player_character.h"
#include "wst_input_action.h"
#include "wst_gamescene.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace wst;

int main(int argc, char* argv[]) {

  /* Code adapted from the SFML 2 "Window" example */

  std::string _resource_path = "resources/";

  cout << "Version " << western_VERSION_MAJOR << "." << western_VERSION_MINOR << endl;

  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "western alpha");
  
  Game_scene first_scene;
  //first_scene.add_layer()
  Scene_layer* first_layer = new Scene_layer("ground1", true);
  first_scene.add_layer(first_layer);
  Screen_render_obj* obj = new Screen_render_obj(_resource_path + "ground", 1);
  first_layer->add_render_obj(obj);

  Player_character player(_resource_path + "exwalk", 8);

  sf::Sprite sprite;

  sf::Clock clock; // starts the clock
  
  Game_action action = NONE;
  Game_action prev_action = NONE;
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

          Input_action_handler::instance()->handle_key_input(event.key.code, action);

          if (prev_action != action) {
            std::cout << "queued action: " << action << std::endl;
            prev_action = action;
          }
          break;
        default:
          break;
      }
    }

    double delta = clock.getElapsedTime().asMilliseconds();


    player.render(delta, (sf::RenderTarget*)&App);

    clock.restart();
    
    //App.draw(sprite.);
    App.display();
  }
}
