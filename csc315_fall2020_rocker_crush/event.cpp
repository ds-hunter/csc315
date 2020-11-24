#include "event.h"
#include "callbacks.h"
#include "board.h"

Event::~Event() {}

/***************************************************************************//**
 * @brief Constructor
 *
 * Display event is called under a number of circumstances.  During its action
 * method, we just swap the buffers (we are assuming double buffer mode)
 * If there is a repaint required by the game, here is where that would likely
 * happen
 ******************************************************************************/
void DisplayEvent::doAction(Board &gameboard)
{
    glClear(GL_COLOR_BUFFER_BIT);

    gameboard.DrawAll();
    glutSwapBuffers();
}

/***************************************************************************//**
 * @brief Constructor
 *
 * This event gets called continuously as the window is resized.  This event
 * usually also triggers a display event
 *
 * @param[in] w - width (in pixels) of the window
 * @param[in] h - height (in pixels) of the window
 ******************************************************************************/
ReshapeEvent::ReshapeEvent(int w, int h) : width(w), height(h) {}

void ReshapeEvent::doAction(Board &gameboard)
{
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    gluOrtho2D( 0.0, width, 0.0, height );       // make OpenGL coordinates
    glViewport( 0, 0, width, height );  // the same as the screen coordinates
}


/***************************************************************************//**
 * @brief Constructor
 *
 * The mouse is moving but no buttons are depressed
 *
 * @param[in] x - the x-coordinate of where the mouse moved to
 * @param[in] y - the y-coordinate of where the mouse moved to
 ******************************************************************************/
MouseMoveEvent::MouseMoveEvent(int x, int y) : xLoc(x), yLoc(y) {}

void MouseMoveEvent::doAction(Board &gameboard)
{
    stringstream ss;

    ss << "x = " << xLoc << " :: y = " << yLoc;
    glutSetWindowTitle(ss.str().c_str());

    gameboard.CheckHover(xLoc, yLoc);
}

/***************************************************************************//**
 * @brief Constructor
 *
 * The mouse is moving but no buttons are depressed
 *
 * @param[in] button - which button was pressed or released
 * @param[in] state  - was the button pressed or released
 * @param[in] x - the x-coordinate of where the mouse moved to
 * @param[in] y - the y-coordinate of where the mouse moved to
 ******************************************************************************/
MouseClickEvent::MouseClickEvent(int b, int s, int x, int y) : button(b), state(s), xLoc(x), yLoc(y) {}

void MouseClickEvent::doAction(Board &gameboard)
{
    string buttonClicked;
    GameTile *tile = nullptr;

    // Check for button clicks
    if (state == 0) 
    {
        buttonClicked = gameboard.CheckClick(xLoc, yLoc);
        if (buttonClicked == "Quit")
            glutLeaveMainLoop();
    }

    if (state == 0) 
    {
        buttonClicked = gameboard.CheckClick(xLoc, yLoc);
        if (buttonClicked == "Reset") {
            gameboard.GenerateNewBoard();
        }
    }

    // Game End, stop registering clicks.
    if (gameboard.GetTurnsRemaining() <= 0) return;

    // Swap 4 tiles
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    { 
        tile = gameboard.GetTile(xLoc, yLoc);
        if(tile != nullptr)
        {
            gameboard.counterClockSwap(tile);
        }
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        tile = gameboard.GetTile(xLoc, yLoc);
        if(tile != nullptr)
        {
            gameboard.clockwiseSwap(tile);
        }
    }
}

/***************************************************************************//**
 * @brief Constructor
 *
 * A keyboard key has been pressed.  This object's action method will react
 * to the escape key by leaving the main glut event loop.  If you need to do
 * resource freeing, doing so before leaving the glut main loop (or immediately
 * thereafter) is suggested
 *
 * @param[in] k - the ascii value of the key that was pressed
 * @param[in] x - the x-coordinate of where the key 'k' was pressed
 * @param[in] y - the y-coordinate of where the key 'k' was pressed
 ******************************************************************************/
KeyboardEvent::KeyboardEvent(unsigned char k, int x, int y) : key(k), xLoc(x), yLoc(y) {}

void KeyboardEvent::doAction(Board &gameboard)
{
    if (key == ESCAPE_KEY || key == Q_KEY)
        glutLeaveMainLoop();
}

/***************************************************************************//**
 * @brief Constructor
 *
 * A keyboard key has been pressed.  This object's action method will react
 * to the escape key by leaving the main glut event loop.  If you need to do
 * resource freeing, doing so before leaving the glut main loop (or immediately
 * thereafter) is suggested
 *
 * @param[in] k - the ascii value of the key that was pressed
 * @param[in] x - the x-coordinate of where the key 'k' was pressed
 * @param[in] y - the y-coordinate of where the key 'k' was pressed
 ******************************************************************************/
void GameStart::doAction(Board &gameboard) 
{
    gameboard.GenerateNewBoard();
    gameboard.AddButton(0, 0, 40, "Reset", Green);
    gameboard.AddButton(0, 40, 40, "Quit", Red);
}
