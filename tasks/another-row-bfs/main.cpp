#include <iostream>
#include <cstdio>
#include <limits.h>
#include <queue>
#include <algorithm>
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
typedef tuple<LL, LL> TLL;

LL reverse(LL value) {
    LL res = 0;
    for (LL i = value; i != 0;) {
        int d = i / 10;
        res = (res - d) * 10 + i;
        i = d;
    }
    return res;
}

void task() {
    int millySeven = 1000007;
    LL a, b;
    while (cin >> a >> b) {
        vector<bool> v(millySeven, false);
        queue<TLL> q;
        q.emplace(a, 0);
        v[a] = true;

        while (!q.empty()) {
            auto r = q.front();
            q.pop();
            if (get<0>(r) == b) {
                cout << (get<1>(r) + 1) << endl;
                break;
            }
            auto next = (get<0>(r) + 1) % millySeven;
            if (!v[next]) {
                q.emplace(next, get<1>(r) + 1);
                v[next] = true;
            }
            long reversedNext = reverse(get<0>(r)) % millySeven;
            if (!v[reversedNext]) {
                q.emplace(reversedNext, get<1>(r) + 1);
                v[reversedNext] = true;
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
