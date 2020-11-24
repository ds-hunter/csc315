/**************************************************************************//**
 * @file graphics.cpp
 *
 * @brief OpenGL graphics program, illustrating use of GLUT and callback 
 * functions.
 *
 * @author: John M. Weiss, Ph.D.
 *
 * @par Class:
 * CSC300 Data Structures
 *
 * @date:   Fall 2015
 *
 * @par Modifications:
 *    * Added doxygen style comments : PJH 9/5/2016
 ******************************************************************************/
#include "graphics.h"

/**************************************************************************//**
 * @brief Draw a line in the active window from point [x1,y1] to [x2,y2]
 *
 * @param[in] x1 - x-coordinate of the starting point
 * @param[in] y1 - y-coordinate of the starting point
 * @param[in] x2 - x-coordinate of the end point
 * @param[in] y2 - y-coordinate of the end point
 * @param[in] color - float array containing the color of the line being drawn
 *
 ******************************************************************************/
void DrawLine( float x1, float y1, float x2, float y2, const float color[] )
{
    // glLineWidth( 10 );
    glColor3fv( color );
    glBegin( GL_LINES );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y2 );
    glEnd();
    glFlush();
}

/**************************************************************************//**
 * @brief Draw a rectangle in the active window from point [x1,y1] to [x2,y2]
 *
 * @param[in] x1 - x-coordinate of the left-lower corner
 * @param[in] y1 - y-coordinate of the left-lower corner
 * @param[in] x2 - x-coordinate of the right-upper corner
 * @param[in] y2 - y-coordinate of the right-upper corner
 * @param[in] color - float array containing the color of the boundries
 *
 ******************************************************************************/
void DrawRectangle( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_LINE_LOOP );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x1, y2 );
    glEnd();
    glFlush();
}

/**************************************************************************//**
 * @brief Draw a filled rectangle in the active window from point [x1,y1] to 
 * [x2,y2]
 *
 * @param[in] x1 - x-coordinate of the left-lower corner
 * @param[in] y1 - y-coordinate of the left-lower corner
 * @param[in] x2 - x-coordinate of the right-upper corner
 * @param[in] y2 - y-coordinate of the right-upper corner
 * @param[in] color - float array containing the filled color of the rectangle
 *
 ******************************************************************************/
void DrawFilledRectangle( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_POLYGON );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x1, y2 );
    glEnd();
    glFlush();
}

/**************************************************************************//**
 * @brief Draw an ellipse in the active window at point [x,y]
 *
 * @param[in] xRadius - x-radius of the ellipse
 * @param[in] yRadius - y-radius of the ellipse
 * @param[in] x - x-coordinate of the center of the ellipse
 * @param[in] y - y-coordinate of the center of the ellipse
 * @param[in] color - float array containing the filled color of the ellipse
 *
 ******************************************************************************/
void DrawEllipse( float xRadius, float yRadius, int x, int y, const float color[] )
{
    // stretch circle into ellipse
    float radius = xRadius < yRadius ? xRadius : yRadius;
    glColor3fv( color );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );

    // by ratio of major to minor axes
    glScalef( xRadius / radius, yRadius / radius, 1.0 );	
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, radius - 1, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
    glFlush();
}

/**************************************************************************//**
 * @brief Draw an ellipse in the active window at point [x,y]
 *
 * @param[in] xRadius - x-radius of the ellipse
 * @param[in] yRadius - y-radius of the ellipse
 * @param[in] x - x-coordinate of the center of the ellipse
 * @param[in] y - y-coordinate of the center of the ellipse
 * @param[in] color - float array containing the filled color of the ellipse
 *
 ******************************************************************************/
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y, const float color[] )
{
    // stretch circle into ellipse
    float radius = xRadius < yRadius ? xRadius : yRadius;
    glColor3fv( color );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );

    // by ratio of major to minor axes
    glScalef( xRadius / radius, yRadius / radius, 1.0 );
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
    glFlush();
}

/**************************************************************************//**
 * @brief Draw text in the window
 *
 * @param[in] string - The text to draw
 * @param[in] x - x-coordinate of the start of the string
 * @param[in] y - y-coordinate of the start of the string
 * @param[in] color - float array containing the filled color of the ellipse
 *
 ******************************************************************************/
void DrawTextString(std::string str, int x, int y, const float color[] )
{
    glColor3fv( color );
    glRasterPos2i( x, y );
    for (auto x : str)
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, x );
}

void DrawFilledTriangle(float x1, float x2, float x3, float y1, float y2,
        float y3, const float color[] ) 
{
    glColor3fv(color); 
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
    glFlush();
}
