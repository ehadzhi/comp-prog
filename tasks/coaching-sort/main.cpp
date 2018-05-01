#include <iostream>
#include <cstdio>
#include <vector>

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

void task() {
    string str;
    getline(cin, str);

    VLL frqTable(63, 0);
    string nums;
    getline(cin, nums);
    LL n = nums.size();

    for (LL i = 0; i < n; i++) {
        char c = nums[i];
        if (c >= '0' && c <= '9') {
            frqTable[c - '0']++;
        }
        if (c >= 'A' && c <= 'Z') {
            frqTable[c - 'A' + 37]++;
        }
        if (c >= 'a' && c <= 'z') {
            frqTable[c - 'a' + 10]++;
        }
    }

    for (LL i = 0, k = 0; i < frqTable.size(); i++) {
        char c;
        if (i >= 0 && i <= 9)
            c = i + '0';
        if (i >= 10 && i <= 36)
            c = i + 'a' - 10;
        if (i >= 37 && i <= 62)
            c = i + 'A' - 37;
        for (LL j = 0; j < frqTable[i]; j++) {
            nums[k] = c;
            k++;
        }
    }
    cout << nums;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
