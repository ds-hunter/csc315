#include "board.h"
#include <iostream>
#include <time.h>
#include <sstream>
#include "callbacks.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"
#include "graphics.h"
#include <iterator>
#include <chrono>
#include <thread>

using namespace std;

Board::Board() {};

Board::~Board() 
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete tileBoard[i][j];
            tileBoard[i][j] = nullptr;
        }
    }

    buttons.clear();        
};

int Board::HorizMatch(int i, int j) 
{
    int matches = 1;
    GameTile *baseTile = tileBoard[i][j];
    //check that it's in the bounds of the board
    while (j + 1 <= 7)
    {
	// check for the color match
        if (baseTile->color == tileBoard[i][j + 1]->color) 
        { 
            matches++;
            j++;
        }
        else
            break;
    }

    return matches;
}

int Board::VertMatch(int i, int j) 
{
    int matches = 1;
    GameTile *baseTile = tileBoard[i][j];
    // check that it's in the bounds of the board
    while (i + 1 <= 7)
    {
        // check for the color match
	if (baseTile->color == tileBoard[i + 1][j]->color) 
        { 
            matches++;
            i++;
        }
        else
            break;
    }

    return matches;
}

int Board::ScoreMatch(int matches, int score) {
    switch (matches)
    {
        default:
            return score;
        case 4:
            return score + 15;
        case 5:
            return score + 30;
        case 6:
            return score + 45;
        case 7:
            return score + 60;
        case 8:
            return score + 75;
    }
}

void Board::AddButton(int x, int y, int size, string text,
        const float col[]) 
{
    // Add a button with all parameters listed
    buttons.push_back(new Button(x, y, size, text, col));
}

void Board::DrawAll() 
{
    // Loop through all buttons and use their draw functions to draw them
    for (Button *b : buttons)
        b->draw();
    // Draw all gametiles
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // if a tile == nullptr it's an empty tile 
	    if (tileBoard[i][j] == nullptr)
                continue;
            // draw each tile by setting their x and y positions from the i + j
	    // position in the board + starting position of the board
            tileBoard[i][j]->x = 160+60*j;
            tileBoard[i][j]->y = 60*i;
            tileBoard[i][j]->draw();
            // Draw outlines if hovered
            if (tileBoard[i][j]->isHovered())
                tileBoard[i][j]->drawOutline();
        }
    }
    // Draw the legend
    DrawLegend();
    // Game End Draw Event
    if (turnsRemaining <= 0) {
        DrawTextString("GAME OVER", glutGet(GLUT_WINDOW_WIDTH)/2, 
                actualY(glutGet(GLUT_WINDOW_HEIGHT)/2), White);
    }
}

string Board::CheckClick(int xPos, int yPos) {
    // Check all buttons for one that contains xPos and yPos, return its name
    for (Button *b : buttons) { 
        if (b->contains(xPos, yPos))
            return b->label;
    }

    // Return "None" for no button found
    return "None";
}

