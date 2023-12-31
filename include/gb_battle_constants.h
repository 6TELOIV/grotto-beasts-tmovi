#ifndef GB_BATTLE_CONSTANTS_H
#define GB_BATTLE_CONSTANTS_H

namespace gb::battle
{
    // Needed to align BGs with screen
    constexpr int x_offset = 8;
    constexpr int y_offset = 48;

    // Definiing size of card grid for LUT lengths
    constexpr int playmat_spaces_middle_x = 5;
    constexpr int playmat_spaces_x = 7;
    constexpr int playmat_spaces_y = 4;
    constexpr int playmat_spaces_middle = playmat_spaces_middle_x * playmat_spaces_y;
    constexpr int playmat_spaces = playmat_spaces_x * playmat_spaces_y;

    // Defining some graphical constraints
    constexpr int player_hand_slots = 4;
}

#endif