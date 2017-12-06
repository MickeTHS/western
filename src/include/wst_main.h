#pragma once

#include <string>
#include <vector>
#include <memory>

#include "wst_json_resource.h"
#include "wst_types.h"
#include "wst_scene.h"

using namespace std;

namespace wst {
    struct Game : public Json_resource {
        Game(const string& title, const string& resourcepath);

        bool init();
        Resource_type type();

        string _title;

        string _mode;
        string _player;

        shared_ptr<Scene> _next_scene;
    };

    struct Main : public Json_resource {
        Main(const string& gamefilepath);

        bool init();
        Resource_type type();

        string _intro;

        vector<shared_ptr<Game>> _games;
    };
}