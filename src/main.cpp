#include "bn_core.h"

// Scenes
#include "gb_battle_scene.h"

int main()
{
    bn::core::init();

    gb::battle::battle_scene();

    return 0;
}