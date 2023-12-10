#ifndef GB_CARDS_H
#define GB_CARDS_H

namespace gb {
    enum card_type {
        CHALLENGER,
        GROTTO,
        WISH,
        BEAST
    };

    struct card {
        const char short_name[11];
        const char long_name[24];
        const card_type type;
    };

    constexpr card cards[200] = {
        { "Glueman", "Glueman", CHALLENGER },
        { "BF B.Berry", "B.F. Bugleberry", CHALLENGER },
        { "B.Sweet P.", "Bittersweet Peaks", GROTTO },
        { "JBA P. Up.", "JBA Power Card: Upgrade", WISH },
        { "2-M. Jelly", "2-Moon Jelly", BEAST },
    };
}

#endif