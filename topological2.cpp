#include <iostream>
#include <bitset>
using namespace std;

bool fastHasIncomingArrows(bool graph[20][20], int size, bitset<100> usedNodes, int node)
{
    bool found = false;
    for(int j = 0; !found && j < size; j++)
    {
        if(!usedNodes.test(j))
        {
            found = graph[node][j];
        }
    }
    return found;
}

void fastPrintGraph(bool graph[20][20], int size, bitset<100> usedNodes)
{
    for(int i = 0; i < size; i++)
    {
        if(!usedNodes.test(i))
        {
            for(int j = 0; j < size; j++)
            {
                if(!usedNodes.test(j))
                {
                    cout << graph[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
}

int fastSolutions(bool graph[20][20], int size, bitset<100> usedNodes)
{
    int solutions = 0;
    if(usedNodes.count() == size - 1)
    {
        solutions = 1;
    }
    else
    {
        for(int i = 0; i < size; i++)
        {
            if(!usedNodes.test(i) && !fastHasIncomingArrows(graph, size, usedNodes, i))
            {
                // set the used nodes to true and then after this solution
                // tree is passed, we unset it
                usedNodes.set(i, true);
                solutions += fastSolutions(graph, size, usedNodes);
                usedNodes.set(i, false);
            }
        }
        /*
        if(!hasIncomingArrows(graph, i))
        {
            vector<bool> sg = subGraph(graph, i);
            solutions += numberOfSolutions(sg);
        }
        */
    }

    return solutions;
}

int main()
{
    int size = 13;
    bool graph[20][20] = {0};
    bitset<100> usedNodes;

    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0; j < size; j++)
        {
            graph[i][j] = i != j
                          && ((i == 0 && j > 0)
                              || (i == 1 && j > 2 && j < size)
                              || j == size - 1 );
        }
    }

    fastPrintGraph(graph, size, usedNodes);

    cout << fastSolutions(graph, size, usedNodes);



    return 0;
}
