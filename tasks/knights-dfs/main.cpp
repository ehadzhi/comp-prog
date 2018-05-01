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

bool isValid(ll x, ll y, ll n) {
    return x >= 0 && x < n
           && y >= 0 && y < n;
}

void task() {

    ll n, num_holes, num_knights;
    cin >> n >> num_holes >> num_knights;

    vvll board(n, vll(n, 0));
    for (ll i = 0; i < num_holes; i++) {
        ll x, y;
        cin >> x >> y;
        board[x][y] = -2;
    }

    for (ll i = 0; i < num_knights; i++) {
        ll x, y;
        cin >> x >> y;
        board[x][y] = -1;
    }

    ll x, y;
    cin >> x >> y;
    qt moves;
    moves.push(make_tuple(x, y));

    ll num_attending_knights = 0;
    ll wait_time = 0;

    while (!moves.empty()) {
        t move = moves.front();
        moves.pop();
        x = get<0>(move);
        y = get<1>(move);

        for (ll i = 0; i < 8; i++) {
            ll nx = x + p[i][0];
            ll ny = y + p[i][1];
            if (isValid(nx, ny, n)) {
                auto &val = board[nx][ny];
                if (val != -2 && val < 1) {
                    moves.push(make_tuple(nx, ny));
                    if (val == -1) {
                        num_attending_knights++;
                        val = board[x][y] + 1;
                        wait_time = val;
                    } else {
                        val = board[x][y] + 1;
                    }
                }
            }
        }
    }

    cout << num_attending_knights << " " << wait_time << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
