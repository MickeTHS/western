#include "config.h"
#include "wst_animation.h"
#include "wst_screenrenderobj.h"
#include "wst_player_character.h"
#include "wst_input_action.h"
#include "wst_gamescene.h"
#include "wst_timer.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <ctime>

using namespace std;
using namespace wst;

int main(int argc, char* argv[]) {

    /* Code adapted from the SFML 2 "Window" example */

    std::string _resource_path = "resources/";

    cout << "Version " << western_VERSION_MAJOR << "." << western_VERSION_MINOR << endl;

    int screen_width = 800;
    int screen_height = 600;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height, 32), "western alpha");

    Game_scene first_scene;
    //first_scene.add_layer()
    Scene_layer* first_layer = new Scene_layer("ground", true);
    first_scene.add_layer(first_layer);
    Screen_render_obj* obj = new Screen_render_obj(_resource_path + "ground", 1);
    obj->set_pos(Pos(200,200));
    
    
    Player_character player(_resource_path + "exwalk", 8);
    player.set_pos(Pos(10,10));


    first_layer->add_render_obj(&player);
    first_layer->add_render_obj(obj);


    //sf::Clock clock; // starts the clock
    Timer tmr;

    Game_action action = NONE;
    Game_action prev_action = NONE;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                window.close();
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

        window.clear(sf::Color::Black);

        

        //double delta = double(end - begin) / CLOCKS_PER_SEC;

        double delta = tmr.elapsed();
        tmr.reset();
        //double delta = (delta / 1000.0f);

        //player.render(delta, (sf::RenderTarget*)&window);
        first_scene.render(delta, (sf::RenderTarget*)&window);

        //begin = end;
        //    clock.restart();

            //App.draw(sprite.);
        window.display();
    }

}
