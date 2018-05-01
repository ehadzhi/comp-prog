#include <iostream>
#include <vector>
#include <tuple>
#include <limits.h>

using namespace std;

typedef long long LL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<VVLL> VVVLL;
typedef tuple<VVLL, VVVLL> ShortestPaths;


void set(VVLL &g);

ShortestPaths floydWarshall(const VVLL &g) {
    auto n = g.size();
    VVVLL paths(n, VVLL(n));
    VVLL dists(n, VLL(n, LLONG_MAX));

    for (LL i = 0; i < n; i++) {
        for (LL j = 0; j < n; j++) {
            if (g[i][j] != 0) {
                dists[i][j] = g[i][j];
                paths[i][j] = {i, j};
            }
            if (i == j) {
                dists[i][j] = 0;
            }
        }
    }

    for (LL i = 0; i < n; i++) {
        for (LL j = 0; j < n; j++) {
            for (LL k = 0; k < n; k++) {
                auto &ik = dists[i][k];
                auto &kj = dists[k][j];
                auto &ij = dists[i][j];
                if (ik != LLONG_MAX && kj != LLONG_MAX
                    && ik + kj < ij) {
                    ij = ik + kj;

                    auto &pik = paths[i][k];
                    auto &pkj = paths[k][j];
                    auto newPath = VLL(pik);
                    newPath.insert(end(newPath), begin(pkj) + 1, end(pkj));
                    paths[i][j] = newPath;
                }
            }
        }
    }

    return make_tuple(dists, paths);
}

int main() {

    int n = 11;
    VVLL g(n, VLL(n, 0));
    set(g);

    auto pathsWithDists = floydWarshall(g);

    for (LL i = 0; i < n; i++) {
        for (LL j = 0; j < n; j++) {
            auto &size = get<0>(pathsWithDists)[i][j];
            if (size != LLONG_MAX) {
                cout << "size: " << size << endl;
                auto path = get<1>(pathsWithDists)[i][j];
                cout << "path: ";
                for (LL k = 0; k < path.size(); k++) {
                    cout << path[k] << " ";
                }
                cout << endl << endl;
            }
        }
    }

    return 0;
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