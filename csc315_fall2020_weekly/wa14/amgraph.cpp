#include "amgraph.h"

Amgraph::Amgraph(istream &fin) {
    int v, w;
    double weight;
    vector <Dedge> edges;

    while ( fin >> v >> w >> weight) {
        N = max(N, max(v,w));
        edges.push_back(Dedge(v, w, weight));
    }

    N++;
    mat.resize(N);
    for (int i = 0; i < N; i++)
    {
        mat[i].resize(N);
        for (int j = 0; j < N; j++) {
            mat[i][j] = std::numeric_limits<double>::infinity();
            if (i == j) mat[i][j] = 0.0;
        }
    }

    for (Dedge e : edges)
        mat[e.From()][e.To()] = e.Weight();
}

int Amgraph::size() { return N; }

double Amgraph::getCell(int from, int to)
{
    return mat[from][to];
}
