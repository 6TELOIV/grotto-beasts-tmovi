#include "gb_battle_scene.h"

// Dependencies
#include "gb_battle_scene_cards_graphics.h"
#include "gb_battle_scene_cursor.h"
#include "gb_battle_scene_state.h"
#include "bn_core.h"
#include "bn_math.h"
#include "bn_random.h"

namespace gb
{
    namespace battle
    {

        void battle_scene()
        {
            state the_state;

            // Main loop
            while (true)
            {
                the_state.update();
                bn::core::update();
            }
        }
    }
}