#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <iomanip>

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

char encode(char ch) {
    static unordered_map<char, char> codes = {{'A', '\0'},
                                              {'E', '\0'},
                                              {'I', '\0'},
                                              {'O', '\0'},
                                              {'U', '\0'},
                                              {'Y', '\0'},
                                              {'W', '\0'},
                                              {'H', '\0'},
                                              {'B', '1'},
                                              {'P', '1'},
                                              {'V', '1'},
                                              {'F', '1'},
                                              {'C', '2'},
                                              {'S', '2'},
                                              {'K', '2'},
                                              {'J', '2'},
                                              {'Q', '2'},
                                              {'X', '2'},
                                              {'Z', '2'},
                                              {'G', '2'},
                                              {'D', '3'},
                                              {'T', '3'},
                                              {'L', '4'},
                                              {'M', '5'},
                                              {'N', '5'},
                                              {'R', '6'}};
    return codes.find(ch)->second;
}

string soundex(const string &name) {
    string res = "0000";

    char last_one_encoded = '\0';
    for (int i = 0, j = 0; i < res.size() && j < name.size(); j++) {
        if (i == 0) {
            res[i] = name[j];
            last_one_encoded = encode(res[i]);
            i++;
            continue;
        }
        char encoded = encode(name[j]);
        if (encoded != '\0' && encoded != last_one_encoded) {
            res[i] = encoded;
            last_one_encoded = encoded;
            i++;

        }
        if (encoded == '\0') {
            last_one_encoded = encoded;
        }
    }

    return res;
}

void task() {

    string name;
    while (!cin.eof()) {
        cin >> name;
        string encoded = soundex(name);
        cout << name << " -> " << encoded << endl;
    }
    cout << setw(20) << "END OF OUTPUT" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
