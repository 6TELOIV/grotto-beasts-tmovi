#ifndef GB_BATTLE_SCENE_STATE_H
#define GB_BATTLE_SCENE_STATE_H

// Dependencies
#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_unique_ptr.h"
#include "gb_battle_scene_cards_graphics.h"
#include "gb_battle_scene_cursor.h"
#include "gb_battle_scene_context_menu.h"
#include "bn_keypad.h"
#include "bn_random.h"

namespace gb::battle
{
    struct state;
    struct player_state;

    constexpr int max_deck_size = 128;
    constexpr int team_size = 5;
    constexpr int sideline_size = 5;
    struct player_state
    {
        player_state(state *state);
        state *parent_state;

        int sideline[sideline_size] = { -1, -1, -1, -1, -1};
        int team[team_size] = { -1, -1, -1, -1, -1};

        int hand[max_deck_size];
        int current_hand_size;
        int hand_size;

        int scored[max_deck_size];
        int current_scored_size;

        int deck[max_deck_size];
        int current_deck_size;
        int deck_size;

        int discard[max_deck_size];
        int current_discard_size;

        int selected_cards[max_deck_size];
        int selected_cards_size;

        void draw_card();
        void shuffle_deck();

        void play_team(int hand_index, int slot);
        void play_sideline(int hand_index, int slot);

    private:
        int _pop_hand_card(int hand_index);
    };

    enum turn
    {
        PLAYER,
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

    struct state
    {
        state();

        player_state player;
        player_state opponent;
        turn current_turn;
        phase current_phase;
        action current_action = NONE;

        bn::regular_bg_ptr playmat;
        bn::unique_ptr<cards_graphics> cards_ptr;
        bn::unique_ptr<cursor> cursor_ptr;
        bn::unique_ptr<context_menu> context_menu_ptr;

        bn::random rng;

        // In player hand at y=0; otherwise, on board
        int cursor_x = 3, cursor_y = 2;
        int hand_offset;

        void move_cursor(directions d);
        void open_menu(menu_item options[], int options_length);
        void move_menu(directions d);
        void draw_player_cards(int count);
        void draw_opponent_cards(int count);
        void summon_player_sideine();
        void summon_player_team();

        void update();
    };
}

#endif
