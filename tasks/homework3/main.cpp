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


void task() {

    string str;
    vector<int> words;
    while (cin >> str) {
        words.push_back(str.length());
    }
    int minLoss = INT_MAX;
    int minLossWidth = INT_MAX;
    int minLossLines = INT_MAX;
    for (int i = 1, word = 0, sum = 0, loss = 0; i <= 10000; i++) {
        int numLines = 0;
        while (word < words.size()) {
            while (sum + 1 + words[word] < i) {
                sum += 1 + words[word];
                word++;
            }
            if (sum + 1 + words[word] > i) {
                loss += 1 + words[word];
            }
            word++;
            numLines++;
            sum = 0;
        }
        if (loss < minLoss) {
            minLoss = loss;
            minLossWidth = i;
            minLossLines = numLines;
        }
        loss = 0;
    }

    cout << minLossLines << " " << minLossWidth << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
