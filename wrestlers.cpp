#include <bits/stdc++.h>
using namespace std;
#define SIZE 100010 //define size
vector<int> adjacencyMatrix[SIZE];//define a vector (adjacency matrix)
int babyfaces[SIZE];
bool visited[SIZE];

//definition of the function bfs()
//checks if the graph of rivalries list is bipartite or not
bool bfs(int pos, int parent)
{
   //make the position visited.
   visited[pos] = 1;

   //assign the node value different to its parent
   babyfaces[pos] = 1 - babyfaces[parent];
   //iterate the adjacency matrix
   for (int i = 0;i<adjacencyMatrix[pos].size();i++)
   {
       int value = adjacencyMatrix[pos][i];
       //if the value is not visted call
       //function bfs() recursively.
       if (!visited[value])
       {
           bfs(value, pos);
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

//definition of the main function
//takes command line arguments
int main(int argc, char * args[])
{
   //declare the variables
   int n, j, k, u, v, r;
   string babyname, rival1, rival2;
   bool possible = 1;
   //create a map variable
   map<string, int> data;
   //open the input text file
   ifstream infile(args[1]);
   //Check if the file exists.
   if (!infile) {
       cout << "Error opening file\n";
       return 0;
   }
   //read the the number of wrestlers.
   infile >> n;
   //create a string array
   string names[n + 1];
   //read the names and store in map
   for (int i = 0; i<n; i++)
   {
       infile >> babyname;
       data[babyname] = i;
       names[i] = babyname;
   }
   //read the the number of rivalries
   infile >> r;
   //read the rivalries listed in pairs.
   for (int i = 0;i < r;i++)
   {
       infile >> rival1 >> rival2;
       //get the index value of rival1
       u = data[rival1];
       //get the index value of rival2
       v = data[rival2];
       //adding edges to the graph
       adjacencyMatrix[u].push_back(v);
       adjacencyMatrix[v].push_back(u);
   }
   //close the input file.
   infile.close();
   //gets str, the pointer to the destination string.
   //make all wrestlers as heels first
   memset(babyfaces, 0, sizeof babyfaces);
   //for bfs all nodes are unvisited
   memset(visited, 0, sizeof visited);
   //assign all values to 0.
   babyfaces[0] = 0;

   //perform bfs for all the connected components
   for (int i = 0;i < n;i++)
   {
       if (visited[i])
           continue;
       //call the function bfs().
       possible = bfs(i, 0);
       //if not bipartite the partitioning is impossible
       if (!possible)
           break;
   }
   //print No, if impossible.
   if (!possible)
   {
       cout << "No" << endl;
   }
   else
   {
       //create vectors.
       vector<string> faces, heels;

       for (int i = 0;i < n;i++)
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
       for (int i = 0;i<faces.size();i++)
           cout << faces[i] << " ";
       cout << endl;
       //print the heels.
       cout << "Heels: ";
       for (int i = heels.size() - 1;i >= 0;i--)
           cout << heels[i] << " ";
       cout << endl;

   }

   return 0;
}