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
    string names[wrestlersSize];
    for (int i = 0; i < wrestlersSize; i++)
    {
        inputF >> wrestler;
        wrestlers[wrestler] = i;
        names[i] = wrestler;
    }
    
    int rivaries;
    inputF >> rivaries;
    vector<int> rivaryMatrix[rivaries];
    
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

bool bfs(int pos, int parent, bool *checked, int *babyFaceArr, vector<int> *rivaryMatrix)
{
    checked[pos] = 1;
    babyFaceArr[pos] = 1 - babyFaceArr[parent];
    
    for (int i = 0; i < rivaryMatrix[pos].size(); i++)
    {
        int v = rivaryMatrix[pos][i];
        if (!checked[v])
        {
            bfs(v, pos, checked, babyFaceArr, rivaryMatrix);
        }
        else
        {
            if (babyFaceArr[v] == babyFaceArr[pos])
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