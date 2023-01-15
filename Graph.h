//
// Created by Khoa on 20/12/2022.
//

#ifndef DSALAB_GRAPH_H
#define DSALAB_GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <functional>


/*
 * Implementation of Graph data structure
 *
 * A graph consists of two small data structure called Vertex and Edge.
 * A graph list is basically an array of vertices (strucuture Vertex). Each
 * vertex will store its adjacent edges in a list. This method is called
 * adjacency list. There is also two other method of storing which is
 * adjacency matrix and edge list.
 */
template <class T = int, class W = int, bool direct = true>
class Graph {
protected:
    class Edge {
    public:
        W   weight;
        int vertexIndex;
    };

    class Vertex {
    public:
        size_t              key;
        T                   data;
        std::vector<Edge>   edgeList;
        bool                flag;
        int                 dist;
    };

    std::vector<Vertex>  G;
public:
    size_t E;
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
        E++;
    }

    /*
     * Breadth-First Search (BFS)
     *
     * Breadth first search is one of the basic and essential searching algorithms on graphs.
     * As a result of how the algorithm works, the path found by breadth first search to any
     * node is the shortest path to that node, i.e. the path that contains the smallest number
     * of edges in unweighted graphs.
     *
     * @param {function} op A function to operator in Breath-First order
     * @param {number} source The source vertex
     * @return {vector} An array representing the shortest path from source to every vertex
     *
     * Time complexity: O(V + E)
     *
     * Note: clear vertex information before use if your want to start from the beginning
     */
    std::vector<int> BFS(std::function<void (const T & data)> op, int source = 0) {
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

    /*
     * Depth-First Search (Stack Iteration Implementation)
     *
     * Depth First Search is one of the main graph algorithms.
     * Depth First Search finds the lexicographical first path in the
     * graph from a source vertex u to each vertex. Depth First Search
     * will also find the shortest paths in a tree (because there only
     * exists one simple path), but on general graphs this is not the case.
     *
     * @param {function} op A function to operator in Depth-First order
     * @param {number} source The source vertex
     * @return {vector} An array representing the shortest path from source to every vertex
     *
     * Time complexity: O(V + E)
     *
     * Note: clear vertex information before use if your want to start from the beginning
     */
    std::vector<int> DFSPreOrder(std::function<void (const T & data)> op, int source = 0) {
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

    /*
     * Depth-First Search (Recursion Implementation)
     *
     * Depth First Search is one of the main graph algorithms.
     * Depth First Search finds the lexicographical first path in the
     * graph from a source vertex u to each vertex. Depth First Search
     * will also find the shortest paths in a tree (because there only
     * exists one simple path), but on general graphs this is not the case.
     *
     * Time complexity: O(V + E)
     *
     * Note: clear vertex information before use if your want to start from the beginning
     */
    std::vector<int> DFSPostOrder(std::function<void (const T & data)> op, int source = 0) {
        // TODO
    }

    struct sort_option {
        bool operator()(Vertex &a, Vertex &b) { return a.dist > b.dist; }
    };

    /*
     * Shortest Paths Problem (Single-sourced): Djikstra's algorithm
     *
     * Shortest Paths Problem is finding the shortest path between two vertices.
     * The algorithm only describe how to get the shortest path from one source
     * to another with the condition of all weights must be POSITIVE.
     *
     * @param {number} fromKey The index of the initial vertex
     * @param {number} toKey The index of the destination vertex
     * @return {array} an array representing all shortest paths from any vertex to the 'toKey' vertex
     *
     * Time complexity:
     * List, Array Implementation: O(V^2)
     * Priority Queue Implementation: O(E logV)
     */
    std::vector<int> Djikstra(int fromKey, int toKey) {
        clearVertex();
        std::vector<int> path(G.size(), -1);
        std::priority_queue<Vertex, std::vector<Vertex>, sort_option> pq;
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

    /*
     * Topological Sort
     *
     * @return {array} An array of Vertex in topological order
     *
     * Algorithm:
     *      1.  call DFS to compute the finishing time of v * f for each v
     *      2.  as each vertex is finished, add to the head of the list
     *      3.  return the list
     */
    std::vector<T> topologicalSort() {
        clearVertex();
        std::vector<T> result;
        for (size_t i = 0; i < G.size(); i++) {
            if (G[i].flag == false) {
                DFSPostOrder([&result](const T& data) {
                    result.push_back(data);
                }, i);
            }
        }

        return result;
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
            std::cout << "] " << (G[i].flag == true ? "visited" : "not visited") << '\n';
        }
        std::cout << std::endl;
    }
};

#endif //DSALAB_GRAPH_H
