#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;

void set(VVLL &g);

class SubSet {
public:
    LL parent, rank;

    SubSet(LL parent, LL rank) : parent(parent), rank(rank) {}
};

LL findIn(vector<SubSet> &set, LL el) {
    LL &parent = set[el].parent;
    if (parent != el) {
        parent = findIn(set, parent);
    }
    return parent;
}

LL unite(vector<SubSet> &set, LL e1, LL e2) {
    LL p1 = findIn(set, e1);
    LL p2 = findIn(set, e2);

    if (set[p1].rank >= set[p2].rank) {
        set[p2].parent = p1;
    }
    if (set[p1].rank < set[p2].rank) {
        set[p1].parent = p2;
    }
    if (set[p1].rank == set[p2].rank) {
        set[p1].rank++;
    }
}

class Edge {
public:
    LL from, to, weight;

    Edge(LL from, LL to, LL weight) : from(from), to(to), weight(weight) {}

    bool operator<(const Edge &e) {
        return weight < e.weight;
    }
};

vector<Edge> kruskal(const VVLL &g) {
    auto n = g.size();
    vector<Edge> edges;

    for (LL i = 0; i < n; i++) {
        for (LL j = 0; j < n; j++) {
            if (g[i][j] != 0) {
                edges.emplace_back(i, j, g[i][j]);
            }
        }
    }
    sort(begin(edges), end(edges));

    vector<SubSet> set;
    for (LL i = 0; i < g.size(); i++) {
        set.emplace_back(i, 0);
    }

    vector<Edge> result;
    LL i = 0;
    while (result.size() < g.size() - 1) {
        Edge e = edges[i];
        LL pTo = findIn(set, e.to);
        LL pFrom = findIn(set, e.from);
        if (pTo != pFrom) {
            unite(set, pFrom, pTo);
            result.push_back(e);
        }
        i++;
    }

    return result;
}

int main() {
    VVLL g(11, VLL(11, 0));
    set(g);

    vector<Edge> edges = kruskal(g);

    for (auto e : edges) {
        cout << e.from << " -> " << e.to << ", weight: " << e.weight << endl;
    }

}

void set(VVLL &g) {
    g[1][4] = 1;
    g[4][1] = 1;
    g[2][3] = 14;
    g[3][2] = 14;
    g[2][4] = 50;
    g[4][2] = 50;
    g[4][6] = 1;
    g[6][4] = 1;
    g[4][5] = 50;
    g[5][4] = 50;
    g[6][10] = 100;
    g[10][6] = 100;
    g[5][10] = 50;
    g[10][5] = 50;
    g[10][7] = 3;
    g[7][10] = 3;
    g[10][8] = 12;
    g[8][10] = 12;
    g[10][9] = 4;
    g[9][10] = 4;
    g[9][8] = 3;
    g[8][9] = 3;
    g[7][8] = 2;
    g[8][7] = 2;
}