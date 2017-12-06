#include "config.h"
#include "wst_animation.h"
#include "wst_screenrenderobj.h"
#include "wst_player_character.h"
#include "wst_input_action.h"
#include "wst_timer.h"
#include "wst_trace.h"
#include "wst_json_resource.h"
#include "wst_main.h"
#include "wst_asset_manager.h"
#include "json11.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <ctime>

using namespace std;
using namespace wst;

int main(int argc, char* argv[]) {
    TRACE("starting application\n");

    Asset_manager::ROOT_FOLDER = "resources/";
    Main g(Asset_manager::ROOT_FOLDER + "main.json");
    if (!g.init()) {
        LOG("error: failed to init main.json\n");
        return 0;
    }

    //std::cout << "horse id: " << json_horse["id"].string_value() << " " << json_horse["animation"].string_value() << " " << json_horse["type"].string_value() << std::endl;

    /*char animation_filepath[256];
    int num_frames = json_horse["num_frames"].int_value();

    sprintf(animation_filepath, "%s%s", _resource_path.c_str(), json_horse["animation"].string_value().c_str());
*/
    char app_version[128];
    char app_title[128];

    sprintf(app_version, "ALPHA %d.%d.%d", western_VERSION_MAJOR, western_VERSION_MINOR, western_VERSION_PATCH);
    sprintf(app_title, "Western Game %s", app_version);

    cout << "Version " << app_version << endl;

    int screen_width = 800;
    int screen_height = 600;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height, 32), app_title);

    /*Screen_render_obj* horse = new Screen_render_obj("horse", animation_filepath, num_frames);
    horse->set_pos(Pos(0,0));
    horse->set_reversed(true);
    horse->set_framerate(0.1);*/
    /*
    Game_scene first_scene;
    first_scene.set_pos(Pos(0,0));
    first_scene.set_rect(Rect(0, 0, screen_width, screen_height));
    first_scene.set_clipping_rect(Rect(0, 0, screen_width, screen_height));
    
    // ----- THE SKY ------ / 
    Scene_layer* sky_layer = new Scene_layer("sky", true);
    Screen_render_obj* sky = new Screen_render_obj("sky", _resource_path + "sky_horizon", 1);
    
    sky->set_pos(Pos(0,0));
    
    sky_layer->set_pos(Pos(0,0));
    sky_layer->set_size(Size(screen_width, screen_height));
    sky_layer->add_render_obj(sky);
    
    std::cout << "setting fill" << std::endl;
    std::cout << "done" << std::endl;
    
    
    // ----- THE GROUND ----- /
    Scene_layer* ground_layer = new Scene_layer("ground", true);
    Screen_render_obj* ground = new Screen_render_obj("ground", _resource_path + "ground_repeat", 1);
    ground->set_pos(Pos(0,0));
    ground_layer->add_render_obj(ground);
    ground_layer->set_pos(Pos(0,190));

    first_scene.add_layer(sky_layer);
    first_scene.add_layer(ground_layer);

    sky->set_fill(FillScene_Repeat_x);
    sky->update();
    
    ground->set_fill(FillScene_Repeat_x);
    ground->update();
    //ground_layer->add_render_obj(horse);
    

    Player_character player(_resource_path + "exwalk", 8);
    player.set_pos(Pos(10,10));*/

    Timer tmr;

    double elapsed = 0.0;

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

        elapsed += delta;

        tmr.reset();

        //player.render(delta, (sf::RenderTarget*)&window);
        /*first_scene.render(delta, (sf::RenderTarget*)&window);

        if (elapsed > 0.025) {
            Pos p = ground->pos();
            ground->set_pos(p + Pos(-1,0));
            elapsed = 0;

        }*/

        //horse->render(delta, (sf::RenderTarget*)&window);
        //Pos p = ground_layer->pos();
        //p.x += 1;
        //ground_layer->set_pos(p);

        window.display();
    }

    return 0;
}