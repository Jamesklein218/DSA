#include "main.h"

#include "Graph.h"
#include "DLinkedList.h"
#include "Sorting.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

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

    return 0;
}