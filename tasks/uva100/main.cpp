#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>

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

int cycle_length(LL a) {
    int res = 1;
    while (a != 1) {
        res++;
        if (a % 2 == 0) {
            a /= 2;
        } else {
            a = 3 * a + 1;
        }
    }
    return res;
}

void task() {

    int a, b, max_cycle;
    while (cin >> a >> b) {
        cout << a << " " << b << " ";
        if (a > b)
            swap(a, b);
        max_cycle = cycle_length(b);
        for (int i = a; i < b; i++) {
            max_cycle = max(max_cycle, cycle_length(i));
        }
        cout << max_cycle << endl;
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
