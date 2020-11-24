#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "util.h"
#include "treenode.h"
#include <string>

const float Black[] = {0.0,0.0,0.0};
const float White[] = {1.0,1.0,1.0};

void DrawLine(float x1, float y1, float x2, float y2, const float color[]);
void DrawTextString(std::string str, float x, float y, const float color[]);
void DrawTree(TreeNode *root, int x, int y, int depth);

#endif
