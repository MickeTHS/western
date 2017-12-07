#pragma once

#include <SFML/Window.hpp>

#include <string>
#include <vector>
#include <memory>

#include "wst_json_resource.h"
#include "wst_types.h"
#include "wst_scene.h"
#include "wst_timer.h"

using namespace std;

namespace wst {
    struct Game : public Json_resource {
        Game(const string& title, const string& resourcepath);

        bool init();
        Resource_type type();
        bool create();
        bool start();

        void render(sf::RenderTarget* target);

        string _title;

        string _mode;
        string _player;

        shared_ptr<Scene> _next_scene;

        shared_ptr<Scene> _running_scene;

        Timer _tmr;

        double _elapsed;

    };

    struct Main : public Json_resource {
        Main(const string& gamefilepath);

        bool init();
        bool create_game(const char* game);
        Resource_type type();

        void render(sf::RenderTarget* target);

        string _intro;

        vector<shared_ptr<Game>> _games;

        shared_ptr<Game> _running_game;
    };
}