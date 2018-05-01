#include <iostream>
#include <cstdio>
#include <limits.h>
#include <queue>
#include <utility>
#include <iterator>

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


class Path {
public:
    LL to;
    LL weight;
    VLL road;

    Path(LL to, LL weight) : to(to), weight(weight) {

    }

    bool operator<(const Path &other) const {
        return weight > other.weight;
    }
};

typedef vector<Path> VP;
typedef vector<VP> VVP;

Path shortestPath(LL from, LL to, const VVP &g) {

    VP paths(g.size(), Path(0, -1));
    priority_queue<Path> q;
    Path initial(from, 0);
    initial.road.push_back(from);
    q.push(initial);

    while (!q.empty()) {
        Path currP = q.top();
        q.pop();

        if (paths[currP.to].weight == -1) {
            paths[currP.to] = currP;

            auto &nextPs = g[currP.to];
            for (const auto &i : nextPs) {
                Path nextP(i.to, i.weight + currP.weight);
                nextP.road.insert(nextP.road.cend(), currP.road.cbegin(), currP.road.cend());
                nextP.road.push_back(nextP.to);
                q.push(nextP);
            }
        }
    }
    return paths[to];
}

void task() {

    LL n, m, x, y, z;
    cin >> n >> m >> x >> y >> z;
    n++;

    VVP g(n);
    for (LL i = 0; i < m; i++) {
        LL a, b, c;
        cin >> a >> b >> c;

        g[a].push_back(Path(b, c));
        g[b].push_back(Path(a, c));
    }

    Path p = shortestPath(x, y, g);
    Path p2 = shortestPath(y, z, g);

    if (p.weight == -1 || p2.weight == -1) {
        cout << -1 << endl;
    } else {
        cout << (p.weight + p2.weight) << endl;

        for (auto r : p.road) {
            cout << r << " ";
        }
        for (LL i = 1; i < p2.road.size(); i++) {
            cout << p2.road[i];
            if (i != p2.road.size() - 1) {
                cout << " ";
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
