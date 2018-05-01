
#include <iostream>

using namespace std;

typedef long long ll;

long exponentiation(ll base, ll exp, ll prime);

int main() {
    ll base = 5;
    ll exp = 100000;
    ll prime = 1000000007L;
    long modulo = exponentiation(base, exp, prime);

    cout << "Should 754573817 == " << modulo << endl;

    return 0;
}

long exponentiation(ll base, ll exp, ll prime) {

    ll t = 1;
    while (exp > 0) {
        if (exp % 2 != 0) {
            t = (t * base) % prime;
        }
        base = (base * base) % prime;
        exp /= 2;
    }
    return t % prime;
}