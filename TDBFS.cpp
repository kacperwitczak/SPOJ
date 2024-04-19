#include <iostream>
#include <vector>
#include <queue>
 
class Graph {
    private: 
 
    std::vector<std::vector<short>> adjList;
    int graphSize;
    public:
 
    Graph(int n) {
        graphSize = n + 1;
        adjList.resize(n + 1);
    }
 
    void addVertexAndNeighbourhood() {
        short vertexID;
        std::cin >> vertexID;
        short numberOfNeighbours;
        std::cin >> numberOfNeighbours;
        for (int i = 0; i < numberOfNeighbours; i++) {
            short neighbour;
            std::cin >> neighbour;
            adjList[vertexID].push_back(neighbour);
        }
    }
 
    void BFS(short startVertex) {
        std::vector<bool> visited(graphSize + 1);
        fill(visited.begin(), visited.end(), false);
        std::queue<short> q;
        q.push(startVertex);
        visited[startVertex] = true;
        while (!q.empty()) {
            short v = q.front();
            q.pop();
            std::cout << v;
            for (auto& u : adjList[v]) {
                if (!visited[u]) {
                    q.push(u);
                    visited[u] = true;
                }
            }
            if (q.empty()) {
                std::cout << '\n';
            }
            else {
                std::cout << ' ';
            }
        }
    };
 
    void DFS(short startVertex) {
        std::vector<bool> visited(graphSize + 1);
        fill(visited.begin(), visited.end(), false);
        DFSHelper(startVertex, visited);
        std::cout << '\n';
    };
 
    void DFSHelper(short v, std::vector<bool>& vis) {
        std::cout << v;
        vis[v] = true;
        for (auto& u : adjList[v]) {
            if (!vis[u]) {
                std::cout << ' ';
                DFSHelper(u,vis);
            }
        }
    }
 
};
 
int main()
{
 
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << "graph " << i + 1 << '\n';
        int graphSize;
        std::cin >> graphSize;
        Graph g(graphSize);
        for (int j = 0; j < graphSize; j++) {
            g.addVertexAndNeighbourhood();
        }
        short queryParam1, queryParam2;
        while (1) {
            std::cin >> queryParam1 >> queryParam2;
            if (queryParam1 == 0 && queryParam2 == 0) {
                break;
            }
            if (queryParam2 == 1) {
                g.BFS(queryParam1);
            }
            else {
                g.DFS(queryParam1);
            }
        }
    }
} 
