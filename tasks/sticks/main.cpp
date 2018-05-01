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
typedef vector<LL> VLL;
typedef vector<bool> VB;

LL separate(const VLL &sticks) {
    LL sum = 0;
    for (auto stick : sticks) {
        sum += stick;
    }

    auto n = sticks.size();

    VB possibleSums(sum + 1, false);
    possibleSums[0] = true;

    for (auto stick : sticks) {
        VLL newSums;
        for (LL i = 0; i < sum + 1; i++) {
            if (possibleSums[i] && !possibleSums[i + stick]) {
                newSums.push_back(i + stick);
            }
        }
        for (auto newSum : newSums) {
            possibleSums[newSum] = true;
        }
    }

    LL res = sum;
    for (LL i = 0; i < sum + 1; i++) {
        if (possibleSums[i]) {
            LL diff = max(i - (sum - i), (sum - i) - i);
            res = min(diff, res);
        }
    }

    return res;
}

void task() {
    LL n;
    cin >> n;
    VLL sticks;

    for (LL i = 0; i < n; i++) {
        LL a;
        cin >> a;
        sticks.push_back(a);
    }

    cout << separate(sticks) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
