#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

bool bfs(int pos, int parent, bool *visited, int *babyfaces, vector<int> *adjacencyMatrix);

int main(int argc, char *args[])
{
    map<string, int> wrestlers;
    bool bipartite = 1;
    int wrestlersSize;
    string wrestler, oponent1, oponent2;

    ifstream inputF(args[1]);
    if (!inputF)
    {
        cout << "No such file\n";
        return 0;
    } 
    inputF >> wrestlersSize;
    //Enter wrestler's names into a string array and map
    string names[wrestlersSize];
    for (int i = 0; i < wrestlersSize; i++)
    {
        inputF >> wrestler;
        wrestlers[wrestler] = i;
        names[i] = wrestler;
    }
    
    int rivaries;
    inputF >> rivaries;
    vector<int> adjacencyMatrix[rivaries];
    
    for (int i = 0; i < rivaries; i++)
    {
        inputF >> oponent1 >> oponent2;
        adjacencyMatrix[wrestlers[oponent1]].push_back(wrestlers[oponent2]);
        adjacencyMatrix[wrestlers[oponent2]].push_back(wrestlers[oponent1]);
    }
    inputF.close();

    //perform bfs for all the connected components
    bool visited[wrestlersSize];
    int babyfaces[wrestlersSize];
    for (int i = 0; i < wrestlersSize; i++)
    {
        visited[i] = babyfaces[i] = 0;
    }

    for (int i = 0; i < wrestlersSize; i++)
    {
        if (visited[i])
            continue;
        //bfs()
        bipartite = bfs(i, 0, visited, babyfaces, adjacencyMatrix);
        if (!bipartite)
            break;
    }
    if (!bipartite)
    {
        cout << "No" << endl;
    }
    else
    {
        //create vectors.
        vector<string> faces, heels;
        for (int i = 0; i < wrestlersSize; i++)
        {
            //push the names if babyfaces are true
            if (babyfaces[i])
                faces.push_back(names[i]);
            else
                //otherwise push heels
                heels.push_back(names[i]);
        }
        cout << "Yes\n";
        cout << "Babyfaces: ";
        //print the baby faces
        for (int i = 0; i < faces.size(); i++)
            cout << faces[i] << " ";
        cout << endl;
        //print the heels.
        cout << "Heels: ";
        for (int i = heels.size() - 1; i >= 0; i--)
            cout << heels[i] << " ";
        cout << endl;
    }

    return 0;
}

bool bfs(int pos, int parent, bool *visited, int *babyfaces, vector<int> *adjacencyMatrix)
{
    //make the position visited.
    visited[pos] = 1;

    //assign the node value different to its parent
    babyfaces[pos] = 1 - babyfaces[parent];
    //iterate the adjacency matrix
    for (int i = 0; i < adjacencyMatrix[pos].size(); i++)
    {
        int value = adjacencyMatrix[pos][i];
        //if the value is not visted call
        //function bfs() recursively.
        if (!visited[value])
        {
            bfs(value, pos, visited, babyfaces, adjacencyMatrix);
        }
        else
        {
            //if two adjacent nodes have same value graph is                //not bipartite
            if (babyfaces[value] == babyfaces[pos])
                return false;
        }
    }
    return true;
}