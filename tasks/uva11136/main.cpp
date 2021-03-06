#include <iostream>
#include <cstdio>
#include <limits.h>
#include <queue>
#include <set>

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

    LL numDays;
    while (true) {
        cin >> numDays;
        if (numDays == 0)
            return;

        multiset<LL> bills;
        LL sumToPay = 0;
        for (LL i = 0; i < numDays; i++) {
            LL numBills;
            cin >> numBills;

            for (LL j = 0; j < numBills; j++) {
                LL bill;
                cin >> bill;
                bills.insert(bill);
            }

            sumToPay += (*(--end(bills)) - *begin(bills));
            bills.erase(begin(bills));
            bills.erase(--end(bills));
        }
        cout << sumToPay << endl;
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
