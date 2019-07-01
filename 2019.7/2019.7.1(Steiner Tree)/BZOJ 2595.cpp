#include<bits/stdc++.h>
using namespace std;
const int maxn = 12;
const int maxS = 1<<12;
const int inf = 0x3f3f3f3f;
int G[maxn][maxn];
int Ans[maxn][maxn];
int pre[maxn][maxn][maxS];
struct node {
    int x, y;
    node(){
    }
    node(int x, int y):x(x), y(y){
    }
};
vector<node> p;
queue<int> Q;
int n, m, k, f[maxn][maxn][maxS];
bool in[maxn][maxn];
int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};
int hash(int x, int y, int s) {
    return s*10000 + x*100 + y;
}
void spfa(int S) {
    while(!Q.empty()) {
        int top = Q.front(); Q.pop();
        int sx = top / 100, sy = top % 100;
        in[sx][sy] = 0;
        for(int i = 0; i < 4; i++) {
            int tx = sx + dx[i], ty = sy + dy[i];
            if(tx < 1 || tx > n || ty < 1 || ty > m) continue;
            if(f[tx][ty][S] > f[sx][sy][S] + G[tx][ty]) {
                f[tx][ty][S] = f[sx][sy][S] + G[tx][ty];
                pre[tx][ty][S] = hash(sx, sy, S);
                if(!in[tx][ty]) {
                    in[tx][ty] = 1;
                    Q.push(hash(tx, ty, 0));
                }
            }
        }
    }
}
void find(int x, int y, int k) {
 
//  printf("%d %d %d\n", x, y, k);
 
    int p = pre[x][y][k];
    if(p < 0) return;
    int x2 = p % 10000 / 100, y2 = p % 100, k2 = p / 10000;
//  printf("%d %d %d\n", x2, y2, k2);
    if(G[x][y]) Ans[x][y] = 2;
    else Ans[x][y] = 1;
    find(x2, y2, k2);
    if(x2 == x && y2 == y) 
    find(x, y, k-k2);
}
void solve() {
    int cntS = 1<<k;
    memset(f, 0x3f, sizeof(f));
    memset(pre, -1, sizeof(pre));
    for(int i = 0; i < p.size(); i++) {
        f[p[i].x][p[i].y][1<<i] = 0;
//      printf("%d--%d\n", p[i].x, p[i].y);
    } 
    for(int S = 1; S < cntS; S++) {
        for(int x = 1; x <= n; x++)  for(int y = 1; y <= m; y++) {
            for(int sub = (S-1)&S; sub; sub = (sub-1)&S) {
                if(f[x][y][S] > f[x][y][sub] + f[x][y][S-sub] - G[x][y]) {
                    f[x][y][S] = f[x][y][sub] + f[x][y][S-sub] - G[x][y];
                    pre[x][y][S] = sub*10000+x*100+y;
                }
                 
            }
            if(f[x][y][S] < inf) {
                Q.push(hash(x, y, 0)); in[x][y] = 1;
            }
        }
        spfa(S);
    }
    int ans = inf;
    int x = p[0].x, y = p[0].y;
    printf("%d\n", f[x][y][cntS-1]);
//  printf("%d %d\n", x, y);
    memset(Ans, 0, sizeof(Ans));
 
    find(x, y, cntS-1);
     
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(G[i][j] == 0) {
            printf("x");continue;}
            if(Ans[i][j] == 0) printf("_");
            else printf("o");
        }
        printf("\n");
    }   
}
int main() {
//  freopen("data.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    k = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            scanf("%d", &G[i][j]);
            if(!G[i][j]) {
                k++;
                p.push_back(node(i, j));
            }
        }
    solve();
    return 0;
}
﻿
