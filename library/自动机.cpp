#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_NODE = 100024;
const int MAX_LEN = 1024;

int N, tot;
int children[MAX_NODE][ALPHABET_SIZE], forbid[MAX_NODE], prelink[MAX_NODE], fa[MAX_NODE], ch[MAX_NODE], nextnode[MAX_NODE];
int head[MAX_LEN];

inline int tr(char x) {
    return x - 'a';
}

void Insert(char s[], int value = 1) {
    int pos = 0;
    for (int i = 0; s[i]; i++) {
        int key = tr(s[i]);
        if (children[pos][key] == 0) {
            children[pos][key] = ++tot;
            fa[tot] = pos;
            ch[tot] = key;
            nextnode[tot] = head[i];
            head[i] = tot;
        }
        pos = children[pos][key];
    }
    forbid[pos] += value;
}

void Fix() {
    prelink[0] = 0;
    for (int L = 0; L < MAX_LEN; ++L) {
        for (int i = head[L]; i; i = nextnode[i]) {
            if (fa[i] == 0) {
                prelink[i] = 0;
            } else {
                prelink[i] = prelink[fa[i]];
                for (; prelink[i] && children[prelink[i]][ch[i]] == 0; prelink[i] = prelink[prelink[i]]);
                if (children[prelink[i]][ch[i]] == 0) {
                    prelink[i] = 0;
                } else {
                    prelink[i] = children[prelink[i]][ch[i]];
                }
            }
            forbid[i] += forbid[prelink[i]];
        }
    }
    for (int L = 0; L < MAX_LEN; ++L) {
        for (int i = head[L]; i; i = nextnode[i]) {
            for (int j = 0; j < ALPHABET_SIZE; ++j) {
                if (!children[i][j]) {
                    children[i][j] = children[prelink[i]][j];
                }
            }
        }
    }
}

void clear() {
    memset(children, 0, sizeof children);
    memset(forbid, 0, sizeof forbid);
    memset(prelink, 0, sizeof prelink);
    memset(fa, 0, sizeof fa);
    memset(ch, 0, sizeof ch);
    memset(nextnode, 0, sizeof nextnode);
    memset(head, 0, sizeof head);
    tot = 0;
}

int main() {
}
