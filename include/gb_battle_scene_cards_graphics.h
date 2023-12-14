#ifndef GB_BATTLE_SCENE_CARDS_GRAPHICS_H
#define GB_BATTLE_SCENE_CARDS_GRAPHICS_H

// Dependencies
#include "gb_cards.h"
#include "bn_vector.h"
#include "bn_unique_ptr.h"
#include "bn_sprite_ptr.h"
#include "gb_battle_scene_cards_graphics_constants.h"
#include "gb_battle_scene_constants.h"
#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_bg_palette_ptr.h"
#include "bn_string_view.h"
#include "bn_sprite_text_generator.h"

namespace gb
{
    namespace battle
    {
        constexpr cell_graphics_info player_deck_full[16] = {
            {3, 8, 203},
            {4, 8, 204},
            {5, 8, 188},
            {2, 9, 109},
            {3, 9, 205},
            {4, 9, 206},
            {5, 9, 190},
            {2, 10, 191},
            {3, 10, 192},
            {4, 10, 192},
            {5, 10, 189}
        };

        constexpr cell_graphics_info opponent_deck_full[16] = {
            {23, 5, 193},
            {24, 5, 194},
            {25, 5, 195},
            {23, 6, 196},
            {24, 6, 197},
            {25, 6, 198},
            {26, 6, 200},
            {23, 7, 86},
            {24, 7, 202},
            {25, 7, 199},
            {26, 7, 201},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
        };

        struct cards_graphics
        {
            static constexpr int columns = 32;
            static constexpr int rows = 32;
            static constexpr int cells_count = columns * rows;

            alignas(int) bn::regular_bg_map_cell cells[cells_count];
            bn::regular_bg_map_item map_item;
            bn::regular_bg_item bg_item;
            bn::regular_bg_ptr bg;
            bn::regular_bg_map_ptr bg_map;

            bn::sprite_text_generator text_generator;
            bn::vector<bn::sprite_ptr, 13> title_text;
            bn::vector<bn::sprite_ptr, 32> body_text;

            cards_graphics();

            void show_playmat_card(int x, int y, card type);
            void hide_playmat_card(int x, int y);

            void show_card_info(card c);

            void show_player_hand(int hand[], int size, int offset);
            void show_player_deck_full();
            // void show_player_deck_half();
            // void show_player_deck_near();
            void hide_player_deck();
            
            void show_opponent_deck_full();
            // void show_player_deck_half();
            // void show_player_deck_near();
            void hide_opponent_deck();

        private:
            void _update_screen(const cell_graphics_info cells[16], card_type type, bool show, int cell_count);
            void update_cell(int x, int y, int cell_index, int palette_id);
            int _card_type_to_palette_id(card_type type);
        };
    }
}

#endif
