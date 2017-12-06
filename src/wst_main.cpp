#include "wst_main.h"
#include "wst_asset_manager.h"


namespace wst {
    Game::Game(const string& title, const string& resourcepath) : Json_resource(resourcepath) {
        TRACE("game contructor: %s\n", resourcepath.c_str());
    }

    bool Game::init() {
        Json_resource::init();
        /*{
    "id":"maingame",
    "mode":"story",
    "next_scene":"scenes/intro.json",
    "player":"characters/player.json"
}*/

        LOG("parsing '%s'...\n", _filename.c_str());    

        
        if (!valid_string(json, "mode")) { return false; }
        if (!valid_string(json, "next_scene")) { return false; }
        if (!valid_string(json, "player")) { return false; }


        string next_scene = Asset_manager::ROOT_FOLDER + json["next_scene"].string_value();
        _mode       = json["mode"].string_value();
        _player     = json["player"].string_value();

        TRACE("Game: next_scene: %s\n", next_scene.c_str());


        _next_scene = make_shared<Scene>(next_scene);

        if (!_next_scene->init()) {
            LOG("error: failed to init next_scene '%s' in Game \n", next_scene.c_str());
        }

        Pos_graph_node::root()->add(_next_scene);

        return true;
    }

    Resource_type Game::type() {
        return RES_GAMEDEF;
    }


    Main::Main(const std::string& gamefilepath) : Json_resource(gamefilepath) {
        
    }

    bool Main::init() {
        LOG("main init %s...\n", _filename.c_str());

        if (!valid_string(json, "intro")) { return false; }
        if (!valid_array(json, "games")) { return false; }

        _intro = json["intro"].string_value();

        auto games = json["games"].array_items();

        for (size_t i = 0; i < games.size(); ++i) {
            if (!valid_string(games[i], "title")) { return false; }
            if (!valid_string(games[i], "file")) { return false; }
            
            string title = games[i]["title"].string_value();
            string file = games[i]["file"].string_value();

            TRACE("parsed title: %s, file: %s\n", title.c_str(), file.c_str());

            shared_ptr<Game> game = make_shared<Game>(title, Asset_manager::ROOT_FOLDER + file);

            if (!game->init()) {
                LOG("error: unable to initiate game %s\n", file.c_str());
                return false;
            }

            _games.push_back(game);
        }

        return true;
    }

    Resource_type Main::type() {
        return RES_MAIN;
    }
}