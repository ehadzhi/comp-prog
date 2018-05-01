#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>

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

typedef queue<tuple<ll, ll>> qt;

typedef vector<bool> vb;

typedef vector<vb> vvb;

typedef vector<ll> vll;

typedef vector<vll> vvll;

bool inRange(ll x, ll y, ll n, ll m) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

void rot(ll x, ll y, ll n, ll m, ll ox, ll oy, vvll &apples, qt &rotten) {
    if (inRange(x, y, n, m) && apples[x][y] == 0) {
        apples[x][y] = apples[ox][oy] + 1;
        rotten.push(make_tuple(x, y));
    }
}

void task() {
    ll n, m, t;
    cin >> n >> m >> t;
    qt rotten;
    ll a, b;
    vvll apples(n, vll(m, 0));
    while (cin >> a >> b ) {
        a--;
        b--;
        rotten.push(make_tuple(a, b));
        apples[a][b] = 1;
    }
    ll num_rotten = 0;
    t++;
    while (true) {

        if (rotten.empty()) {
            break;
        }
        auto apple = rotten.front();
        rotten.pop();
        ll x = get<0>(apple);
        ll y = get<1>(apple);
        if (apples[x][y] > t) {
            break;
        }
        num_rotten++;

        rot(x + 1, y, n, m, x, y, apples, rotten);
        rot(x - 1, y, n, m, x, y, apples, rotten);
        rot(x, y + 1, n, m, x, y, apples, rotten);
        rot(x, y - 1, n, m, x, y, apples, rotten);
    }
    cout << n * m - num_rotten << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
