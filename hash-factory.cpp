#include <string>

using namespace std;

struct HashFactory {
    string s;
    long long base, mod;
    vector <long long> prefixHash, suffixHash;
    int N;
    
    HashFactory(string _s, int _base, int _mod) {
        //give original string without padding
        //use 1-index
        
        s = _s;
        base = _base;
        mod = _mod;
        
        N = s.length();
        s = "3" + s;
        
        prefixHash.resize(N + 1, 0);
        suffixHash.resize(N + 2, 0);
        
        long long p = 1;
        
        for (int i = 1; i <= N; i++) {
            prefixHash[i] = (prefixHash[i - 1] + 1ll * (s[i] - 'a' + 1) * p % mod) % mod;
            p = p * base % mod;
        }
        
        p = 1;
                
        for (int i = N; i >= 1; i--) {
            suffixHash[i] = (suffixHash[i + 1] + 1ll * (s[i] - 'a' + 1) * p % mod) % mod;
            p = p * base % mod;
        }
    }
    
    long long bp(long long a, long long b) {
        if (b == 0)
            return 1;
            
        long long mid = bp(a, b / 2);
        if (b & 1) {
            return mid * mid % mod * a % mod;
        } else {
            return mid * mid % mod;
        }
    }
    
    bool isPalindrome(int l, int r) {
        long long x = prefixHash[r] - prefixHash[l - 1];
        x %= mod;
        x += mod;
        x %= mod;
        
        
        long long y = suffixHash[l] - suffixHash[r + 1];
        y %= mod;
        y += mod;
        y %= mod;
        
        x = x * bp((bp(base, l - 1)), mod - 2) % mod;
        y = y * bp((bp(base, N - r)), mod - 2) % mod;
        
        return (x == y);
    }
};