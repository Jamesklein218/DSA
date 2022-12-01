#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <cstring>
#include <climits>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>

#include "AVLTree.h"

using namespace std;

int main() {
    AVLTree<int> avl;
    int arr[] = {10,52,98,32,68,92,40,13,42,63};
    for (int i = 0; i < 10; i++){
        avl.insert(arr[i]);
    }
    avl.remove(52);
    avl.printTreeStructure();

    return 0;
}