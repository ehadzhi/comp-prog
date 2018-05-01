#include <iostream>
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

void task() {
    LL m, n, k;
    cin >> m >> n >> k;
    LL a1[m][n], a2[n][k];
    for (LL i = 0; i < m; i++)
        for (LL j = 0; j < n; j++)
            cin >> a1[i][j];

    for (LL i = 0; i < n; i++)
        for (LL j = 0; j < k; j++)
            cin >> a2[i][j];

    LL res[m][k] = {};
    for (LL i = 0; i < m; i++)
        for (LL j = 0; j < k; j++)
            for (LL l = 0; l < n; l++)
                res[i][j] += a1[i][l] * a2[l][j];

    for (LL i = 0; i < m; i++) {
        for (LL j = 0; j < k; j++)
            cout << res[i][j] << " ";
        cout << endl;
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