GameTile* Board::GenerateRandomTile() {
    // ASSUMING RANDOM SEED IS ALREADY GENERATED
    GameTile *tile = nullptr;
    const float *color;
    int colorRoll = rand() % 3;
    int shapeRoll = rand() % 3;


    // Get random RGB color
    switch(colorRoll) 
    {
        case 0:
            color = Red;
            break;
        case 1:
            color = Blue;
            break;
        case 2:
            color = Green;
            break;
        default:
            cout << "Something went wrong with the color roll." << endl;
            color = Red;
            break;
    }

    // Generate random shape at board position
    switch(shapeRoll) 
    {
        case 0:
            tile = new Circle(0, 0, 55, color);
            break;
        case 1:
            tile = new Triangle(0, 0, 55, color);
            break;
        case 2:
            tile = new Square(0, 0, 55, color);
            break;
        default:
            cout << "Something went wrong with the random shape roll." << endl;
            break;
    }

    return tile;
}
void Board::GenerateNewBoard() 
{
    // Generate new seed & set up board/tile dimensions
    srand(time(NULL));
    GameTile *tile;
    int boardStartX = 160;
    int boardStartY = 0;
    int tableSize = 8;
    int xPos, yPos;

    // Update scores
    if (highscore < score)
        highscore = score;
    score = 0;
    turnsRemaining = 25;
    for (int i = 0; i < tableSize; i++)
    {
        for (int j = 0; j < tableSize; j++)
        {
	    // draw each tile by setting their x and y positions from the i + j
	    // position in the board + starting position of the board
            xPos = boardStartX + 60 * j;
            yPos = boardStartY + 60 * i;
            tile = GenerateRandomTile();
            tile->x = xPos;
            tile->y = yPos;
            tileBoard[i][j] = tile;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT);
    DrawAll();
    glutSwapBuffers();
}

void Board::CheckMatches() {
    GameTile *tile;
    string shape;
    const float *color;
    int matches = 0;
    int points = 0;

    // Loop through all tiles in the tileboard
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
	    tile = tileBoard[i][j];
            shape = tile->shape;
            color = tile->color;

            // Set Score Multiplier
            if (color == Blue)
                points = 25;
            else if (color == Red)
                points = 30;
            else
                points = 45; 

            // Score horizontal matches
            matches = HorizMatch(i,j);
            if (matches >= 3)
            {
                points = ScoreMatch(matches, points);
                // Delete matched tiles
                for (int k = j; k < j+matches; k++)
                {
		    // enough matches were made for a delete + score, call
		    // DrawRectangle to draw the highlight box around the
		    // matched tiles x-Location, y-Location + tile size (55)
                    DrawRectangle(tileBoard[i][k]->x, 
				    actualY(tileBoard[i][k]->y), 
				    tileBoard[i][k]->x+55, 
				    actualY(tileBoard[i][k]->y+55), White);
		    glutSwapBuffers();
		    std::this_thread::sleep_for(std::chrono::milliseconds(100));
		    // delete matched tile and set to nullptr ('empty' tile)
		    delete tileBoard[i][k];
                    tileBoard[i][k] = nullptr;
                }
                // call to update board to fill any 'empty' tiles and move the
		// appropriate tiles down
                UpdateBoard();
                score += points;
            }

            // Score vertical matches
            matches = VertMatch(i, j);
            if (matches >= 3)
            {
                points = ScoreMatch(matches, points);
                for (int k = i; k < i+matches; k++)
                {
		    // enough matches were made for a delete + score, call
		    // DrawRectangle to draw the highlight box around the
		    // matched tiles x-Location, y-Location + tile size (55)
                    DrawRectangle(tileBoard[k][j]->x, 
				    actualY(tileBoard[k][j]->y), 
				    tileBoard[k][j]->x+55, 
				    actualY(tileBoard[k][j]->y+55), White);
		    glutSwapBuffers();
		    std::this_thread::sleep_for(std::chrono::milliseconds(100));
		    // delete matched tile and set to nullptr ('empty' tile)
	  	    delete tileBoard[k][j];
                    tileBoard[k][j] = nullptr;
                }
		// call to update board to fill any 'empty' tiles and move the
		// appropriate tiles down
                UpdateBoard();
                score += points;
            }
        }
    }    
}

void Board::CheckHover(int xLoc, int yLoc) 
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
	    // call contains function to verify the hovered x-Location +
	    // y-Location are points contained within a tile
            if (tileBoard[i][j]->contains(xLoc, yLoc))
            {
                tileBoard[i][j]->toggleHover(true);
            }
            else
            {
                tileBoard[i][j]->toggleHover(false);
            }

        }
    }

    // check for matches whenever the mouse moves to reduce time with unused
    // matches
    CheckMatches();
}

/***************************************************************************//**
 * @brief A board member function that takes in an x-Location and y-Location as
 * coordinates, these coordinates usually come from the mouse click event to
 * see where the player clicked, then returns the pointer to the clicked tile
 * 
 * @param[in] xLoc : x-Location of player's click
 * 
 * @param[in] yLoc : y-Location of player's click
 ******************************************************************************/
