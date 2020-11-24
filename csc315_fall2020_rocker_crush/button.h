#ifndef BUTTON_H
#define BUTTON_H
#include "labeledTile.h"

class Button : public LabeledTile
{
    public:
        Button(int, int, int, string, const float[]);
        ~Button();
        bool contains(int, int);
        void draw();
};

#endif
