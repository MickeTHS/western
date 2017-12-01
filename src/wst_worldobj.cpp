#include "wst_worldobj.h"

namespace wst {
    World_obj::World_obj() {}

    void World_obj::set_rect(Rect& r) { _rect = r; }

    Rect World_obj::rect() { return _rect; }
    
}