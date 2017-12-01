#include "wst_worldobj.h"

namespace wst {
    World_obj::World_obj() {}

    void World_obj::set_pos(Pos& p) { _pos = p; }
    void World_obj::set_rect(Rect& r) { _rect = r; }

    Pos World_obj::pos() { return _pos; }
    Rect World_obj::rect() { return _rect; }
    
}