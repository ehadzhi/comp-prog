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

    Edge(LL to, LL weight) : to(to), weight(weight) {

    }

    bool operator<(const Edge &other) const {
        return weight > other.weight;
    }
};

typedef vector<Edge> VE;
typedef vector<VE> VVE;

LL mst(const VVE &g) {
    vector<bool> present(g.size(), false);
    LL res = 0, numPresent = 0;
    priority_queue<Edge> q;
    q.push(Edge(1, 0));

    while (!q.empty()) {
        Edge e = q.top();
        q.pop();

        if (!present[e.to]) {
            present[e.to] = true;
            numPresent++;
            res += e.weight;
            for (auto i : g[e.to]) {
                q.push(i);
            }

        }
    }
    if (numPresent != g.size() - 1)
        return -1;
    return res;
}

void task() {
    LL n, m;
    cin >> n >> m;
    n++;

    VVE g(n);
    LL sum = 0;
    for (LL i = 0; i < m; i++) {
        LL a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(Edge(b, c));
        g[b].push_back(Edge(a, c));
        sum += c;
    }

    LL mstWeight = mst(g);


    if (mstWeight == -1) {
        cout << -1 << endl;
    } else{
        cout << (sum - mstWeight) << endl;
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
