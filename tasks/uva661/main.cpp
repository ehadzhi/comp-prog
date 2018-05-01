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

    int seq = 0;
    while (true) {
        int num_devices, operations, fuse_capacity, total = 0, max_c = 0;
        cin >> num_devices >> operations >> fuse_capacity;
        if (num_devices == 0)
            break;
        int devices[num_devices][2] = {0};
        for (int i = 0; i < num_devices; i++) {
            cin >> devices[i][0];
        }
        for (int i = 0; i < operations; i++) {
            int device;
            cin >> device;
            if (devices[device][1]) {
                devices[device][1] = 0;
                total -= devices[device][0];
            } else {
                devices[device][1] = 1;
                total += devices[device][0];
                max_c = max(total, max_c);
                if (fuse_capacity < total)
                    break;
            }
        }
        cout << "Sequence " << ++seq << endl;
        cout << (fuse_capacity >= total ? "Fuse was not blown." : "Fuse was blown.") << endl;
        if (fuse_capacity >= total)
            cout << "Maximal power consumption was " << max_c << " amperes." << endl;
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
