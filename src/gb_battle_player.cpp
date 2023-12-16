#include "gb_battle_player.h"

namespace gb::battle {
    void player::draw_card()
    {
        hand[current_hand_size++] = deck[--current_deck_size];
    }

    int player::pop_hand_card(int hand_index)
    {
        int theCard = hand[hand_index];
        for (int i = hand_index; i < current_hand_size + 1; i++)
        {
            hand[i] = hand[i + 1];
        }
        current_hand_size--;
        return theCard;
    }

    // Fisher-Yates shuffle algorithm
    void player::shuffle_deck(bn::random rng)
    {
        for (int i = deck_size - 1; i > 0; i--)
        {
            int j = rng.get_int(i);
            // swap the values
            int temp = deck[j];
            deck[j] = deck[i];
            deck[i] = temp;
        }
    }
}