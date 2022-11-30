#include<bits/stdc++.h>
using namespace std;

#define int_max 1e9+5
#define pi pair<int,int>

vector<string> route = {"Railways","Roadways","Airways"};


//Cost Calculation using TSP
int tsp(int mask,int pos,int n,vector<vector<pi>>& dist, vector<vector<int>>& parent){
    if(mask == (1<<n) -1){
        return dist[pos][0].first;
    }

    int ans = int_max;
    for(int city=0;city<n;city++){
        if((mask&(1<<city))==0){
            int newAns = dist[pos][city].first + tsp( mask|(1<<city),city,n,dist,parent);
            if(newAns < ans){
                parent[pos][mask] = city;
                ans = newAns;
            }
        }
    }

    return ans;
}



int main(){

    
    int n,m;
    cout<<"Enter no. of city"<<endl;
    cin>>n;
    cout<<"Enter number of person travelling"<<endl;
    cin>>m;

    vector<string> cityName(n);
    cout<<"Enter name of cities"<<endl;
    for(int i=0;i<n;i++){
        cin>>cityName[i];
    }

    cout<<"\n\n";

    vector<vector<pi>> dist(n,vector<pi>(n,{0,0}));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;

            cout<<cityName[i]<<" -> "<<cityName[j]<<endl;

            //Minimum cost of travelling between 2 cities
            priority_queue< pi,vector<pi>, greater<pi> > pq;
            for(int k=0;k<3;k++){
                //0 -> Railways, 1-> Roadways , 2->Airways
                int temp;
                cin>>temp;
                pq.push({temp,k});
            }

            dist[i][j].first = pq.top().first;
            dist[i][j].second = pq.top().second;
        }
    }



    cout<<"\n\n\n\n";
    vector<vector<int>> parent(n+1,vector<int>((1<<n)));
    cout<<"Total Travelling Cost: "<<m*tsp(1,0,n,dist,parent)<<endl;


    //Finding Path
    vector<int> path(n);
    int path_counter = 0;
    int cur_node = 0;
    int cur_mask = 1;
    do {
        path[path_counter++] = cur_node;
        cur_node = parent[cur_node][cur_mask];
        cur_mask = cur_mask | (1 << cur_node);
    } while(cur_node != 0);


    //Printing Path
    cout<<cityName[0];

    for(int i=1;i<=n;i++){
        cout<<"   --by "<< route[dist[path[i-1]][path[i%n]].second] <<"-->   "<<cityName[path[i%n]];;
    }
    
    cout<<endl;
    return 0;
}



//int vis_all = (1<<n) -1;

// int dist[10][10] = {
// 0 1 3 2    ---- 35 each
//     {0,10,15,20},
//     {5,0,9,10},
//     {6,13,0,12},
//     {8,8,9,0}
// };

/*
dist[5][5] = {
    {0,20,30,10,11},
    {15,0,16,4,2},
    {3,5,0,2,4},
    {19,6,18,0,3},
    {16,4,7,16}
}
0 3 1 4 2 ---- 28 each
*/
