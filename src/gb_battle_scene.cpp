#include "gb_battle_scene.h"

namespace gb::battle
{

    /**
     * @brief Constructor
     */
    battle_scene::battle_scene()
        : playmat(bn::regular_bg_items::playmat.create_bg(8, 48)),
          cards_graphics_ptr(bn::unique_ptr(new cards_graphics())),
          cursor_ptr(bn::unique_ptr(new cursor()))
    {
        // phase/turn
        current_turn = rng.get_int() % 2 == 0 ? ACTOR : OPPONENT;
        current_phase = START_OF_TURN;

        // player
        actor.deck_size = 60;
        actor.current_deck_size = actor.deck_size;
        actor.current_discard_size = 0;
        actor.current_hand_size = 0;
        actor.current_scored_size = 0;
        for (int i = 0; i < actor.current_deck_size; i++)
        {
            actor.deck[i] = i;
        }
        actor.shuffle_deck(rng);

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
        opponent.shuffle_deck(rng);

        // deal cards
        draw_actor_cards(6);
        draw_opponent_cards(6);
    }

    /**
     * @brief Called every frame; handles progressing the game state.
     */
    void battle_scene::update()
    {
        // Get the pressed directions
        directions d = {0, 0, 0, 0};
        if (bn::keypad::up_pressed())
            d.up = 1;
        if (bn::keypad::down_pressed())
            d.down = 1;
        if (bn::keypad::left_pressed())
            d.left = 1;
        if (bn::keypad::right_pressed())
            d.right = 1;

        // If any directions are pressed, process the updates needed
        if (d.up | d.down | d.left | d.right)
        {
            // Move cursor/menu
            if (context_menu_ptr)
            {
                move_menu(d);
            }
            else
            {
                move_cursor(d);
            }
        }

        // Display the pointed at info
        bn::string<13> title;
        bn::string<32> body;
        if (cursor_y == 0)
        {
            card the_card = cards[actor.hand[cursor_x + hand_offset]];
            title = the_card.short_name;
                body = bn::format<32>(bn::string_view("C{} P{} G{}"), the_card.cost, the_card.power, the_card.goal);
        }
        else if (cursor_y == 1)
        {
            if (cursor_x == 0)
            {
            }
            else if (cursor_x == 6)
            {
            }
            else
            {
                card the_card = cards[actor.sideline[cursor_x - 1]];
                title = the_card.short_name;
                body = bn::format<32>(bn::string_view("C{} P{} G{}"), the_card.cost, the_card.power, the_card.goal);
            }
        }
        else if (cursor_y == 2)
        {
            if (cursor_x == 0)
            {
            }
            else if (cursor_x == 6)
            {
            }
            else
            {
                card the_card = cards[actor.team[cursor_x - 1]];
                title = the_card.short_name;
                body = bn::format<32>(bn::string_view("C{} P{} G{}"), the_card.cost, the_card.power, the_card.goal);
            }
        }
        else if (cursor_y == 3)
        {
            if (cursor_x == 0)
            {
            }
            else if (cursor_x == 6)
            {
            }
            else
            {
                card the_card = cards[opponent.team[cursor_x - 1]];
                title = the_card.short_name;
                body = bn::format<32>(bn::string_view("C{} P{} G{}"), the_card.cost, the_card.power, the_card.goal);
            }
        }
        else
        {
            if (cursor_x == 0)
            {
            }
            else if (cursor_x == 6)
            {
            }
            else
            {
                card the_card = cards[opponent.sideline[cursor_x - 1]];
                title = the_card.short_name;
                body = bn::format<32>(bn::string_view("C{} P{} G{}"), the_card.cost, the_card.power, the_card.goal);
            }
        }
        cards_graphics_ptr->show_info(title, body);

        // If context menu is open
        if (context_menu_ptr)
        {
            if (bn::keypad::a_pressed())
            {
                // If they have selected to summon, summon.
                if (current_action == SUMMONING && context_menu_ptr->get_selected() == SELECT)
                {
                    summon_actor(cursor_y == 1 ? actor.sideline : actor.team);
                    context_menu_ptr.reset();
                    current_action = NONE;
                }
            }
            // cancel whatever we were doing in the menu
            else if (bn::keypad::b_pressed())
            {
                context_menu_ptr.reset();
            }
        }
        // otherwise
        else
        {
            if (bn::keypad::a_pressed())
            {
                if (cursor_y == 0)
                {
                    if (current_action == NONE)
                    {
                        current_action = SUMMONING;
                        actor.hand_indices[0] = hand_offset + cursor_x;
                    }
                }
                else if (cursor_y == 1 || cursor_y == 2)
                {
                    if (current_action == SUMMONING)
                    {
                        open_sumon_menu();
                    }
                }
            }
        }
    }

