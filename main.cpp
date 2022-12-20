#include "main.h"

#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "BTree.h"
#include "DLinkedList.h"
#include "Graph.h"
#include "HashMap.h"
#include "Heap.h"
#include "SplayTree.h"
#include "Sorting.h"

using namespace std;

void test_djkstra() {
    Graph<int, int, true> g;

    for (int i = 0; i < 6; i++)
        g.insertVertex(i);

    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 5);
    g.insertEdge(1, 3, 2);
    g.insertEdge(1, 5, 7);
    g.insertEdge(2, 5, 1);
    g.insertEdge(3, 0, 2);
    g.insertEdge(3, 2, 1);
    g.insertEdge(3, 4, 4);
    g.insertEdge(4, 3, 3);
    g.insertEdge(5, 4, 1);

    vector<int> path = g.Djikstra(0, 5);

    for (int i = 0; i < path.size(); i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << "\t";
    }
}

void topo_sort_test() {
    Graph<int> g;

    for (int i = 0; i < 8; i++)
        g.insertVertex(i);

    g.insertEdge(0, 1);
    g.insertEdge(1, 2);
    g.insertEdge(1, 5);
    g.insertEdge(1, 6);
    g.insertEdge(3, 5);
    g.insertEdge(3, 7);
    g.insertEdge(4, 1);
    g.insertEdge(4, 7);
    g.insertEdge(7, 6);

    vector<int> topo = g.topologicalSort();

    for (int i = 0; i < topo.size(); i++)
        cout << topo[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    topo_sort_test();

    return 0;
}