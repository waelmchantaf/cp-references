#include <bits/stdc++.h>

using namespace std;

struct SegmentTreeNonLazy {
    int sz;
    vector <int> segTree;
    
    SegmentTreeNonLazy(int SZ) {
        sz = SZ + 5;
        segTree.resize(4 * sz, 0);
    }
    
    int getQuery(int v, int l, int r, int L, int R) {        
        if (L > R || l > r)
            return 0;
            
        if (l > R || r < L)
            return 0;
            
        if (L <= l && r <= R) 
            return segTree[v];
        
        int mid = (l + r) / 2;
        return max(getQuery(2 * v, l, mid, L, R),
            getQuery(2 * v + 1, mid + 1, r, L, R)); 
    }
    
    void updateValue(int v, int l, int r, int idx, int val) {        
        if (idx > r || idx < l)
            return;
        
        if (l == r) {
            segTree[v] = val;
            
            return;
        }
        
        int mid = (l + r) / 2;
        updateValue(2 * v, l, mid, idx, val);
        updateValue(2 * v + 1, mid + 1, r, idx, val);
        
        segTree[v] = max(segTree[2 * v], segTree[2 * v + 1]);
    }
};