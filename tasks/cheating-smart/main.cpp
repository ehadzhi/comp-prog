#include <iostream>
#include <cstdio>
#include <limits.h>
#include <queue>

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


class Path {
public:
    LL to;
    LL weight;

    Path(LL to, LL weight) : to(to), weight(weight) {

    }

    bool operator<(const Path &other) const {
        return weight > other.weight;
    }
};

typedef vector<Path> VP;
typedef vector<VP> VVP;

LL shortestPath(LL from, LL to, const VVP &g) {

    vector<LL> paths(g.size(), -1);
    priority_queue<Path> q;
    q.push(Path(from, 0));

    while (!q.empty()) {
        Path current = q.top();
        q.pop();

        if (paths[current.to] == -1) {
            paths[current.to] = current.weight;

            for (LL i = 0; i < g[current.to].size(); i++) {
                q.push(Path(g[current.to][i].to, current.weight + g[current.to][i].weight));
            }
        }
    }

    return paths[to];
}

void task() {
    LL n, m, k;

    cin >> n >> m >> k;

    VVP g(n);

    for (LL i = 0; i < m; i++) {
        LL x, y;
        cin >> x >> y;
        g[x].push_back(Path(y, 0));
        g[y].push_back(Path(x, 0));
    }

    for (LL i = 0; i < k; i++) {
        LL x, y;
        cin >> x >> y;
        g[x].push_back(Path(y, 1));
        g[y].push_back(Path(x, 1));
    }

    cout << shortestPath(n - 1, 0, g) << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
