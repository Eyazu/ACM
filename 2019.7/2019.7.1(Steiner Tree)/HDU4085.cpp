#include<bits/stdc++.h>
using namespace std;
const int maxn = 55;
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
int bit[maxn];
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
    int a = 0;
    for(int i = 1; i <= k; i++) {
        if(S & bit[i]) a++;
        if(S & bit[n-i+1]) a--;
    }
    return a == 0;
}
void solve() {
    int cntS = 1 << (2*k);
    int dp[maxS];
    while(!Q.empty()) Q.pop();
    memset(f, inf, sizeof(f));
    memset(in, 0, sizeof(in));
    memset(bit, 0, sizeof(bit));
    
    for(int i = 1; i <= k; i++) {    
        bit[i] = 1<<(i-1); f[i][bit[i]] = 0;
        bit[n-i+1] = 1<<(k+i-1); f[n-i+1][bit[n-i+1]] = 0;
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
        

    for(int S = 0; S < cntS; S++) 
        if(check(S)) {
            for(int j = S&(S-1); j; j = (j-1)&S)
                if(check(j)) {
                    dp[S] = min(dp[S], dp[j] + dp[S-j]);
                }
        }
    if(dp[cntS-1] >= inf) printf("No solution\n");
    else printf("%d\n", dp[cntS-1]);
}
int main() {
//    freopen("hdu4085.txt", "r", stdin);
    int T;
    int m;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &k);
        int u, v, w;
        
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(node(v, w));
            G[v].push_back(node(u, w));
        } 
        solve();
        for(int i = 0; i <= n; i++) G[i].clear();
    }
    return 0;
}