    /**
     * @brief Helper to move the cursor. Updates cursor_x and cursor_y as needed
     */
    void battle_scene::move_cursor(directions d)
    {
        // Move the cursor
        if (cursor_y == 0)
        {
            if (d.right)
            {
                if (cursor_x + 1 == player_hand_slots)
                {
                    if (hand_offset < bn::max(actor.current_hand_size - player_hand_slots, 0))
                    {
                        cards_graphics_ptr->show_player_hand(actor.hand, actor.current_hand_size, ++hand_offset);
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
                        cards_graphics_ptr->show_player_hand(actor.hand, actor.current_hand_size, --hand_offset);
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
        }
        else
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
        }
        cursor_ptr->move_to(cursor_x, cursor_y);
    }

    /**
     * @brief Moves the context menu
     */
    void battle_scene::move_menu(directions d)
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

    /**
     * @brief Opens a new context menu
     */
    void battle_scene::open_menu(menu_item options[], int options_length)
    {
        context_menu_ptr = bn::unique_ptr(new context_menu(cursor_x, cursor_y, options, options_length));
    }

    /**
     * @brief Draws an amount of cards form the actors deck to hand.
     * @param amount Number of cards to draw
     */
    void battle_scene::draw_actor_cards(int amount)
    {
        for (int i = 0; i < amount; i++)
            actor.draw_card();

        cards_graphics_ptr->show_player_hand(actor.hand, actor.current_hand_size, hand_offset);
        if (actor.current_deck_size * 2 > actor.deck_size)
        {
            // cards_ptr->show_player_deck_full();
        }
        else
        {
            // cards_ptr->hide_player_deck();
        }
    }

    /**
     * @brief Draws an amount of cards form the opponent's deck to hand.
     * @param amount Number of cards to draw
     */
    void battle_scene::draw_opponent_cards(int amount)
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

    /**
     * @brief Opens a menu with options depending on if a card may be summoned
     */
    void battle_scene::open_sumon_menu()
    {
        menu_item options[4];
        int options_length = 0;
        if (cursor_y == 1)
        {
            if (actor.sideline[cursor_x - 1] == -1)
            {
                card the_card = cards[actor.hand[actor.hand_indices[0]]];
                if (the_card.type != WISH)
                {
                    options_length = 1;
                    options[0] = SELECT;
                }
            }
            else
            {
                options_length = 1;
                options[0] = VIEW;
            }
        }
        else if (cursor_y == 2)
        {
            if (actor.team[cursor_x - 1] == -1)
            {
                card the_card = cards[actor.hand[actor.hand_indices[0]]];
                if (the_card.type != GROTTO && the_card.type != WISH)
                {
                    options_length = 1;
                    options[0] = SELECT;
                }
            }
            else
            {
                options_length = 1;
                options[0] = VIEW;
            }
        }
        else if (cursor_y == 0 && actor.current_hand_size > 0)
        {
            options_length = 1;
            options[0] = VIEW;
        }
        else if (cursor_y == 3 || cursor_y == 4)
        {
            int *location = cursor_y == 4 ? opponent.sideline : opponent.team;
            options_length = 1;
            if (location[cursor_x - 1] != -1)
            {
                options[0] = VIEW;
                options_length = 1;
            }
        }

        if (options_length > 0)
        {
            open_menu(options, options_length);
        }
    }

    void battle_scene::summon_actor(int summon_location[])
    {
        summon_location[cursor_x - 1] = actor.pop_hand_card(actor.hand_indices[0]);
        cards_graphics_ptr->show_playmat_card(cursor_x - 1, cursor_y - 1, cards[summon_location[cursor_x - 1]]);
        if (hand_offset > bn::max(actor.current_hand_size - player_hand_slots, 0))
        {
            hand_offset--;
        }
        cards_graphics_ptr->show_player_hand(actor.hand, actor.current_hand_size, hand_offset);
    }
}