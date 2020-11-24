#include "floydwarshall.h"
#include <limits>

Floydwarshall::Floydwarshall(Amgraph *G)
{
    initialize(G);
    executeFW();
}

void Floydwarshall::initialize(Amgraph *G) {
    memo.resize(G->size());
    next.resize(G->size());
    for (int row = 0; row < G->size(); row++) {
        memo[row].resize(G->size());
        next[row].resize(G->size());
        for (int col = 0; col < G->size(); col++) {
            memo[row][col] = G->getCell(row, col);
            next[row][col] = -1;
            if (memo[row][col] != std::numeric_limits<double>::infinity())
                next[row][col] = col;
        }
    }
}

void Floydwarshall::executeFW()
{
    int N = memo.size();
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (memo[i][k] + memo[k][j] < memo[i][j])
                {
                    memo[i][j] = memo[i][k] + memo[k][j];
                    next[i][j] = next[i][k];
                }

    checkForNegCycles();
}

void Floydwarshall::checkForNegCycles()
{
    int N = memo.size();

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (memo[i][k] + memo[k][j] < memo[i][j])
                {
                    memo[i][j] = -1 * std::numeric_limits<double>::infinity();
                    next[i][j] = -1;
                }
}

bool Floydwarshall::hasPath(int from, int to)
{
    if (memo[from][to] != std::numeric_limits<double>::infinity())
        return false;
    if (memo[from][to] != -1 * std::numeric_limits<double>::infinity())
        return false;

    return true;
} 

double Floydwarshall::distance(int from, int to)
{
    return memo[from][to];
}

list<int> Floydwarshall::pathTo(int from, int to)
{
    list<int> path;
    if (!hasPath(from, to)) return path;
    
    int current = from;
    for (; current != to; current = next[current][to])
    {
        if (current == -1) return list<int>();
        path.push_back(current);
    }
    if (next[current][to] == -1) return list<int>();
    path.push_back(to);
    return path;
}


