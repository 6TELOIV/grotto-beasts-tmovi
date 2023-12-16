#include "gb_battle_context_menu.h"

namespace gb::battle
{
    context_menu::context_menu(int x, int y, menu_item items[], int item_count)
        : options_length(item_count),
          selection(bn::sprite_items::context_buttons.create_sprite(menu_locations[x + (y * 7)], 4))
    {
        for (int i = 0; i < item_count; i++)
        {
            options[i] = items[i];
            auto location = menu_locations[x + (y * 7)];
            location.set_y(location.y() + (i * 8));
            sprite_ptrs[i] = bn::unique_ptr(new bn::sprite_ptr(bn::sprite_items::context_buttons.create_sprite(location, items[i])));
            sprite_ptrs[i]->set_z_order(0);
        }
        selection.set_z_order(1);
    }

    void context_menu::move_up()
    {
        if (selected_option > 0) {
            selected_option--;
            selection.set_y(selection.y() - 8);
        }
    }

    void context_menu::move_down()
    {
        if (selected_option < options_length - 1) {
            selected_option++;
            selection.set_y(selection.y() + 8);
        }
    }
    menu_item context_menu::get_selected()
    {
        return options[selected_option];
    }
}