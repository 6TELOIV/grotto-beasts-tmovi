#ifndef GB_BATTLE_SCENE_CURSOR_H
#define GB_BATTLE_SCENE_CURSOR_H

// Dependencies
#include "gb_battle_scene_constants.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

// Graphics
#include "bn_sprite_items_cursor.h"

namespace gb
{
    namespace battle {
        
        constexpr bn::fixed_point cursor_playmat_locations[playmat_spaces] = {
            {-90, 10},
            {-60, 10},
            {-30, 10},
            {0, 10},
            {30, 10},
            {60, 10},
            {90, 10},
            {-84, -12},
            {-56, -12},
            {-28, -12},
            {0, -12},
            {28, -12},
            {56, -12},
            {84, -12},
            {-78, -40},
            {-52, -40},
            {-26, -40},
            {0, -40},
            {26, -40},
            {52, -40},
            {78, -40},
            {-72, -58},
            {-48, -58},
            {-24, -58},
            {0, -58},
            {24, -58},
            {48, -58},
            {72, -58},
        };

        constexpr int hand_location_count = 5;
        constexpr bn::fixed_point cursor_hand_locations[hand_location_count] = {
            {8, 40},
            {32, 40},
            {56, 40},
            {80, 40},
            {104, 40},
        };
        

        struct cursor
        {
            int playmat_x;
            int playmat_y;
            bool in_hand;
            int hand_index;
            int hand_offset;
            bn::sprite_ptr sprite;

            cursor();

            void move_up();

            void move_down();

            void move_right();

            void move_left();
        };
 
    }
}

#endif