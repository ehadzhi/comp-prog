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

LL cut(LL s, LL e, const VLL &v, LL sum) {
    if (e - s <= 1) {
        return 0;
    }
    LL halfSum = sum / 2;
    LL closestSum = 0, closestI = 0;

    for (LL i = s; i < e; i++) {
        closestSum += v[i];
        if (closestSum >= halfSum) {
            closestI = i;
            break;
        }
    }
    LL dPrev = -1 * (closestSum - v[closestI] - halfSum);
    LL d = closestSum - halfSum;
    if (closestI > 0 && d > 0
        && d > dPrev) {
        closestSum -= v[closestI];
        closestI--;
    }
    cerr << closestI + 1 << endl;
    return sum + cut(s, closestI + 1, v, closestSum) +
           cut(closestI + 1, e, v, sum - closestSum);
}

void task() {
    LL n;
    cin >> n;
    VLL v(n);
    LL sum = 0;
    for (LL i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
    }

    cout << cut(0, n, v, sum) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
