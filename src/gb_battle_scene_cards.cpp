#include "gb_battle_scene_cards.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_bg_palette_items_card_fronts_palette_challengers.h"
#include "bn_bg_palette_items_card_fronts_palette_grottos.h"
#include "bn_bg_palette_items_card_fronts_palette_beasts.h"
#include "bn_regular_bg_tiles_items_cards.h"
#include "bn_bg_palette_items_card_backs_palette.h"

namespace gb
{
    namespace battle
    {
        cards::cards()
            : bg_map_item(cells[0], bn::size(cards::columns, cards::rows)),
              bg_item(bn::regular_bg_tiles_items::cards, bn::bg_palette_items::card_fronts_palette_beasts, bg_map_item),
              bg(bg_item.create_bg(x_offset, y_offset)),
              bg_map(bg.map())
        {
        }

        void cards::show_card(int x, int y)
        {
            _update_screen(card_graphics_infos[(y * playmat_spaces_x) + x], true);
        }

        void cards::hide_card(int x, int y)
        {
            _update_screen(card_graphics_infos[(y * playmat_spaces_x) + x], false);
        }

        void cards::show_player_deck_full() {
            _update_screen(player_deck_full, true);
        }

        void cards::hide_player_deck() {
            _update_screen(player_deck_full, false);
        }

        void cards::show_opponent_deck_full() {
            _update_screen(opponent_deck_full, true);
        }

        void cards::hide_opponent_deck() {
            _update_screen(opponent_deck_full, false);
        }
        

        void cards::_update_screen(const cell_graphics_info cell_infos[16], bool show) {
            for (int i = 0; i < 16; i++)
            {
                auto cell_graphics_info = cell_infos[i];
                auto &cell = cells[(cell_graphics_info.y * columns) + cell_graphics_info.x];
                auto cellInfo = bn::regular_bg_map_cell_info(cell);
                cellInfo.set_tile_index(show ? cell_graphics_info.tile_index : 0);
                cell = cellInfo.cell();
            }
            bg_map.reload_cells_ref();
        }
    }
}