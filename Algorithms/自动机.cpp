#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_NODE = 100010;
const int MAX_LEN = 1010;

int N, tot;
int child[MAX_NODE][ALPHABET_SIZE], forbid[MAX_NODE], prelink[MAX_NODE], father[MAX_NODE], now[MAX_NODE], nextnode[MAX_NODE];
int headpoint[MAX_LEN];

inline int tr(char x) {
    return x - 'a';
}

void Insert(char s[], int value = 1) {
    int pos = 0;
    for (int i = 0; s[i]; i++) {
        int key = tr(s[i]);
        if (child[pos][key] == 0) {
            child[pos][key] = ++tot;
            father[tot] = pos;
            now[tot] = key;
            nextnode[tot] = headpoint[i];
            headpoint[i] = tot;
        }
        pos = child[pos][key];
    }
    forbid[pos] += value;
}

void Fix() {
    prelink[0] = 0;
    for (int L = 0; L < MAX_LEN; ++L) {
        for (int i = headpoint[L]; i; i = nextnode[i]) {
            if (father[i] == 0) {
                prelink[i] = 0;
            } else {
                prelink[i] = prelink[father[i]];
                for (; prelink[i] && child[prelink[i]][now[i]] == 0; prelink[i] = prelink[prelink[i]]);
                if (child[prelink[i]][now[i]] == 0) {
                    prelink[i] = 0;
                } else {
                    prelink[i] = child[prelink[i]][now[i]];
                }
            }
            forbid[i] += forbid[prelink[i]];
        }
    }
    for (int L = 0; L < MAX_LEN; ++L) {
        for (int i = headpoint[L]; i; i = nextnode[i]) {
            for (int j = 0; j < ALPHABET_SIZE; ++j) {
                if (!child[i][j]) {
                    child[i][j] = child[prelink[i]][j];
                }
            }
        }
    }
}

void clear() {
    memset(child, 0, sizeof child);
    memset(forbid, 0, sizeof forbid);
    memset(prelink, 0, sizeof prelink);
    memset(father, 0, sizeof father);
    memset(now, 0, sizeof now);
    memset(nextnode, 0, sizeof nextnode);
    memset(headpoint, 0, sizeof headpoint);
    tot = 0;
}

int main() {
}
