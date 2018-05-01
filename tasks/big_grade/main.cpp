#include <iostream>
#include <array>
#include <cstdio>

using namespace std;

typedef int I;
typedef long L;
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

LL find(LL num, pair<string, array<LL, 2>> a[], LL l, LL r) {

    LL mid;
    while (l <= r) {
        mid = (r - l) / 2 + l;
        if (num >= a[mid].second[0] &&
            num <= a[mid].second[1]) {
            return mid;
        }
        if (num < a[mid].second[0])
            r = mid;
        if (num > a[mid].second[1])
            l = mid + 1;
    }
    return 0;
}

void task() {
    LL n, m;
    cin >> n >> m;
    pair<string, array<LL, 2>> a[n];
    LL last = 0, curr;
    for (LL i = 0; i < n; i++) {
        cin >> a[i].first >> curr;
        a[i].second[0] = last;
        a[i].second[1] = last + curr - 1;
        last = last + curr;
    }
    LL to_find;
    for (LL i = 0; i < m; i++) {
        cin >> to_find;
        cout << a[find(to_find - 1, a, 0, n - 1)].first << endl;
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
