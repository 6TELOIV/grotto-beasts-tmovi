#include "gb_battle_scene_state.h"

// Graphics
#include "bn_regular_bg_items_playmat.h"

namespace gb::battle
{
    state::state() : player(this),
                     opponent(this),
                     playmat(bn::regular_bg_items::playmat.create_bg(8, 48)),
                     cards_ptr(bn::unique_ptr(new cards())),
                     cursor_ptr(bn::unique_ptr(new cursor()))
    {
        // phase/turn
        current_turn = rng.get_int() % 2 == 0 ? PLAYER : OPPONENT;
        current_phase = START_OF_TURN;

        // player
        player.current_deck_size = 4;
        player.current_discard_size = 0;
        player.current_hand_size = 0;
        player.current_scored_size = 0;
        for (int i = 0; i < player.current_deck_size; i++)
        {
            player.deck[i] = i;
        }
        player.shuffle_deck();

        // opponent
        opponent.current_deck_size = 4;
        opponent.current_discard_size = 0;
        opponent.current_hand_size = 0;
        opponent.current_scored_size = 0;
        for (int i = 0; i < opponent.current_deck_size; i++)
        {
            player.deck[i] = i;
        }
        opponent.shuffle_deck();

        // deal cards
        for (int i = 0; i < 1; i++)
        {
            draw_player_card();
        }

        for (int i = 0; i < 1; i++)
        {
            draw_opponent_card();
        }
    }

    void state::draw_player_card()
    {
        player.draw_card();
        if (player.current_deck_size * 2 > player.deck_size)
        {
            cards_ptr->show_player_deck_full();
        }
        else
        {
            cards_ptr->hide_player_deck();
        }
    }

    void state::draw_opponent_card()
    {
        opponent.draw_card();
        if (opponent.current_deck_size * 2 > opponent.deck_size)
        {
            cards_ptr->show_opponent_deck_full();
        }
        else
        {
            cards_ptr->hide_opponent_deck();
        }
    }

    void state::update()
    {
        if (bn::keypad::up_pressed())
        {
            cursor_ptr->move_up();
        }
        if (bn::keypad::down_pressed())
        {
            cursor_ptr->move_down();
        }
        if (bn::keypad::left_pressed())
        {
            cursor_ptr->move_left();
        }
        if (bn::keypad::right_pressed())
        {
            cursor_ptr->move_right();
        }

        if (bn::keypad::a_pressed())
        {
            cards_ptr->show_card(cursor_ptr->playmat_x, cursor_ptr->playmat_y);
        }

        if (bn::keypad::b_pressed())
        {
            cards_ptr->hide_card(cursor_ptr->playmat_x, cursor_ptr->playmat_y);
        }
    }

    player_state::player_state(state *state) : parent_state(state) {}

    void player_state::draw_card()
    {
        hand[current_hand_size++] = deck[--current_deck_size];
    }

    // Fisher-Yates shuffle algorithm
    void player_state::shuffle_deck()
    {
        for (int i = deck_size - 1; i > 0; i--)
        {
            int j = parent_state->rng.get_int(i);
            // swap the values
            int temp = deck[j];
            deck[j] = deck[i];
            deck[i] = temp;
        }
    }
}