#include <vector>
#include <cstdio>

using namespace std;

typedef long long LL;
typedef vector<LL> VLL;

class segTree {
public:
    VLL *tree;
    VLL *lazy;
    LL numElements;

    segTree(const VLL &arr) {
        numElements = arr.size();
        tree = new VLL(4 * numElements, 0);
        lazy = new VLL(4 * numElements, 0);

        construct(arr, 0, numElements - 1, 0);
    }

    void construct(const VLL &arr, LL l, LL r, LL i) {
        if (l <= r) {
            if (l == r) {
                tree->at(i) = arr[l];
            } else {
                LL mid = (r - l) / 2 + l;
                LL nextI = 2 * i + 1;
                construct(arr, l, mid, nextI);
                construct(arr, mid + 1, r, nextI + 1);

                tree->at(i) = tree->at(nextI) + tree->at(nextI + 1);
            }
        }
    }

    LL get(LL l, LL r) {
        return get(l, r, 0, numElements - 1, 0);
    }

    LL get(LL ql, LL qr, LL l, LL r, LL i) {
        bool outOfRange = l > r || l > qr || r < ql;
        if (outOfRange) {
            return 0;
        }

        bool inRange = l >= ql && r <= qr;
        if (inRange) {
            return tree->at(i);
        }
        LL mid = (r - l) / 2 + l;
        LL nextI = 2 * i + 1;
        return get(ql, qr, l, mid, nextI) + get(ql, qr, mid + 1, r, nextI + 1);
    }

    ~segTree() {
        delete tree;
        delete lazy;
    }

};

int main() {

    VLL arr = {1, 3, 5, 7, 9, 11};

    segTree tree(arr);

    printf("Sum of values in given range = %lld\n",
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