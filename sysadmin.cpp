//#include <iostream>
//
//using namespace std;
//typedef long long ll;
//
//ll pow(ll a, ll b) {
//    return b > 0 ? a * pow(a, b - 1) : 1;
//}
//
//int main() {
//    ll n, p;
//
//    cin >> p >> n;
//    ll a[n];
//
//    for (ll i = 0; i < n; i++) {
//        cin >> a[i];
//    }
//
//    for (ll i = 0; i < n; i++) {
//        ll tp = pow(3, p), offset = 0;
//        for (ll j = 1; j <= p + 1; j++) {
//            ll i1 = offset + tp / 3;
//            ll i2 = offset + (tp / 3) * 2 - 1;
//            if (tp == 1 || a[i] - 1 >= i1 && a[i] - 1 <= i2) {
//                cout << j << endl;
//                break;
//            }
//            if (a[i] - 1 > i2)
//                offset += (tp * 2) / 3;
//            tp /= 3;
//        }
//    }
//}