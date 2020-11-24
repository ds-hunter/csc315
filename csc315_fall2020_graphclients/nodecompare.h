#ifndef _NODE_H
#define _NODE_H

struct Node
{
    int vertex;
    double overallDist;
    Node(int v, double o) : vertex(v), overallDist(o) {}
};

class nodeCompare
{
    public:
        bool operator()(const Node &lhs, const Node &rhs)
        {
            return (lhs.overallDist > rhs.overallDist);
        }
};

#endif
