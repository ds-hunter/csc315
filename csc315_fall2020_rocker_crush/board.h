#ifndef BOARD_H
#define BOARD_H

#include "button.h"
#include "gameTile.h"
#include "graphics.h"
#include <vector>
#include <string>

using namespace std;

class Board 
{
    private:
	// vector containing the ui buttons
        vector<Button *> buttons;
	// 8x8 'gameboard' containing 64 randomly generated game tiles
        GameTile* tileBoard[8][8];
        int score = 0;
        int highscore = 0;
        int turnsRemaining = 25;
        int HorizMatch(int, int);
        int VertMatch(int, int);
        int ScoreMatch(int, int);
        void FillNullTiles();
    public:
        Board();
        ~Board();
        void AddButton(int, int, int, string, const float[]);
        void DrawAll();
        string CheckClick(int, int);
        GameTile *GenerateRandomTile();
        void GenerateNewBoard();
        void CheckMatches();
        void CheckHover(int xLoc, int yLoc);
        GameTile* GetTile(int, int);
        void counterClockSwap(GameTile*);
        void clockwiseSwap(GameTile*);
        int GetTurnsRemaining();
        void UpdateBoard();
        void DrawLegend();	
};

#endif
