#include<vector>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

class segTree {
    vll *tree;
    vll *lazy;
    ll numElements;
public:
    segTree(const vll &arr) {
        auto size = arr.size() * 4;
        tree = new vll(size, 0);
        lazy = new vll(size, 0);
        numElements = arr.size();
        construct(arr, 0, numElements - 1, 0);
    }

    ~segTree() {
        delete tree;
        delete lazy;
    }

    void construct(const vll &arr, ll l, ll r, ll i);

    ll get(ll l, ll r);

    ll get(ll l, ll r, ll ql, ll qr, ll index);
};

void segTree::construct(const vll &arr, ll l, ll r, ll i) {
    if (l <= r) {
        if (l == r)
            (*tree)[i] = arr[l];
        else {
            ll mid = (r - l) / 2 + l;
            ll nextI = 2 * i + 1;
            construct(arr, l, mid, nextI);
            construct(arr, mid + 1, r, nextI + 1);
            (*tree)[i] = (*tree)[nextI] + (*tree)[nextI + 1];
        }
    }
}

ll segTree::get(ll l, ll r) {
    return get(0, numElements - 1, l, r, 0);
}

ll segTree::get(ll l, ll r, ll ql, ll qr, ll index) {
    if ((*lazy)[index] != 0) {
        (*tree)[index] += (qr - ql + 1) * (*lazy)[index];
        if (ql != qr) {
            (*lazy)[index * 2 + 1] += (*lazy)[index];
            (*lazy)[index * 2 + 2] += (*lazy)[index];
        }
        (*lazy)[index] = 0;
    }

    bool outOfRange = l > r || l > qr || r < ql;
    if (outOfRange)
        return 0;

    bool inRange = l >= ql && r <= qr;
    if (inRange)
        return (*tree)[index];

    ll mid = (r - l) / 2 + l;
    ll nextI = 2 * index + 1;
    return get(l, mid, ql, qr, nextI)
           + get(mid + 1, r, ql, qr, nextI + 1);
}

int main() {

    vll arr = {1, 3, 5, 7, 9, 11};

    segTree tree(arr);

    printf("Sum of values in given range must be 15 = %lld\n",
           tree.get(1, 3));

// to be done
//    // Add 10 to all nodes at indexes from 1 to 5.
//    updateRange(n, 1, 5, 10);
//
//    // Find sum after the value is updated
//    printf("Updated sum of values in given range = %d\n",
//           getSum( n, 1, 3));


    return 0;
};