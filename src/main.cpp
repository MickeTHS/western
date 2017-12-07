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

    char app_version[128];
    char app_title[128];

    sprintf(app_version, "ALPHA %d.%d.%d", western_VERSION_MAJOR, western_VERSION_MINOR, western_VERSION_PATCH);
    sprintf(app_title, "Western Game %s", app_version);

    LOG("%s\n", app_title); 

    Asset_manager::ROOT_FOLDER = "resources/";
    Main g(Asset_manager::ROOT_FOLDER + "main.json");
    if (!g.init()) {
        LOG("error: failed to init main.json\n");
        return 0;
    }
    
    int screen_width = 800;
    int screen_height = 600;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height, 32), app_title);

    Timer tmr;

    double elapsed = 0.0;

    Game_action action = NONE;
    Game_action prev_action = NONE;

    if (!g.create_game("maingame")) {
        LOG("error: unable to create maingame\n");
        return 0;
    }

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

        g.render((sf::RenderTarget*)&window);

        window.display();
    }

    return 0;
}