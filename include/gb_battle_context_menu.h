#ifndef GB_BATTLE_CONTEXT_MENU_H
#define GB_BATTLE_CONTEXT_MENU_H

// Dependencies
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_unique_ptr.h"

#include "gb_battle_constants.h"

// Graphics
#include "bn_sprite_items_context_buttons.h"

namespace gb::battle
{
    constexpr bn::fixed_point menu_locations[playmat_spaces + player_hand_slots + 3] = {
        {24, 40},
        {48, 40},
        {72, 40},
        {96, 40},
        {0, 0},
        {0, 0},
        {0, 0},
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

    enum menu_item
    {
        VIEW = 0,
        SUMMON,
        ACTIVATE,
        SELECT
    };

    struct context_menu
    {
        int options_length;
        bn::sprite_ptr selection;
        menu_item options[4];
        int selected_option = 0;
        bn::unique_ptr<bn::sprite_ptr> sprite_ptrs[4];

        context_menu(int x, int y, menu_item items[], int item_count);
        void move_up();
        void move_down();
        menu_item get_selected();
    };
}

#endif