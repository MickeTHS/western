#include "wst_main.h"

namespace wst {
    Game::Game(const string& resourcepath) : Json_resource(resourcepath) {

    }

    bool Game::init() {
        return true;
    }

    Resource_type Game::type() {
        return RES_GAMEDEF;
    }


    Main::Main(const std::string& gamefilepath) : Json_resource(gamefilepath) {

    }

    bool Main::init() {
        if (!json["intro"].is_string()) {
            LOG("error: 'intro' not set in main.json");
            return false;
        }
        
        intro = json["intro"].string_value();

        return true;
    }

    Resource_type Main::type() {
        return RES_MAIN;
    }
}