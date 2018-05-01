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

class Event {
public:
    LL start;
    LL lenght;

    Event(LL start, LL lenght) : start(start), lenght(lenght) {}

    bool operator<(const Event &rhs) const {
        if (start < rhs.start)
            return true;
        if (rhs.start < start)
            return false;
        return lenght < rhs.lenght;
    }
};

typedef vector<Event> VE;

LL paths(const VE &events, LL curr) {
    LL res = 0;
    for (LL i = curr + 1; i < events.size(); i++) {
        if (events[i].start < events[curr].start + events[curr].lenght) {
            res = max(res, paths(events, i));
        } else {
            res = max(res, 1 + paths(events, i));
            break;
        }
    }

    return res;
}

void task() {

    // vector<long long> v(1000000, 0); // long long 10^5 7.8 MB
    // vector<int> v1(1000000, 0); // int 10^5 3.9 MB
    // vector<bool> v2(10000000, 1); // bool 10^7 1.3 MB
    // vector<bool> v2(100000000, 1); // bool 10^8 11.9 MB
    // while (true);

    LL a, b;

    VE events;
    while (cin >> a >> b) {
        events.emplace_back(a, b);
    }

    LL res = paths(events, 0);
    res++;
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
