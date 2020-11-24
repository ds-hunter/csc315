/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <iostream>
#include "event.h"
#include "util.h"

using namespace std;

// actualY function to invert y axis
int actualY(int y);
// Callback for the display event
void display();
// Callback for the keyboard event
void keyboard(unsigned char key, int x, int y);
// Callback for the mouseClick event
void mouseClick(int button, int state, int x, int y);
// Callback for the mouseMove event
void mouseMove(int x, int y);
// Callback for the reshape event
void reshape(const int x, const int y);
// Program start function
void gameStart();
// Common function for collecting event information
void utilityCentral(Event *);

#endif
