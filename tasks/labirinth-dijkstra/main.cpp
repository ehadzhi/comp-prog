#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

typedef long long LL;

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

typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef tuple<LL, LL> TLL;
typedef vector<TLL> VTLL;

VVLL p = {{0,  1},
          {1,  0},
          {0,  -1},
          {-1, 0}};

bool isFree(LL x, LL y, const VVLL &space) {
    return x >= 0 && y >= 0
           && x < space.size() && y < space[0].size()
           && space[x][y] == 1;
}

class Sort {
public:
    bool operator()(const TLL &one, const TLL &two) const {
        return get<0>(one) > get<0>(two);
    }
};

TLL findMaxPath(LL x, LL y, LL l, VVLL &space) {
    space[x][y] = 0;

    VTLL maxPaths;
    for (LL i = 0; i < 4; i++) {
        LL nx = x + p[i][0];
        LL ny = y + p[i][1];
        if (isFree(nx, ny, space))
            maxPaths.push_back(findMaxPath(nx, ny, l, space));
    }

    if (maxPaths.empty())
        return make_tuple(1, 0);

    if (maxPaths.size() == 1) {
        return make_tuple(get<0>(maxPaths[0]) + 1, 0);

    }

    if (maxPaths.size() > 1) {
        sort(begin(maxPaths), end(maxPaths), Sort());
        auto m = maxPaths[0];
        auto vM = get<0>(m);
        auto bM = get<1>(m);

        auto subM = maxPaths[1];
        auto vSubM = get<0>(subM);
        auto bSubM = get<1>(subM);

        if (bM == 1 && bSubM == 1)
            return make_tuple(vM, 1);

        if (bM == 0 && bSubM == 1)
            return make_tuple(vM + 1, 0);

        if (bM == 1 && bSubM == 0) {
            if (vSubM + 1 + l > vM) {
                return make_tuple(vSubM + 1, 0);
            }
            return make_tuple(vM, 1);
        }

        if (bM == 0 && bSubM == 0)
            return make_tuple(vM + 1, 0);
    }
}

void task() {
    LL n, m;
    cin >> m >> n;
    VVLL space(n, VLL(m, 0));
    LL x, y;

    for (LL i = 0; i < n; i++) {
        for (LL j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '.') {
                space[i][j] = 1;
                x = i;
                y = j;
            }
        }
    }

    cout << get<0>(findMaxPath(x, y, 0, space)) << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
