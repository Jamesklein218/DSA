//
// Created by Khoa on 20/12/2022.
//

#ifndef DSALAB_GRAPH_H
#define DSALAB_GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <functional>

template <class T = int, class W = int, bool direct = true>
class Graph {
protected:
    struct Edge {
        W   weight;
        int vertexIndex;
    };

    struct Vertex {
        size_t                 key;
        T                   data;
        std::vector<Edge>   edgeList;
        bool                flag;
        int                 dist;
    };

    std::vector<Vertex>  G;
public:
    Graph() {}
    int insertVertex(T data) {
        Vertex newVertex{G.size(), data, std::vector<Edge>(), 0, 0};
        G.push_back(newVertex);
        return G.size() - 1;
    }
    void insertEdge(int fromKey, int toKey, W weight = (W)0) {
        Edge newEdge {weight, toKey};
        G[fromKey].edgeList.push_back(newEdge);
        if (direct == false) {
            Edge newEdge {weight, fromKey};
            G[toKey].edgeList.push_back(newEdge);
        }
    }
    std::vector<int> BFS(std::function<void (const T & data)> op, int source = 0) {
        clearVertex();
        std::vector<int> path(G.size(), -1);
        std::queue<int> q;
        q.push(source);
        G[source].flag = true;

        while (q.empty() == false) {
            int currentVertexIdx = q.front();
            op(G[currentVertexIdx].data);
            q.pop();

            for (size_t i = 0; i < G[currentVertexIdx].edgeList.size(); i++) {
                Edge currentEdge = G[currentVertexIdx].edgeList[i];
                if (G[currentEdge.vertexIndex].flag == false) {
                    q.push(currentEdge.vertexIndex);
                    G[currentEdge.vertexIndex].flag = true;
                    path[currentEdge.vertexIndex]   = currentVertexIdx;
                }
            }
        }

        return path;
    }

    std::vector<int> DFS(std::function<void (const T & data)> op, int source = 0) {
        clearVertex();
        std::vector<int> path(G.size(), -1);
        std::stack<int> s;
        s.push(source);
        G[source].flag = true;

        while (s.empty() == false) {
            int currentVertexIdx = s.top();
            op(G[currentVertexIdx].data);
            s.pop();

            for (int i = G[currentVertexIdx].edgeList.size() - 1; i >= 0; i--) {
                Edge currentEdge = G[currentVertexIdx].edgeList[i];
                if (G[currentEdge.vertexIndex].flag == false) {
                    s.push(currentEdge.vertexIndex);
                    G[currentEdge.vertexIndex].flag = true;
                    path[currentEdge.vertexIndex]   = currentVertexIdx;
                }
            }

        }
        return path;
    }

    struct option {
        bool operator()(Vertex &a, Vertex &b) { return a.dist > b.dist; }
    };

    std::vector<int> Djikstra(int fromKey, int toKey) {
        clearVertex();
        std::vector<int> path(G.size(), -1);
        std::priority_queue<Vertex, std::vector<Vertex>, option> pq;
        G[fromKey].dist = 0;
        pq.push(G[fromKey]);
        while (pq.empty() == false) {
            Vertex currentVertex = pq.top();
            pq.pop();
            for (size_t i = 0; i < currentVertex.edgeList.size(); i++) {
                Edge neighborEdge = currentVertex.edgeList[i];
                int neighborVertexIndex = neighborEdge.vertexIndex;
                if (currentVertex.dist + neighborEdge.weight < G[neighborVertexIndex].dist) {
                    G[neighborVertexIndex].dist = currentVertex.dist + neighborEdge.weight;
                    pq.push(G[neighborVertexIndex]);
                    path[neighborVertexIndex] = currentVertex.key;
                }
            }
        }
        return path;
    }

    void clearVertex() {
       for (size_t i = 0; i < G.size(); i++) {
           G[i].flag = false;
           G[i].dist = INT_MAX;
       }
    };
    void printAll() const {
        for (size_t i = 0; i < G.size(); i++) {
            std::cout << G[i].data << " [";
            for (size_t j = 0; j < G[i].edgeList.size(); j++) {
                std::cout << G[G[i].edgeList[j].vertexIndex].data << ",";
            }
            std::cout << "]" << '\n';
        }
    }
};

#endif //DSALAB_GRAPH_H
