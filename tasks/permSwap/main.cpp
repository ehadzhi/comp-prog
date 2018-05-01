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

typedef unsigned int LL;
typedef vector<LL> VLL;

LL mSort(VLL &nums, LL l, LL r, VLL& mergeTable) {
    LL n = r - l, res = 0, mid = (r - l) / 2 + l;
    if (n < 2)
        return res;
    res += mSort(nums, l, mid, mergeTable);
    res += mSort(nums, mid, r, mergeTable);

    LL i = 0, i1 = l, i2 = (l + r) / 2;
    while (i1 < mid && i2 < r) {
        if (nums[i1] > nums[i2]) {
            mergeTable[i] = nums[i2];
            i2++;
            res += mid - i1;
        } else {
            mergeTable[i] = nums[i1];
            i1++;
        }
        i++;
    }
    while (i1 < mid) {
        mergeTable[i++] = nums[i1++];
    }
    while (i2 < r) {
        mergeTable[i++] = nums[i2++];
    }
    for (LL i = l; i < r; i++) {
        nums[i] = mergeTable[i - l];
    }

    return res;
}

void task() {
    LL n;
    cin >> n;
    VLL nums;
    nums.reserve(n);

    for (LL i = 0; i < n; i++) {
        LL a;
        cin >> a;
        nums.push_back(a);
    }

    VLL table = VLL(nums.size());
    LL res = mSort(nums, 0, nums.size(), table);

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
