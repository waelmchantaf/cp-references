#include <vector>
#include <stack>

using namespace std;

struct VirtualTree {
    /*
        1. initialize with proper parameters
        2. add edges
        3. call dfsCalcOrders
        4. For each query:
            * call queryBuildVirtualTree
            * call queryCalcAnswer (DO WHATEVER YOU WANT TO FIND THE ANSEWR)
            * call queryClear
    */ 
    
    vector <vector<int>> adj, adjQuery;
    vector <vector<int>> up;
    vector <bool> isSpecial;
    vector <int> in, out, pa, builtTreeVertices;
    int counter, root, l, queryRoot;
    
    VirtualTree(int SZ, int ROOT) {
        vector<int> emptyVector;
        emptyVector.clear();

        adj.clear();
        adj.resize(SZ + 1, emptyVector);
        
        adjQuery.clear();
        adjQuery.resize(SZ + 1, emptyVector);
        
        in.clear();
        in.resize(SZ + 1);
        
        out.clear();
        out.resize(SZ + 1);
        
        counter = 0;
        root = ROOT;
        
        l = log2(SZ);
        
        up.clear();
        up.resize(SZ + 1, vector<int>(l + 1, 0));
        
        pa.clear();
        pa.resize(SZ + 1, 0);
        
        isSpecial.clear();
        isSpecial.resize(SZ + 1, 0);
        
        queryRoot = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfsCalcOrders(int v, int p) {
        in[v] = ++counter;
        up[v][0] = p;
        
        for (int i = 1; i <= l; i++) 
            up[v][i] = up[up[v][i - 1]][i - 1];
        
        for (auto u: adj[v]) {
            if (u == p)
                continue;
            
            dfsCalcOrders(u, v);
        }
        
        out[v] = ++counter;
    }
    
    bool isAncestorOf(int u, int v) {
        return (in[u] <= in[v]) && (out[u] >= out[v]);
    }
    
    int lca(int u, int v) {
        if (isAncestorOf(u, v)) return u;
        if (isAncestorOf(v, u)) return v;
        
        for (int i = l; i >= 0; i--)
            if (!isAncestorOf(up[u][i], v))
                u = up[u][i];
        return up[u][0];
    }
    
    void queryBuildVirtualTree(vector<int>& specialVertices) {
        sort(specialVertices.begin(), specialVertices.end(), [&](int u, int v) {
           return in[u] < in[v]; 
        });
        
        for (int i = 0; i < (int) specialVertices.size(); i++) {
            if (i + 1 < (int) specialVertices.size())
                builtTreeVertices.push_back(lca(specialVertices[i], specialVertices[i + 1]));
            builtTreeVertices.push_back(specialVertices[i]);
            
            isSpecial[specialVertices[i]] = true;
        }
        
        sort(builtTreeVertices.begin(), builtTreeVertices.end(), [&](int u, int v){
           return in[u] < in[v]; 
        });
        
        int len = unique(builtTreeVertices.begin(), builtTreeVertices.end()) - builtTreeVertices.begin();
        builtTreeVertices.resize(len);
        
        stack <int> st;
        for (auto u: builtTreeVertices) {
            while (st.size() && !isAncestorOf(st.top(), u))
                st.pop();
                
            if (st.empty()) {
                queryRoot = u;
            } else pa[u] = st.top();
            
            st.push(u);
        }
        
        for (auto u: builtTreeVertices) {
            if (u != queryRoot)
                adjQuery[pa[u]].push_back(u);
        }
    }
    
    int queryGetAnswer() {
        /*
         - you have adjQuery with ONLY CHILDREN (NO PARENT)
         - you have queryRoot
         - you have builtTreeVertices sorted
         - you have isSpecial[v]
        */
        
        
        //return answer
    }
    
    void queryClear() {
        queryRoot = 0;
        
        for (auto u: builtTreeVertices) {
            pa[u] = 0;
            isSpecial[u] = false;
            adjQuery[u].clear();
        }
        
        builtTreeVertices.clear();
    }
};
