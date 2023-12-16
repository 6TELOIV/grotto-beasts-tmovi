// Dependencies
#include "bn_core.h"
#include "bn_unique_ptr.h"

#include "gb_scene.h"
#include "gb_battle_scene.h"

int main()
{
    bn::core::init();

    bn::unique_ptr<gb::scene> current_scene(new gb::battle::battle_scene());
    while (true) {
        current_scene->update();
        bn::core::update();
    } 

    return 0;
}