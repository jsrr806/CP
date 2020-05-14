/*
Solution of: https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/jadu-and-spaceship/

Maximum Bipartite Matching using Edmonds-Karp Max Flow Algorithm
https://www.geeksforgeeks.org/maximum-bipartite-matching/
https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/

More Questions:- 
1) https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/easy-game/
*/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
void insert(vector<pair<int,int> >graph[],int u,int v,int wt)
{
    graph[u].push_back(make_pair(v,wt));
}
bool bfs(vector<pair<int,int> > rGraph[],int s,int t,pair<int,int> parent[],int size)
{
    bool vis[size]; 
    memset(vis, false, sizeof(vis));
    queue<int>q;
    q.push(s);
    vis[s]=true;
    parent[s]=make_pair(-1,-1);
    while(q.size()>0)
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<rGraph[u].size();i++)
        {
            int v=rGraph[u][i].first;
            int wt=rGraph[u][i].second;
            if(vis[v]==false && wt>0)
            {
                q.push(v); 
                parent[v] = make_pair(u,i); 
                vis[v] = true;
            }
        }
    }
    // if reached to the sink return true
    return (vis[t] == true);
}
void print(vector<pair<int,int> > graph[],int size)
{
    for(int i=0;i<size;i++)
    {
        cout<<i<<" : ";
        for(int j=0;j<graph[i].size();j++)
        {
            cout<<"("<<graph[i][j].first<<", "<<graph[i][j].second<<") | ";
        }
        cout<<endl;
    }
}
int EdmondsKarpMaxFlow(vector<pair<int,int> > graph[], int s, int t,int size)
{
    int max_flow = 0;
    //Residual Graph
    vector<pair<int,int> > rGraph[size];
    for(int i=0;i<size;i++)
    {
        rGraph[i]=graph[i];
    }
    pair<int,int> parent[size];
    int cnt=0;
    while(bfs(rGraph,s,t,parent,size))
    {
        cnt++;
        int path_flow = INT_MAX;
        for (int v=t; v!=s; v=parent[v].first)
        {
            int u = parent[v].first;
            int idx = parent[v].second;
            int wt=rGraph[u][idx].second;
            path_flow = min(path_flow, wt); 
        }
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (int v=t; v != s; v=parent[v].first) 
        { 
            int u = parent[v].first;
            int idx=parent[v].second;
            rGraph[u][idx].second -= path_flow; 
            int next=-1;
            for(int i=0;i<rGraph[v].size();i++)
            {
                int next=rGraph[v][i].first;
                if(next==u)
                {
                    next=i;
                    break;
                }
            }
            if(next!=-1)
            rGraph[v][next].second += path_flow;
            else
            insert(rGraph,v,u,1);
        }
        max_flow+=path_flow;
    }
    
    return max_flow;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<bool>isPrime(m+1,true);
    vector<ll>allPrimes;
    isPrime[1]=false;
    for(int i=2;i<=m;i++)
    {
        if(isPrime[i])
        {
            allPrimes.push_back(i);
            int next=2;
            while(i*next<=m)
            {
                isPrime[i*next]=false;
                next++;
            }
        }
    }
    vector<ll>arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int pSize=allPrimes.size();
    int s=0,t=n+pSize+1;
    vector<pair<int,int> >bpGraph[n+pSize+2];
    //create residual graph
    for(int i=1;i<=n;i++)
    {
        insert(bpGraph,s,i,1);
    }
    for(int i=n+1;i<n+pSize+1;i++)
    {
        insert(bpGraph,i,t,1);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<allPrimes.size()&&allPrimes[j]<=arr[i];j++)
        {
            if(arr[i]%allPrimes[j]==0)
            {
                int u=i+1;
                int v=n+j+1;
                insert(bpGraph,u,v,1);
            }
        }
    }
    cout<<EdmondsKarpMaxFlow(bpGraph,s,t,n+pSize+2);

    return 0;
}
