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
    string profile = "prod";
    try {
        profile = getenv("profile");
    }
    catch (exception e) {
        cerr << e.what();
    }
    if (profile == "dev") {
        string base = "../temp/t";
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
    return false;
}


void task() {


    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    int c = 0, m = INT_MIN;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j <= i; j++) {
            int index = j % 2 == 0 ? i / 2 : i - (i / 2 + 1);
            c += index;
            m = max(c, m);
        }
    }

    cout << m << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