GameTile* Board::GetTile(int xLoc, int yLoc) 
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tileBoard[i][j]->contains(xLoc, yLoc))
            {
                return tileBoard[i][j];
            }
        }
    }

    return nullptr;
}

/***************************************************************************//**
 * @brief A board member function that takes in a pointer to a GameTile and 
 * conducts a counter clockwise rotation within the array tileBoard. 
 * 
 * @param[in] GameTile *t : a pointer to a GameTile, this is usually found by
 *                          clicking on a GameTile on the board and returning
 *                          the pointer with the board member func GetTile
 ******************************************************************************/
void Board::counterClockSwap(GameTile *t)
{
    int j = (t->x - 160) / 60;
    int i = t->y / 60;

    if (i >= 0 && i < 7 && j >= 0 && j < 7)
    {
        swap(tileBoard[i][j]->x, tileBoard[i + 1][j]->x);
        swap(tileBoard[i][j]->y, tileBoard[i + 1][j]->y);
        swap(tileBoard[i][j], tileBoard[i + 1][j]);

        swap(tileBoard[i][j]->x, tileBoard[i][j + 1]->x);
        swap(tileBoard[i][j]->y, tileBoard[i][j + 1]->y);
        swap(tileBoard[i][j], tileBoard[i][j + 1]);

        swap(tileBoard[i][j + 1]->x, tileBoard[i + 1][j + 1]->x);
        swap(tileBoard[i][j + 1]->y, tileBoard[i + 1][j + 1]->y);
        swap(tileBoard[i][j + 1], tileBoard[i + 1][j + 1]);
    }
    turnsRemaining--;
    // redraw the board after the swap
    glClear(GL_COLOR_BUFFER_BIT);
    DrawAll();
    glutSwapBuffers();
    // check for new matches after a rotation
    CheckMatches();
}

/***************************************************************************//**
 * @brief A board member function that takes in a pointer to a GameTile and 
 * conducts a clockwise rotation within the array tileBoard. 
 * 
 * @param[in] GameTile *t : a pointer to a GameTile, this is usually found by
 *                          clicking on a GameTile on the board and returning
 *                          the pointer with the board member func GetTile
 ******************************************************************************/
void Board::clockwiseSwap(GameTile *t)
{
    int j = (t->x - 160) / 60;
    int i = t->y / 60;
    
    if (i >= 0 && i < 7 && j >= 0 && j < 7)
    {
        swap(tileBoard[i][j]->x, tileBoard[i][j + 1]->x);
        swap(tileBoard[i][j]->y, tileBoard[i][j + 1]->y);
        swap(tileBoard[i][j], tileBoard[i][j + 1]);

        swap(tileBoard[i][j]->x, tileBoard[i + 1][j]->x);
        swap(tileBoard[i][j]->y, tileBoard[i + 1][j]->y);
        swap(tileBoard[i][j], tileBoard[i + 1][j]);

        swap(tileBoard[i + 1][j]->x, tileBoard[i + 1][j + 1]->x);
        swap(tileBoard[i + 1][j]->y, tileBoard[i + 1][j + 1]->y);
        swap(tileBoard[i + 1][j], tileBoard[i + 1][j + 1]);
    }
    turnsRemaining--;
    // redraw the board after the swap
    glClear(GL_COLOR_BUFFER_BIT);
    DrawAll();
    glutSwapBuffers();
    // recheck for matches after a rotation
    CheckMatches();
}

int Board::GetTurnsRemaining() {
    return turnsRemaining;
}

/***************************************************************************//**
 * @brief A board member function that recursively checks for nullptrs that
 * indicate an 'empty' tile, it fills the slot in the array with the board
 * member function GenerateRandomTile and then moves the tile down and continues
 * until the board is full.
 ******************************************************************************/
