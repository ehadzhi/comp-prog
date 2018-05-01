#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

typedef vector<ll> vll;

class bininTree {
    vll *cont;
public:
    bininTree(const vll &arr) {
        auto n = arr.size();
        cont = new vll(n + 1, 0);
        for (ll i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }

    ~bininTree() {
        delete (cont);
    }

    void update(ll i, ll val) {
        i++;
        while (i < cont->size()) {
            cont->at(i) += val;
            i += i & (-i);
        }
    }

    ll getSum(ll i) {
        i++;
        ll res = 0;
        while (i > 0) {
            res += cont->at(i);
            i -= i & (-i);
        }
        return res;
    }
};

int main() {
    vll arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    bininTree tree(arr);

    cout << "Sum of elements in arr[0..5] should be 21 = "
         << tree.getSum(5);
}