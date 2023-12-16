#ifndef GB_BATTLE_SCENE_H
#define GB_BATTLE_SCENE_H

// Dependencies
#include "bn_core.h"
#include "bn_math.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_format.h"
#include "bn_string_view.h"

#include "gb_scene.h"
#include "gb_battle_player.h"
#include "gb_battle_cards_graphics.h"
#include "gb_battle_cursor.h"
#include "gb_battle_context_menu.h"
#include "gb_battle_cards_graphics.h"
#include "gb_battle_cursor.h"

// Graphics
#include "bn_regular_bg_items_playmat.h"

namespace gb::battle
{

    enum turn
    {
        ACTOR,
        OPPONENT
    };

    enum phase
    {
        START_OF_TURN,
        FIRST_ACTION,
        BATTLE,
        SECOND_ACTION,
        END_OF_TURN
    };

    struct directions
    {
        unsigned up : 1;
        unsigned down : 1;
        unsigned left : 1;
        unsigned right : 1;
    };

    enum action
    {
        LOCKED,
        NONE,
        SUMMONING,
        NUM_ACTIONS
    };

    class battle_scene : public scene
    {
    public:
        battle_scene();
        void update();

    private:
        player actor;
        player opponent;
        turn current_turn;
        phase current_phase;
        action current_action = NONE;

        bn::regular_bg_ptr playmat;
        bn::unique_ptr<cards_graphics> cards_graphics_ptr;
        bn::unique_ptr<cursor> cursor_ptr;
        bn::unique_ptr<context_menu> context_menu_ptr;

        bn::random rng;

        // In player hand at y=0; otherwise, on board
        int cursor_x = 3, cursor_y = 2;
        int hand_offset;

        void move_cursor(directions d);
        
        void open_menu(menu_item options[], int options_length);
        void move_menu(directions d);

        void draw_actor_cards(int count);
        void draw_opponent_cards(int count);

        void open_sumon_menu();
        void summon_actor(int summon_location[]);
    };
}

#endif
