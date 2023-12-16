#ifndef GB_SCENE_H
#define GB_SCENE_H

namespace gb
{
    class scene
    {
    public:
        scene() = default;
        virtual void update() = 0;
        virtual ~scene() = default;
    };
}

#endif