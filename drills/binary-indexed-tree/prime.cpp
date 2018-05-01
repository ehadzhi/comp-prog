#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

class bininTree {
    vll *tree;
public:
    bininTree(const vll &arr) {
        tree = new vll(arr.size() + 1, 0);

        for (ll i = 0; i < arr.size(); i++) {
            update(i, arr[i]);
        }
    }

    ~bininTree() {
        delete tree;
    }

    void update(ll i, ll val) {
        i++;
        while (i < tree->size()) {
            tree->at(i) += val;
            i += i & (-i);
        }
    }

    ll getSum(ll i) {
        i++;
        ll res = 0;
        while (i > 0) {
            res += tree->at(i);
            i -= i & (-i);
        }
        return res;
    }
};

int main() {
    vll arr = {1,2,3,4,5,6,7,9};

    bininTree tree(arr);
    cout << "Sum of elements in arr[0..5] should be 21 = "
         << tree.getSum(5);

    arr[3] += 6;
    tree.update(3, 6);

    cout << "\nSum of elements in arr[0..5] after update should be 27 = "
         << tree.getSum(5);

}