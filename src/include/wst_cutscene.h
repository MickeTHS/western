#pragma once

#include "wst_json_resource.h"
#include "wst_trace.h"

#include <string>
#include <vector>

using namespace std;

namespace wst {
    struct Frame {
        Frame(int time, const string& object_id, const string& action);

        int     _time;
        string  _object_id;
        string  _action;
    };

    struct Cutscene : public Json_resource {
        Cutscene(const string& filepath);

        bool init();
        Resource_type type();

        bool    _skippable;
        string  _next_scene;
        string  _type;

        vector<string> _asset_ids;
        vector<Frame*> _frames;
    };
}