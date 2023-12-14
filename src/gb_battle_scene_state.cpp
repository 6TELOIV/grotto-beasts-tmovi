#include "gb_battle_scene_state.h"

// Graphics
#include "bn_regular_bg_items_playmat.h"

namespace gb::battle
{
    state::state() : player(this),
                     opponent(this),
                     playmat(bn::regular_bg_items::playmat.create_bg(8, 48)),
                     cards_ptr(bn::unique_ptr(new cards_graphics())),
                     cursor_ptr(bn::unique_ptr(new cursor()))
    {
        // phase/turn
        current_turn = rng.get_int() % 2 == 0 ? PLAYER : OPPONENT;
        current_phase = START_OF_TURN;

        // player
        player.deck_size = 60;
        player.current_deck_size = player.deck_size;
        player.current_discard_size = 0;
        player.current_hand_size = 0;
        player.current_scored_size = 0;
        for (int i = 0; i < player.current_deck_size; i++)
        {
            player.deck[i] = i;
        }
        player.shuffle_deck();

        // opponent
        opponent.deck_size = 60;
        opponent.current_deck_size = opponent.deck_size;
        opponent.current_discard_size = 0;
        opponent.current_hand_size = 0;
        opponent.current_scored_size = 0;
        for (int i = 0; i < opponent.current_deck_size; i++)
        {
            opponent.deck[i] = i;
        }
        opponent.shuffle_deck();

        // deal cards
        draw_player_cards(6);
        draw_opponent_cards(6);
    }

    void state::move_menu(directions d)
    {
        if (d.up)
        {
            context_menu_ptr->move_up();
        }
        else if (d.down)
        {
            context_menu_ptr->move_down();
        }
    }

    void state::draw_player_cards(int amount)
    {
        for (int i = 0; i < amount; i++)
            player.draw_card();

        cards_ptr->show_player_hand(player.hand, player.current_hand_size, hand_offset);
        if (player.current_deck_size * 2 > player.deck_size)
        {
            // cards_ptr->show_player_deck_full();
        }
        else
        {
            // cards_ptr->hide_player_deck();
        }
    }

    void state::draw_opponent_cards(int amount)
    {
        for (int i = 0; i < amount; i++)
            opponent.draw_card();
        if (opponent.current_deck_size * 2 > opponent.deck_size)
        {
            // cards_ptr->show_opponent_deck_full();
        }
        else
        {
            // cards_ptr->hide_opponent_deck();
        }
    }

    void state::summon_player_team()
    {
        player.play_team(player.selected_cards[0], cursor_x - 1);
        cards_ptr->show_playmat_card(cursor_x - 1, 0, cards[player.team[cursor_x - 1]]);
        if (hand_offset > bn::max(player.current_hand_size - player_hand_slots, 0)) {
            hand_offset--;
        }
        cards_ptr->show_player_hand(player.hand, player.current_hand_size, hand_offset);
    }

    void state::summon_player_sideine()
    {
        player.play_sideline(player.selected_cards[0], cursor_x - 1);
        cards_ptr->show_playmat_card(cursor_x - 1, 0, cards[player.sideline[cursor_x - 1]]);
        if (hand_offset > bn::max(player.current_hand_size - player_hand_slots, 0)) {
            hand_offset--;
        }
        cards_ptr->show_player_hand(player.hand, player.current_hand_size, hand_offset);
    }

    void state::update()
    {
        directions d = {0, 0, 0, 0};
        if (bn::keypad::up_pressed())
            d.up = 1;
        if (bn::keypad::down_pressed())
            d.down = 1;
        if (bn::keypad::left_pressed())
            d.left = 1;
        if (bn::keypad::right_pressed())
            d.right = 1;

        if (d.up | d.down | d.left | d.right)
        {
            if (context_menu_ptr)
            {
                move_menu(d);
            }
            else
            {
                move_cursor(d);
            }
        }

        if (cursor_y == 0)
        {
            cards_ptr->show_card_info(cards[player.hand[cursor_x + hand_offset]]);
        }

        // If context menu is open
        if (context_menu_ptr)
        {
            if (bn::keypad::a_pressed())
            {
                switch (current_action)
                {
                case SUMMONING:
                    if (context_menu_ptr->get_selected() == SELECT)
                    {
                        if (cursor_y == 1)
                        {
                            summon_player_sideine();
                        }
                        else if (cursor_y == 2)
                        {
                            summon_player_team();
                        }
                        context_menu_ptr.reset();
                    }
                    break;
                }
            } else if (bn::keypad::b_pressed()) {
                context_menu_ptr.reset();
            }
        }
        // otherwise
        else
        {
            if (bn::keypad::a_pressed())
            {
                switch (cursor_y)
                {
                case 0:
                    if (current_action == NONE)
                    {
                        current_action = SUMMONING;
                        player.selected_cards[0] = hand_offset + cursor_x;
                    }
                    break;
                case 1:
                    if (current_action == SUMMONING)
                    {
                        menu_item options[1];
                        if (player.sideline[cursor_x - 1] != -1)
                        {
                            options[0] = VIEW;
                        }
                        else
                        {
                            options[0] = SELECT;
                        }
                        open_menu(options, 1);
                    }
                    break;
                }
            }
        }
    }

    void state::move_cursor(directions d)
    {
        switch (cursor_y)
        {
        case 0:
            if (d.right)
            {
                if (cursor_x + 1 == player_hand_slots)
                {
                    if (hand_offset < bn::max(player.current_hand_size - player_hand_slots, 0))
                    {
                        cards_ptr->show_player_hand(player.hand, player.current_hand_size, ++hand_offset);
                    }
                }
                else
                {
                    cursor_x++;
                }
            }
            else if (d.left)
            {
                if (cursor_x == 0)
                {
                    if (hand_offset > 0)
                    {
                        cards_ptr->show_player_hand(player.hand, player.current_hand_size, --hand_offset);
                    }
                }
                else
                {
                    cursor_x--;
                }
            }

            if (d.up)
            {
                cursor_y = 1;
                cursor_x = 3;
            }
            break;
        default:
        {
            if (d.right)
            {
                cursor_x = bn::min(cursor_x + 1, 6);
            }
            else if (d.left)
            {
                cursor_x = bn::max(cursor_x - 1, 0);
            }

            if (d.down)
            {
                if (cursor_y == 1)
                {
                    cursor_x = 0;
                }
                cursor_y = bn::max(cursor_y - 1, 0);
            }
            else if (d.up)
            {
                cursor_y = bn::min(cursor_y + 1, 4);
            }
            break;
        }
        }
        cursor_ptr->move_to(cursor_x, cursor_y);
    }

    void state::open_menu(menu_item options[], int options_length)
    {
        context_menu_ptr = bn::unique_ptr(new context_menu(cursor_x, cursor_y, options, options_length));
    }

    player_state::player_state(state *state) : parent_state(state) {}

    void player_state::draw_card()
    {
        hand[current_hand_size++] = deck[--current_deck_size];
    }

    int player_state::_pop_hand_card(int hand_index)
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

    void player_state::play_team(int hand_index, int slot)
    {
        team[slot] = _pop_hand_card(hand_index);
    }

    void player_state::play_sideline(int hand_index, int slot)
    {
        sideline[slot] = _pop_hand_card(hand_index);
    }
}