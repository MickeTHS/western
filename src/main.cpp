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
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <ctime>

using namespace std;
using namespace wst;

int main(int argc, char* argv[]) {

    /* Code adapted from the SFML 2 "Window" example */

    std::string _resource_path = "resources/";

    char app_version[128];
    char app_title[128];

    sprintf(app_version, "ALPHA %d.%d.%d", western_VERSION_MAJOR, western_VERSION_MINOR, western_VERSION_PATCH);
    sprintf(app_title, "Western Game %s", app_version);

    cout << "Version " << app_version << endl;

    int screen_width = 800;
    int screen_height = 600;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height, 32), app_title);

    Game_scene first_scene;
    first_scene.set_pos(Pos(0,0));
    first_scene.set_rect(Rect(0, 0, screen_width, screen_height));
    first_scene.set_clipping_rect(Rect(0, 0, screen_width, screen_height));
    
    // ----- THE SKY ------ / 
    Scene_layer* sky_layer = new Scene_layer("sky", true);
    Screen_render_obj* sky = new Screen_render_obj(_resource_path + "sky_horizon", 1);
    sky->set_pos(Pos(0,0));
    sky_layer->add_render_obj(sky);
    sky_layer->set_pos(Pos(0,0));

    // ----- THE GROUND ----- /
    Scene_layer* ground_layer = new Scene_layer("ground", true);
    Screen_render_obj* ground = new Screen_render_obj(_resource_path + "ground_repeat", 1);
    ground->set_pos(Pos(0,0));
    ground_layer->add_render_obj(ground);
    ground_layer->set_pos(Pos(0,180));

    first_scene.add_layer(sky_layer);
    first_scene.add_layer(ground_layer);
    
    Player_character player(_resource_path + "exwalk", 8);
    player.set_pos(Pos(10,10));

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

        double delta = tmr.elapsed();
        tmr.reset();

        //player.render(delta, (sf::RenderTarget*)&window);
        first_scene.render(delta, (sf::RenderTarget*)&window);

        Pos p = ground_layer->pos();
        p.x += 1;
        ground_layer->set_pos(p);

        window.display();
    }

    return 0;
}