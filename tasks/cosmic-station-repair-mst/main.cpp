#include <iostream>
#include <cstdio>
#include <limits.h>
#include <queue>
#include <algorithm>

using namespace std;

void task();

bool equals(FILE *f1, FILE *f2) {
    char f1c, f2c;
    while (true) {
        f1c = fgetc(f1);
        f2c = fgetc(f2);
        if (f1c == EOF || f2c == EOF)
            return f1c == f2c;
        if (f1c != f2c)
            return false;
    }
}

bool tests() {
    try {
        string profile = getenv("profile");
        if (profile == "dev") {
            string base = "./temp/t";
            int test_num = 1;
            FILE *in;
            do {
                auto path = base + to_string(test_num);
                auto *expected = (path + "e").c_str();
                auto *actual = (path + "a").c_str();

                in = freopen(path.c_str(), "r", stdin);
                if (in) {
                    freopen(actual, "w", stdout);

                    clock_t begin = clock();

                    task();

                    clock_t end = clock();
                    auto elapse = double(end - begin) / CLOCKS_PER_SEC;

                    fprintf(stderr, "Test %d took %f sec.\n", test_num, elapse);
                    if (!equals(fopen(expected, "r"), fopen(actual, "r"))) {
                        cerr << "Problem in test " << test_num << endl;
                    }
                }
                test_num++;
            } while (in);
            return true;
        }
    } catch (exception e) {

    }
    return false;
}

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

    Edge() {}

    Edge(LL from, LL to, LL weight) : from(from), to(to), weight(weight) {}

    bool operator<(const Edge &e) const {
        return weight < e.weight;
    }
};

LL kruskal(vector<Edge> &edges, LL n) {
    sort(begin(edges), end(edges));

    vector<SubSet> set;
    for (LL i = 0; i < n; i++) {
        set.emplace_back(i, 0);
    }

    LL result = 0, num = 0, i = 0;
    while (num < n - 1) {
        Edge e = edges[i];
        LL pTo = findIn(set, e.to);
        LL pFrom = findIn(set, e.from);
        if (pTo != pFrom) {
            unite(set, pFrom, pTo);
            result += e.weight;
            num++;
        }
        i++;
    }
    return result;
}


void task() {
    LL n, m, k;
    cin >> n >> m >> k;
    n++;
    vector<Edge> g(m + k);

    for (LL i = 0; i < m; i++) {
        LL a, b, c;
        cin >> a >> b >> c;
        g.emplace_back(a, b, c);
        g.emplace_back(b, a, c);
    }

    for (LL i = 0; i < k; i++) {
        LL a, b;
        cin >> a >> b;
        g.emplace_back(a, b, 0);
        g.emplace_back(b, a, 0);
    }

    LL res = kruskal(g, n);
    cout << res << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