void Board::UpdateBoard() {
    bool changed = false;

    // Fill first row of tiles
    for (int j = 0; j < 8; j++)
        if (tileBoard[0][j] == nullptr)
        {
            // if the tile is a nullptr then a new tile is generated and passed
	    // the x and y coordinate. 
	    tileBoard[0][j] = GenerateRandomTile();
            tileBoard[0][j]->x = 160 + 60 * j;
            tileBoard[0][j]->y = 0; 
        }

    // Check for any cases where a tile needs to be moved down
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Drop tiles down 
            if (tileBoard[i + 1][j] == nullptr)
            {
                changed = true;
                tileBoard[i][j]->x = 160 + 60 * j;
                tileBoard[i][j]->y = 60 * i;
                // if the tile below (i + 1) is empty (nullptr) then swap tiles 
		swap(tileBoard[i][j], tileBoard[i + 1][j]);
		
		// redraw the tiles after a swap is completed, with a small
		// delay so the player can visually see the tiles 'falling'
                glClear(GL_COLOR_BUFFER_BIT);
                DrawAll();
                glutSwapBuffers();
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }
        }
    }

    // Base Case
    if (changed == false)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        DrawAll();
        glutSwapBuffers();
        return;
    }
    UpdateBoard();
}

/***************************************************************************//**
 * @brief A board member function that draws the score, high score, turns, and
 * legend.
 ******************************************************************************/
void Board::DrawLegend()
{
    // Draw Score box 
    DrawFilledRectangle(0, actualY(100), 110, actualY(145), Gray);   
    DrawTextString("Score", 30, actualY(95), White);

    // Draw High Score box
    DrawFilledRectangle(0, actualY(175), 110, actualY(220), Blue);
    DrawTextString("High Score", 10, actualY(170), White);

    // Draw Turns box
    DrawFilledRectangle(0, actualY(250), 110, actualY(295), Magenta);
    DrawTextString("Turns", 30, actualY(245), White);

    // Draw Legend box
    DrawTextString("Legend", 5, actualY(390), White); 
    DrawRectangle(5, actualY(510), 155, actualY(395), Yellow);

    // Draw Legend text
    DrawTextString("Num. of", 95, actualY(380), White);
    DrawTextString("Matches", 95, actualY(390), White);
    DrawTextString("4x = 15", 95, actualY(420), White);
    DrawTextString("5x = 30", 95, actualY(440), White);
    DrawTextString("6x = 45", 95, actualY(460), White);
    DrawTextString("7x = 60", 95, actualY(480), White);
    DrawTextString("8x = 75", 95, actualY(500), White);

    // Draw the blue shapes 
    DrawTextString("25", 13, actualY(410), White); 
    DrawFilledEllipse(10, 10, 20, actualY(430), Blue);
    DrawFilledTriangle(10, 30, 20, actualY(450), actualY(450), actualY(470), 
            Blue);
    DrawFilledRectangle(10, actualY(500), 30, actualY(480), Blue);

    // Draw the red shapes
    DrawTextString("30", 43, actualY(410), White); 
    DrawFilledEllipse(10, 10, 50, actualY(430), Red);
    DrawFilledTriangle(40, 60, 50, actualY(450), actualY(450), actualY(470), 
            Red);
    DrawFilledRectangle(40, actualY(500), 60, actualY(480), Red);

    // Draw the green shapes
    DrawTextString("45", 73, actualY(410), White); 
    DrawFilledEllipse(10, 10, 80, actualY(430), Green);
    DrawFilledTriangle(70, 90, 80, actualY(450), actualY(450), actualY(470), 
            Green);
    DrawFilledRectangle(70, actualY(500), 90, actualY(480), Green);

    // Draw the score label
    DrawTextString(to_string(score), 40, actualY(125), White);
    // Draw the highscore label
    DrawTextString(to_string(highscore), 40, actualY(200), White);
    // Draw the turns label
    DrawTextString(to_string(turnsRemaining), 40, actualY(275), White);
}
