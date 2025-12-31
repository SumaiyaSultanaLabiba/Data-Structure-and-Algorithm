#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//left_node is a function to check whether all the nodes are taken in their respective components or not
int left_node(vector<int>& component_detector, int num_of_nodes)
{
   for(int i=1; i<=num_of_nodes; i++)
   {
     if(component_detector[i]==-1) return i;
   }
   return -1;
}


void DFS(vector<vector<int>>& adjList, int root, int& currentTime, vector<int>& startTime, vector<int>& finishTime, vector<bool>& visited, vector<bool>& inProgress, vector<bool>& allDone, vector<int>& component_detector, int group)
{
    component_detector[root]=group;
    startTime[root]=currentTime;
    currentTime++;
    visited[root]=true;
    inProgress[root]=true;

    for(int v: adjList[root])
    {
        if(!visited[v])
        {
            DFS(adjList, v, currentTime, startTime, finishTime, visited, inProgress, allDone, component_detector, group);
        }
    }
    
    inProgress[root]=false;
    finishTime[root]=currentTime++;
    allDone[root]= true;
}



int main()
{
    int n, m; // n= number of nodes, m= number of edges
    cin>>n>>m;
    vector<vector<int>> adjList(n+1);
    for(int i=1; i<=m; i++)
    {
        int u, v;
        cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    //starting DFS
    vector<int> component_detector(n+1, -1);//detects which node belongs to which component, initially none of them belongs to any component, so -1
    int currentTime=0;
    int group=0;
    vector<int> startTime(n+1);
    vector<int> finishTime(n+1);
    vector<bool> visited(n+1, false);
    vector<bool> inProgress(n+1, false);
    vector<bool> allDone(n+1, false);
    while(left_node(component_detector, n)!=-1)
    {
    int root=left_node(component_detector, n);
    DFS(adjList, root, currentTime, startTime, finishTime, visited, inProgress, allDone, component_detector, group++);
    }
    


    //printing all results
    int total_number_of_components=n;
    vector<int> sorted_components=component_detector;
    sort(sorted_components.begin(), sorted_components.end());
    for(int i=1; i<=n-1; i++)
    {
        if(sorted_components[i]==sorted_components[i+1]) total_number_of_components--;
    }
    for(int i=1; i<=n; i++)
    {
        cout<<"Node: "<<i<<", Start: "<<startTime[i]<<", Finish: "<<finishTime[i]<<", Group: "<<component_detector[i]<<endl;
    }
    cout<<"Total number of connected components: "<<total_number_of_components<<endl;
    return 0;
}