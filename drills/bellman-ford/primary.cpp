#include <vector>
#include <iostream>
#include <tuple>
#include <limits.h>

using namespace std;

typedef long long LL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef tuple<LL, LL, LL> Edge;
typedef tuple<VLL, LL> Path;
typedef tuple<vector<Edge>, LL> Graph;

void set(vector<Edge> &g);

vector<Path> bellmanFord(LL v, const vector<Edge> &g, LL numV) {
    vector<Path> paths(numV, make_tuple(VLL(), LONG_LONG_MAX));

    get<1>(paths[v]) = 0;
    for (LL i = 0; i <= numV; i++) {
        bool improved = false;
        for (auto edge : g) {
            LL v1 = get<0>(edge);
            LL v2 = get<1>(edge);
            LL w = get<2>(edge);
            LL v1PathW = get<1>(paths[v1]);
            LL v2PathW = get<1>(paths[v2]);
            if (v1PathW != LONG_LONG_MAX && v1PathW + w < v2PathW) {
                auto newShortest = VLL(get<0>(paths[v1]));
                newShortest.push_back(v1);
                paths[v2] = make_tuple(newShortest, v1PathW + w);
                improved = true;
            }
        }
        if (i != numV && !improved) {
            break;
        }
        if (i == numV && improved) {
            cout << "There is a cycle" << endl;
            break;
        }
    }
    return paths;
}


int main() {
    vector<Edge> g;
    set(g);

    auto paths = bellmanFord(1, g, 11);

    for (LL j = 0; j < paths.size(); j++) {
        auto path = paths[j];
        cout << "---------" << endl;
        cout << "Path: ";
        auto &p = get<0>(path);
        for (auto j : p) {
            cout << j << " ";
        }
        cout << j;
        cout << endl;
        cout << "Weigth: " << get<1>(path) << endl;
    }

}

void set(vector<Edge> &g) {
    g.push_back(make_tuple(1, 4, 1));
    g.push_back(make_tuple(4, 1, 1));
    g.push_back(make_tuple(2, 3, 14));
    g.push_back(make_tuple(3, 2, 14));
    g.push_back(make_tuple(2, 4, 50));
    g.push_back(make_tuple(4, 2, 50));
    g.push_back(make_tuple(4, 6, 1));
    g.push_back(make_tuple(6, 4, 1));
    g.push_back(make_tuple(4, 5, 50));
    g.push_back(make_tuple(5, 4, 50));
    g.push_back(make_tuple(6, 10, 100));
    g.push_back(make_tuple(10, 6, 100));
    g.push_back(make_tuple(5, 10, 50));
    g.push_back(make_tuple(10, 5, 50));
    g.push_back(make_tuple(10, 7, 3));
    g.push_back(make_tuple(7, 10, 3));
    g.push_back(make_tuple(10, 8, 12));
    g.push_back(make_tuple(8, 10, 12));
    g.push_back(make_tuple(10, 9, 4));
    g.push_back(make_tuple(9, 10, 4));
    g.push_back(make_tuple(9, 8, 3));
    g.push_back(make_tuple(8, 9, 3));
    g.push_back(make_tuple(7, 8, 2));
    g.push_back(make_tuple(8, 7, 2));
}
