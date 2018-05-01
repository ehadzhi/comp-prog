#include <iostream>
#include <cstdio>
#include <vector>
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

typedef vector<ll> vll;

typedef vector<vll> vvll;

typedef tuple<ll, ll> t;

typedef queue<t> qt;

const vvll p = {{-2, -1},
                {-1, -2},
                {1,  -2},
                {2,  -1},
                {2,  1},
                {1,  2},
                {-1, 2},
                {-2, 1}};

bool isValid(ll x, ll y, ll n, ll m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void task() {

    ll n, m, x, y, x1, y1, x2, y2;

    cin >> n >> m >> x >> y >> x1 >> y1 >> x2 >> y2;

    vvll space(n, vll(m, 0));

    space[x][y] = 1;
    space[x1][y1] = -1;
    space[x2][y2] = -2;


    qt qt1;
    qt1.push(make_tuple(x, y));

    ll tx, ty, res = 0, res2 = 0;
    while (res == 0) {
        t t1 = qt1.front();
        qt1.pop();
        tx = get<0>(t1);
        ty = get<1>(t1);

        for (ll i = 0; i < 8; i++) {
            ll nx = tx + p[i][0];
            ll ny = ty + p[i][1];

            if (isValid(nx, ny, n, m)) {
                if (space[nx][ny] == 0) {
                    space[nx][ny] = space[tx][ty] + 1;
                    qt1.push(make_tuple(nx, ny));
                }
                if (space[nx][ny] < 0) {
                    space[nx][ny] = space[tx][ty] + 1;
                    res = space[nx][ny];
                    tx = nx;
                    ty = ny;
                    break;
                }
            }
        }
    }
    qt qt2;
    qt2.push(make_tuple(tx, ty));
    while (res2 == 0) {
        t t1 = qt2.front();
        qt2.pop();
        tx = get<0>(t1);
        ty = get<1>(t1);

        for (ll i = 0; i < 8; i++) {
            ll nx = tx + p[i][0];
            ll ny = ty + p[i][1];

            if (isValid(nx, ny, n, m)) {
                if (space[nx][ny] <= res && space[nx][ny] >= 0) {
                    space[nx][ny] = space[tx][ty] + 1;
                    qt2.push(make_tuple(nx, ny));
                }
                if (space[nx][ny] < 0) {
                    res2 = space[tx][ty];
                    break;
                }
            }
        }
    }
    cout << res2 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
