#include "wst_input_action.h"

namespace wst {
    void Input_action_handler::handle_key_input(sf::Keyboard::Key key, Game_action& result) {
        switch(key) {
            case sf::Keyboard::Key::A:
                result = MOVE_LEFT;
                break;
            case sf::Keyboard::Key::S:
                result = MOVE_DOWN;
                break;
            case sf::Keyboard::Key::D:
                result = MOVE_RIGHT;
                break;
            case sf::Keyboard::Key::W:
                result = MOVE_UP;
                break;
            case sf::Keyboard::Key::Q:
                result = UNCOCK_COCK_WEAPON;
                break;
            case sf::Keyboard::Key::E:
                result = LOAD_WEAPON;
                break;
            case sf::Keyboard::Key::R:
                result = UNLOAD_WEAPON;
                break;
            case sf::Keyboard::Key::Return:
                result = INTERACT;
                break;
            case sf::Keyboard::Key::Space:
                result = MOUNT_DISMOUNT;
                break;
            case sf::Keyboard::Key::Tab:
                result = DRAW_HOLSTER_WEAPON;
                break;
            default:
                result = NONE;
                break;
        }
    }
}