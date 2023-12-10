#ifndef GB_BATTLE_SCENE_STATE_H
#define GB_BATTLE_SCENE_STATE_H

// Dependencies
#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_unique_ptr.h"
#include "gb_battle_scene_cards.h"
#include "gb_battle_scene_cursor.h"
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

        int sideline[sideline_size];
        int team[team_size];

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

        void draw_card();
        void shuffle_deck();
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

    struct state
    {
        state();

        player_state player;
        player_state opponent;
        turn current_turn;
        phase current_phase;

        bn::regular_bg_ptr playmat;
        bn::unique_ptr<cards> cards_ptr;
        bn::unique_ptr<cursor> cursor_ptr;

        bn::random rng;

        void draw_player_card();
        void draw_opponent_card();

        void update();
    };
}

#endif
