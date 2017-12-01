/**
 * A world object is an object in the world
 * it has properties which could be interacted with
 * it has a world position
 *
 * the player_character is a world object?
*/

#pragma once

#include "wst_types.h"

namespace wst {
    struct World_obj {
        World_obj();

        void set_pos(Pos& p);
        void set_rect(Rect& r);

        Pos pos();
        Rect rect();

        Pos _pos;
        Rect _rect;
    };
}