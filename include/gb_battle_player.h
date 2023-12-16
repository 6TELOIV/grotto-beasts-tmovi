#ifndef GB_BATTLE_PLAYER_H
#define GB_BATTLE_PLAYER_H

#include "bn_random.h"

namespace gb::battle {
    constexpr int team_size = 5;
    constexpr int sideline_size = 5;
    constexpr int max_deck_size = 256;
    struct player
    {
        player() = default;

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

        int hand_indices[max_deck_size];
        int selected_cards_size;

        void draw_card();
        void shuffle_deck(bn::random rng);
        int pop_hand_card(int hand_index);
    };
}

#endif