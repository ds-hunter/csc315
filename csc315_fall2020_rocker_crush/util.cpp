#include "util.h"

/***************************************************************************//**
 * @brief Main event dispatch function
 *
 * Any events to which the application has subscribed will be routed through
 * this function.  If you need to maintain application state, this is a good
 * place to do so.  All events have an 'action' method which take a Game
 * object.  The Game class can react to the various events by inspecting the
 * event object that is currently acting.
 *
 * @param[in] event - Pointer to an Event object.
 ******************************************************************************/
void utilityCentral(Event *event)
{
    static Board gameboard;

    event->doAction(gameboard);
    glutPostRedisplay();
    delete event;
}

/***************************************************************************//**
 * Initialize glut callback functions, set the display mode, create a window
 ******************************************************************************/
void initOpenGL(int argc, char** argv, int wCols, int wRows)
{
    glutInit(&argc, argv);

    // Choose the display mode for the window.  GLUT_DOUBLE means double 
    // buffering, GLUT_RGBA is 24-bit color with 8-bit alpha

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Set window size and position
    glutInitWindowSize(wCols, wRows);

    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);

    // Subscribe to GLUT events

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouseClick);

    glutPassiveMotionFunc(mouseMove);

    glutReshapeFunc(reshape);

    utilityCentral(new GameStart());
    // This is the color which will be used to clear the display / back plane
    // when glClear() is called
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
