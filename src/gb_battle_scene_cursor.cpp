#include "gb_battle_scene_cursor.h"

namespace gb
{
    namespace battle
    {

        cursor::cursor() : playmat_x(0),
                           playmat_y(0),
                           in_hand(false),
                           hand_index(0),
                           hand_offset(0),
                           sprite(bn::sprite_items::cursor.create_sprite(cursor_playmat_locations[(playmat_y * playmat_spaces_x) + playmat_x]))
        {
        }

        void cursor::move_up()
        {
            if (in_hand)
            {
                in_hand = false;
                sprite.set_position(cursor_playmat_locations[(playmat_y * playmat_spaces_x) + playmat_x]);
            }
            else if (playmat_y < playmat_spaces_y - 1)
            {
                sprite.set_position(cursor_playmat_locations[(++playmat_y * playmat_spaces_x) + playmat_x]);
            }
        }

        void cursor::move_down()
        {
            if (playmat_y > 0)
            {
                sprite.set_position(cursor_playmat_locations[(--playmat_y * playmat_spaces_x) + playmat_x]);
            }
            else
            {
                in_hand = true;
                sprite.set_position(cursor_hand_locations[hand_index]);
            }
        }

        void cursor::move_right()
        {
            if (in_hand) {
                if (hand_index < hand_location_count - 1) {
                    sprite.set_position(cursor_hand_locations[++hand_index]);
                }
            }
            else if (playmat_x < playmat_spaces_x - 1)
            {
                sprite.set_position(cursor_playmat_locations[(playmat_y * playmat_spaces_x) + ++playmat_x]);
            }
        }

        void cursor::move_left()
        {
            if (in_hand) {
                if (hand_index > 0) {
                    sprite.set_position(cursor_hand_locations[--hand_index]);
                }
            }
            else if (playmat_x > 0)
            {
                sprite.set_position(cursor_playmat_locations[(playmat_y * playmat_spaces_x) + --playmat_x]);
            }
        }
    };
}
