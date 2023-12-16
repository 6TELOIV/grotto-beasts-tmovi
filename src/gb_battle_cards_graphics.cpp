#include "gb_battle_cards_graphics.h"

namespace gb
{
    namespace battle
    {
        cards_graphics::cards_graphics()
            : map_item(cells[0], bn::size(columns, rows)),
              bg_item(bn::regular_bg_tiles_items::cards, bn::bg_palette_items::cards_palette, map_item),
              bg(bg_item.create_bg(x_offset, y_offset)),
              bg_map(bg.map()),
              text_generator(unifont_sprite_font)
        {
        }

        void cards_graphics::show_playmat_card(int x, int y, card c)
        {
            _update_screen(card_graphics_infos[(y * playmat_spaces_middle_x) + x], c.type, true, 16);
            bg_map.reload_cells_ref();
        }

        void cards_graphics::hide_playmat_card(int x, int y)
        {
            _update_screen(card_graphics_infos[(y * playmat_spaces_middle_x) + x], BEAST, false, 16);
            bg_map.reload_cells_ref();
        }

        void cards_graphics::show_info(bn::string<13> title, bn::string<32> body)
        {
            title_text.clear();
            body_text.clear();
            text_generator.generate(-116, 57, title, title_text);
            text_generator.generate(-116, 73, body, body_text);
        }

        void cards_graphics::show_player_hand(int hand[], int size, int offset)
        {
            for (int i = 0; i < player_hand_slots; i++) {
                if (i + offset >= size) {
                    _update_screen(player_hand[i], BEAST, false, 4);
                } else {
                    _update_screen(player_hand[i], cards[hand[i + offset]].type, true, 4);
                }
            }
            if (size > player_hand_slots + offset) {
                _update_screen(player_hand_right_arrow, BEAST, true, 4);
            } else {
                _update_screen(player_hand_right_arrow, BEAST, false, 4);
            }
            if (offset > 0) {
                _update_screen(player_hand_left_arrow, BEAST, true, 4);
            } else {
                _update_screen(player_hand_left_arrow, BEAST, false, 4);
            }
            bg_map.reload_cells_ref();
        }

        void cards_graphics::show_player_deck_full()
        {
            _update_screen(player_deck_full, BEAST, true, 16);
            bg_map.reload_cells_ref();
        }

        void cards_graphics::hide_player_deck()
        {
            _update_screen(player_deck_full, BEAST, false, 16);
            bg_map.reload_cells_ref();
        }

        void cards_graphics::show_opponent_deck_full()
        {
            _update_screen(opponent_deck_full, BEAST, true, 16);
            bg_map.reload_cells_ref();
        }

        void cards_graphics::hide_opponent_deck()
        {
            _update_screen(opponent_deck_full, BEAST, false, 16);
            bg_map.reload_cells_ref();
        }

        void cards_graphics::_update_screen(const cell_graphics_info cell_infos[], card_type type, bool show, int cell_count)
        {
            int palette_id = _card_type_to_palette_id(type);
            for (int i = 0; i < cell_count; i++)
            {
                update_cell(cell_infos[i].x, cell_infos[i].y, show ? cell_infos[i].tile_index : 0, palette_id);
            }
        }

        void cards_graphics::update_cell(int x, int y, int tile_index, int palette_id)
        {
            BN_LOG("---------");
            BN_LOG(" Drawing ", tile_index);
            BN_LOG("    at x ", x);
            BN_LOG("       y ", y);
            BN_LOG("with pal ", palette_id);
            bn::regular_bg_map_cell &current_cell = cells[map_item.cell_index(x, y)];
            bn::regular_bg_map_cell_info current_cell_info(current_cell);
            current_cell_info.set_tile_index(tile_index);
            current_cell_info.set_palette_id(palette_id);
            current_cell = current_cell_info.cell();
            BN_LOG("    Drew ", current_cell);
        }

        int cards_graphics::_card_type_to_palette_id(card_type type)
        {
            switch (type)
            {
            case CHALLENGER:
                return 3;
            case GROTTO:
                return 1;
            case WISH:
                return 2;
            default:
                return 0;
            }
        }
    }
}