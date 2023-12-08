#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bgs_mosaic.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_actions.h"
#include "bn_regular_bg_builder.h"
#include "bn_regular_bg_attributes.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_attributes_hbe_ptr.h"

#include "bn_regular_bg_items_playmat.h"
#include "bn_regular_bg_items_cards.h"

int main()
{
    bn::core::init();

    bn::regular_bg_ptr playmat = bn::regular_bg_items::playmat.create_bg(8, 48);

    while (true)
    {
        bn::core::update();
    }
}
