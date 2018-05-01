#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <tuple>

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

class Path {
public:
    LL to;
    LL weight;

    Path(LL to, LL weight) : to(to), weight(weight) {

    }

    bool operator<(const Path &one) const {
        return weight > one.weight;
    }
};

typedef vector<vector<Path>> VVP;


LL shortestPath(LL from, LL to, const VVP &g) {
    LL n = g.size();
    VLL paths(n, -1);
    priority_queue<Path> q;
    q.push(Path(from, 0));

    while (!q.empty()) {
        Path current = q.top();
        q.pop();

        if (paths[current.to] == -1) {
            paths[current.to] = current.weight;
            for (const auto &possibleNext : g[current.to]) {
                q.push(Path(possibleNext.to, current.weight + possibleNext.weight));
            }
        }

    }
    return paths[to];

}

void task() {
    LL n, m, x, y;
    cin >> n >> m >> x >> y;
    VVP g(n + 1);

    for (LL i = 0; i < m; i++) {
        LL a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(Path(b, c));
        g[b].push_back(Path(a, c));
    }

    LL path = shortestPath(x, y, g);
    cout << path << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
