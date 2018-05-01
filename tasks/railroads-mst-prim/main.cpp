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

class Edge {
public:
    LL to;
    LL weight;
    bool railroad;

    Edge(LL to, LL weight, bool railroad) : to(to), weight(weight), railroad(railroad) {}

    bool operator>(const Edge &rhs) const {
        if (weight != rhs.weight)
            return weight > rhs.weight;
        if(railroad == rhs.railroad)
            return false;
        return railroad <= rhs.railroad;
    }
};

typedef vector<Edge> VE;
typedef vector<VE> VVE;

LL mst(const VVE &g) {

    priority_queue<Edge, VE, greater<Edge>> q;

    q.emplace(1, 0, false);
    LL res = 0;
    vector<bool> present(g.size(), false);
    while (!q.empty()) {
        Edge e = q.top();
        q.pop();

        if (!present[e.to]) {
            if (e.railroad) {
                res++;
            }

            present[e.to] = true;
            for (const auto &i : g[e.to]) {
                if (!present[i.to]) {
                    q.push(i);
                }
            }
        }
    }
    return res;
}

void task() {

    LL n, m, k;
    cin >> n >> m >> k;
    n++;
    VVE g(n);

    for (LL i = 0; i < m; i++) {
        LL a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c, false);
        g[b].emplace_back(a, c, false);
    }

    for (LL i = 0; i < k; i++) {
        LL a, b;
        cin >> a >> b;
        g[1].emplace_back(a, b, true);
        g[a].emplace_back(1, b, true);
    }


    LL res = mst(g);

    cout << (k - res) << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
