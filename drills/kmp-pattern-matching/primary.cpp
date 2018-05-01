#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

void kmpSearch(const string &pattern, const string &text) {

    vll lps(pattern.length());
    vll lps = computeLps



}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    kmpSearch(pattern, text);
    return 0;
}