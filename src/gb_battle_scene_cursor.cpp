#include "gb_battle_scene_cursor.h"

namespace gb
{
    namespace battle
    {

        cursor::cursor() : sprite(bn::sprite_items::cursor.create_sprite(0, 0))
        {
        }

        void cursor::move_to(int x, int y) {
            switch (y) {
                case 0:
                    sprite.set_position(cursor_player_hand_locations[x]);
                    break;
                default:
                    sprite.set_position(cursor_playmat_locations[((y - 1) * playmat_spaces_x) + x]);
                    break;
            }
        }
    };
}
