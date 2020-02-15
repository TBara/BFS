/********************************************************
 * * Author: Tom Barabasz
 * * Class: CS 325 W2020
 * * Homework 5
 * * Breadth First Search Babyface vs Heels: Suppose there are two types of professional wrestlers: “Babyfaces” (“good guys”) and
 * * “Heels” (“bad guys”). Between any pair of professional wrestlers, there may or may not be a rivalry.
 * * Suppose we have n wrestlers and we have a list of r pairs of rivalries.
 * ******************************************************/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

bool bfs(int pos, int parent, bool *checked, int *babyFaceArr, vector<int> *adjacencyMatrix);
void printRivaries(int wrestlersSize, int *babyFaceArr, string *names);

int main(int argc, char *args[])
{
    //Map wrestler names with index
    map<string, int> wrestlers;
    bool bipartite = 1;
    int wrestlersSize;
    string wrestler, oponent1, oponent2;

    //Read input data
    ifstream inputF("data.txt");
    if (!inputF)
    {
        cout << "No such file\n";
        return 0;
    } 
    inputF >> wrestlersSize; //Number of wrestlers
    string names[wrestlersSize]; //Wrestlers names
    for (int i = 0; i < wrestlersSize; i++)
    {
        inputF >> wrestler;
        wrestlers[wrestler] = i; //Mapwrestler names and index
        names[i] = wrestler; //Store wrestler names
    }
    
    int rivaries; 
    inputF >> rivaries; //Get number of rivaries
    vector<int> rivaryMatrix[rivaries];
    
    //Set rivaries and add edges to the graph
    for (int i = 0; i < rivaries; i++)
    {
        inputF >> oponent1 >> oponent2;
        rivaryMatrix[wrestlers[oponent1]].push_back(wrestlers[oponent2]);
        rivaryMatrix[wrestlers[oponent2]].push_back(wrestlers[oponent1]);
    }
    inputF.close();

    bool checked[wrestlersSize];
    int babyFaceArr[wrestlersSize];
    for (int i = 0; i < wrestlersSize; i++)
    {
        checked[i] = babyFaceArr[i] = 0;
    }

    //Run BFS connected sets
    for (int i = 0; i < wrestlersSize; i++)
    {
        if (checked[i])
            continue;
        
        bipartite = bfs(i, 0, checked, babyFaceArr, rivaryMatrix);
        if (!bipartite)
            break;
    }
    if (!bipartite)
    {
        cout << "No" << endl;
    }
    else
    {
        printRivaries(wrestlersSize, babyFaceArr, names);
    }

    return 0;
}

//Verify graph is bipartite
bool bfs(int idx, int parent, bool *checked, int *babyFaceArr, vector<int> *rivaryMatrix)
{
    checked[idx] = 1;
    babyFaceArr[idx] = 1 - babyFaceArr[parent];
    
    //iterate rivary matrix
    for (int i = 0; i < rivaryMatrix[idx].size(); i++)
    {
        int v = rivaryMatrix[idx][i];
        if (!checked[v])
        {
            //Recursive bfs
            bfs(v, idx, checked, babyFaceArr, rivaryMatrix);
        }
        else
        {
            //Not bipartite
            if (babyFaceArr[v] == babyFaceArr[idx])
            {
                return false;
            }
        }
    }
    return true;
}

void printRivaries(int wrestlersSize, int *babyFaceArr, string *names)
{
        vector<string> babyFaces, heels;
        for (int i = 0; i < wrestlersSize; i++)
        {
            if (babyFaceArr[i])
                babyFaces.push_back(names[i]);
            else
                heels.push_back(names[i]);
        }
        cout << "Yes\n";
        cout << "Babyfaces: ";
        
        for (int i = 0; i < babyFaces.size(); i++)
            cout << babyFaces[i] << " ";
        cout << endl;
        
        cout << "Heels: ";
        for (int i = heels.size() - 1; i >= 0; i--)
            cout << heels[i] << " ";
        cout << endl;
}