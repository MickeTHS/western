#pragma once

#include <memory>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace wst {

    enum Game_action {
        NONE = 0,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        DRAW_HOLSTER_WEAPON,
        UNCOCK_COCK_WEAPON,
        LOAD_WEAPON,
        UNLOAD_WEAPON,
        FIRE_WEAPON,
        MOUNT_DISMOUNT,
        INTERACT,
        LOOT,
        DROP,
        UNEQUIP_EQUIP,
        TALK,
        MAX_ACTION
    };

    struct Input_action_handler {
        
        Input_action_handler(Input_action_handler const&) = delete;
        Input_action_handler& operator=(Input_action_handler const&) = delete;

        static std::shared_ptr<Input_action_handler> instance()
        {
            static std::shared_ptr<Input_action_handler> s{new Input_action_handler};
            return s;
        }

        void handle_key_input(sf::Keyboard::Key key, Game_action& result);

    private:
        Input_action_handler() {}
    };
}