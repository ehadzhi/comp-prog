#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef int i;
typedef long l;
typedef long long ll;

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

typedef vector<ll> vll;
typedef vector<vll> vvll;

void dfs(const vvll &g, vll &tr, ll i) {
    if (!tr[i]) {
        tr[i] = 1;

        for (ll j = 0; j < g.size(); j++) {
            if (g[i][j]) {
                dfs(g, tr, j);
            }
        }
    }
}

void task() {
    ll n, m;

    cin >> n >> m;
    vvll g(n, vll(n, 0));

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a][b] = 1;
        g[b][a] = 1;
    }


    vll traversed(n, 0);

    ll res = 0;
    for (ll i = 0; i < n; i++) {
        if (!traversed[i]) {
            res++;
        }
        dfs(g, traversed, i);
    }

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
