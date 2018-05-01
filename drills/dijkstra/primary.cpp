#include <vector>
#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

typedef long long LL;

typedef vector<LL> VLL;

typedef vector<VLL> VVLL;

typedef tuple<VLL, LL> Path;

void set(VVLL &g);

struct LessPath {
    bool operator()(const Path &p1, const Path &p2) {
        return get<1>(p1) >= get<1>(p2);
    }
};

typedef priority_queue<Path, vector<Path>, LessPath> Queue;

vector<Path> dijkstra(LL v, const VVLL &g) {
    auto n = g.size();
    vector<Path> vp;
    vp.reserve(n);

    vector<bool> done(n, false);

    Queue q((LessPath()), vp);

    q.push(make_tuple(VLL(1, 1), 0));

    while (!q.empty()) {
        auto path = q.top();
        q.pop();
        VLL currentPath = get<0>(path);
        LL v = currentPath.back();
        LL w = get<1>(path);

        if (!done[v]) {
            done[v] = true;
            vp.push_back(path);

            for (LL i = 0; i < n; i++) {
                auto new_w = g[v][i];
                if (!done[i] && new_w > 0) {
                    auto next_path(currentPath);
                    next_path.push_back(i);
                    q.push(make_tuple(next_path, w + new_w));
                }
            }
        }
    }
    return vp;
}

int main() {
    VVLL g(11, VLL(11, 0));
    set(g);

    auto paths = dijkstra(1, g);

    for (auto &path : paths) {
        cout << "---------" << endl;
        cout << "Path: ";
        Steiner tree problem     auto &p = get<0>(path);
        for (long long j : p) {
            cout << j << " ";
        }
        cout << endl;
        cout << "Weigth: " << get<1>(path) << endl;
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

