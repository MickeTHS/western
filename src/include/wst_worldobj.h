/**
 * A world object is an object in the world
 * it has properties which could be interacted with
 * it has a world position
 * 
 * the player_character is a world object?
*/

#pragma once

namespace wst {
    struct Rect {
        Rect() { left = 0; top = 0; width = 0; height = 0; }
        Rect(int left, int top, int width, int height) {
            this->left   = left;
            this->top    = top;
            this->width  = width;
            this->height = height;
        }

        int left, top, width, height;
    };

    struct Pos {
        Pos(int x, int y) { this->x = x; this->y = y; }
        Pos() { x = 0; y = 0; }

        int x; // negative is left, positive is right
        int y; // negative is down, positive is up
    };


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