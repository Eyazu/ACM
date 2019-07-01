#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 10;
const int maxS = 1<<12;
const int inf = 0x3f3f3f3f;
struct node {
    int u, d;
    node(){
    }
    node(int u, int d):u(u), d(d){
    }
};
vector<node> G[maxn];
queue<int> Q;
bool in[maxn][maxS];
int bit[maxn], spe[maxn], be[maxn], num[maxn];
int f[maxn][maxS];
int n, k;
void spfa() {
    while(!Q.empty()) {
        int t = Q.front(); Q.pop();
        int u = t / 10000, s = t % 10000;
//        printf("u:%d\n", u);
        in[u][s] = 0;
        for(int i = 0; i < G[u].size(); i++) {
            node p = G[u][i];
            int v = p.u, w = p.d;
            if(f[v][s] > f[u][s] + w) {
                f[v][s] = f[u][s] + w;
                if(!in[v][s]) {
                    in[v][s] = 1;
                    Q.push(v*10000+s);
//                    printf("==%d===%d\n", v, s);
                }
            }
        }
    }
}
bool check(int S) {
    int tmp[maxn];
    memset(tmp, 0, sizeof(tmp));
    for(int i = 0; i < k; i++) {
        if(S & (1<<i)) tmp[be[spe[i]]]++;
    }
    for(int i = 1; i <= n; i++) 
        if(tmp[i] && tmp[i] != num[i]) return false;
    return true;
}
void solve() {
    int cntS = 1 << k;
    int dp[maxS];
    while(!Q.empty()) Q.pop();
    memset(f, inf, sizeof(f));
    memset(in, 0, sizeof(in));
    memset(bit, 0, sizeof(bit));
     
    for(int i = 0; i < k; i++) {    
        bit[spe[i]] = 1<<i; f[spe[i]][bit[spe[i]]] = 0;
    }
    for(int S = 0; S < cntS; S++) {
        for(int i = 1; i <= n; i++) {
            for(int j = (S-1)&S; j; j = (j-1)&S) {    // 子集 
                f[i][S] = min(f[i][S], f[i][j] + f[i][S-j]);
            }
            if(f[i][S] < inf && !in[i][S]) {
                Q.push(i*10000+S); in[i][S] = 1;
//                printf("%d--%d\n", i, S);
            } 
        }
        spfa();
    }
    memset(dp, 0x3f, sizeof(dp));
    for(int S = 0; S < cntS; S++){
        for(int i = 1; i <= n; i++)
            dp[S] = min(dp[S], f[i][S]);
 
    }
 //   printf("%d\n", dp[cntS-1]);    
     
    for(int S = 0; S < cntS; S++) 
        if(check(S)) {
            for(int j = S&(S-1); j; j = (j-1)&S)
                if(check(j)) {
                    dp[S] = min(dp[S], dp[j] + dp[S-j]);
                }
        }
    printf("%d\n", dp[cntS-1]);
}
void init() {
    memset(num, 0, sizeof(num));
}
int main() {
//    freopen("hdu4085.txt", "r", stdin);
//    freopen("wrong.txt", "w", stdout);
    int T;
    int m;
    scanf("%d%d%d", &n, &m, &k);
    int u, v, w;
    init();
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(node(v, w));
        G[v].push_back(node(u, w));
    } 
     
    int a, b;
    for(int i = 0; i < k; i++) {
        scanf("%d%d", &a, &b);
        spe[i] = b;
        be[b] = a;
        num[a]++;
    }
    solve();
    for(int i = 0; i <= n; i++) G[i].clear();
     
    return 0;
}
﻿
