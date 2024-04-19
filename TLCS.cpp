//zrodlo, z ktÃ³rego korzystaÅem: https://www.youtube.com/watch?v=sSno9rV8Rhg
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
 
void lcs_dp(std::vector<std::vector<int>>& dp, std::string& x, std::string& y,int n, int m) {
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = std::max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
}
 
struct PathElem{
    int x;
    int y;
};
 
std::vector<PathElem> reconstructPath(std::vector<std::vector<int>>& dp, int y, int x) {
    std::vector<PathElem> path;
    while (x > 0 && y > 0) {
        if (dp[y][x] == dp[y - 1][x]) {
            y--;
        }
        else if (dp[y][x] == dp[y][x - 1]) {
            x--;
        }
        else {
            x--;
            y--;
            path.push_back({ y , x });
        }
    }
 
    return path;
}
 
int main()
{
    int N;
    int counter = 1;
    std::cin >> N;
    while (N > 0) {
        int n,m;
        std::string x,y;
        std::cin >> n >> x >> m >> y;
        std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
        lcs_dp(dp,x,y,n,m);
        std::vector<PathElem> path = reconstructPath(dp,n,m);
        if (path.size() > 0) {
            std::cout << "case " << counter << " Y\n";
            std::cout << path.size() << '\n';
            for (int i = path.size() - 1; i >= 0; i--) {
                std::cout << x[path[i].x] << ' ' << path[i].x + 1 << ' ' << path[i].y + 1 << '\n';
            }
        }
        else {
            std::cout << "case " << counter << " N\n";
        }
        counter++;
        N--;
    }
 
    return 0;
}
 
