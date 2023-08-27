#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
int N;

using Matrix = array<array <long long, 101>, 101>; 
 
Matrix mul (Matrix a, Matrix b) {
    Matrix res;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            
            res[i][j] = 0;
            for (int k = 1; k <= N; k++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    
    return res;
}
