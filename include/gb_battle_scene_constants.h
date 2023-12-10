#ifndef GB_BATTLE_SCENE_CONSTANTS_H
#define GB_BATTLE_SCENE_CONSTANTS_H

namespace gb
{
    namespace battle {
        // Needed to align BGs with screen
        constexpr int x_offset = 8;
        constexpr int y_offset = 48;

        // Definiing size of card grid for LUT lengths
        constexpr int playmat_spaces_x = 7;
        constexpr int playmat_spaces_y = 4;
        constexpr int playmat_spaces = playmat_spaces_x * playmat_spaces_y;
    }
}

#endif