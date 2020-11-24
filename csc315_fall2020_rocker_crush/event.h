#ifndef _EVENT_H_
#define _EVENT_H_
#include <iostream>
#include <GL/freeglut.h>
#include <sstream>
#include "graphics.h"
#include "board.h"

using namespace std;

#define ESCAPE_KEY 27
#define Q_KEY 113
/***************************************************************************//**
 * @class Event
 ******************************************************************************/
class Event
{
    public:
        virtual void doAction(Board &) = 0;
        virtual ~Event();
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class DisplayEvent : public Event
{
    public:
        void doAction(Board &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class KeyboardEvent : public Event
{
    /// The key involved in this event
    unsigned char key;
    /// The x-location of where the event took place
    int xLoc;
    /// The y-location of where the event took place
    int yLoc;

    public:
    /// Constructor
    KeyboardEvent(unsigned char, int, int);

    void doAction(Board &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class MouseClickEvent : public Event
{
    /// The button involved in the event
    int button;
    /// The state of the button for this event (e.g. up, down)
    int state;
    /// The x-location of where the event took place
    int xLoc;
    /// The y-location of where the event took place
    int yLoc;

    public:
    /// Constructor
    MouseClickEvent(int, int, int, int);

    void doAction(Board &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class MouseMoveEvent : public Event
{
    /// The x-location of where the event took place
    int xLoc;
    /// The y-location of where the event took place
    int yLoc;

    public:
    /// Constructor
    MouseMoveEvent(int, int);

    void doAction(Board &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class ReshapeEvent : public Event
{
    int width;
    int height;
    public:
    ReshapeEvent(int, int);

    void doAction(Board &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class GameStart : public Event
{
    public:
    void doAction(Board &);
};

#endif
