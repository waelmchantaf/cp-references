#include <vector>

using namespace std;

struct trieNode {
    int child[2], cnt;
    
    trieNode () {
        child[0] = child[1] = -1;
        cnt = 0;
    }
};
 
struct Trie {
    vector <trieNode> trie;
    int root, id;
    
    Trie () {
        id = 0;
        root = 0;
        trie.clear();
        
        trieNode tmp;
        trie.push_back(tmp);
    }
    
    void clear() {
        id = 0;
        root = 0;
        trie.clear();
        
        trieNode tmp;
        trie.push_back(tmp);
    }
    
    int fetchNode() {
        id++;
        
        trieNode tmp;
        trie.push_back(tmp);
        
        return id;
    }
    
    void add(int mask) {
        int cur = root;
        
        for (int bit = 29; bit >= 0; bit--) {
            int x = (((1 << bit) & mask) != 0);

            if (trie[cur].child[x] == -1) {
                trie[cur].child[x] = fetchNode();
            }
            
            cur = trie[cur].child[x];
            trie[cur].cnt++;
        }
    }
} trie;