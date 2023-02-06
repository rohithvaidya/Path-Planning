#include <iostream>
#include <vector>
#include <cstdlib>
#include<stack>
#include<set>

using namespace std;

int adj_matrix[100][100];

struct Node{
    int h=0;
    int f=0; //Total Cost
    int g = 0; //Start to Current Distance

    int id;
    int status;
    };

vector<vector<Node>> grid;
set<int> final_path;

void a_star(){
    vector<Node> open_list;
    vector<Node> closed_list;
    vector<Node> successors;

    struct Node goal_node = grid[8][8];
    goal_node.h = 0;
    int goal_x = 8;
    int goal_y = 8;

    struct Node start_node = grid[0][0];
    start_node.h = 98;
    start_node.g = 0;
    start_node.f = 98;

    open_list.push_back(start_node);

    while(!open_list.empty()){

    struct Node q = open_list[0];

    int q_pos = 0;


    for(int i=0;i<open_list.size();i++){

        if(open_list[i].f < q.f){
            q  = open_list[i];
            q_pos = i;
        }
    }

    closed_list.push_back(q);
    open_list.erase(open_list.begin()+q_pos);




    for(int i=0;i<100;i++){
        if(adj_matrix[q.id][i]==1){
            for(int j=0;j<10;j++){
                for(int k=0;k<10;k++){
                    if(grid[j][k].id == i){

                        successors.push_back(grid[j][k]);
                    }
                }

            }
        }
    }



    for(auto i:successors){

        if(i.id == goal_node.id){
                cout<<endl;
            cout<<"Goal Reached "<<i.id;
            cout<<"Distance "<<i.g;
            cout<<"Total Cost "<<i.f;
            cout<<endl;

            for(auto o:closed_list){
                cout<<o.id<<" ";
            }
            return;
        }

        else{
            i.g = q.g + 1;
            i.h = (goal_x - i.id);
            i.f = i.g + i.h;
        }

        for(auto k:open_list){
            if((k.id == i.id)){
                continue;
            }
        }

        for(auto l:closed_list){
            if((l.id == i.id)){
                continue;
            }
        }
        //cout<<i.id<<" ";
        open_list.push_back(i);
        }
        //cout<<endl;
    successors.clear();

    }



    }


void dfs_with_limit(int start, int goal, vector<bool>& visited, int limit)
{

    if(limit<=1){
        return;
    }
    stack<int> s;
    s.push(0);
    visited[0] = true;

while(!s.empty()){
    int node = s.top();
    if(s.size()==1){
        limit-=1;
    }
    s.pop();
    cout<<node<<" ";
    if(node==goal){
        return;
    }
    cout<<endl;
    for(int i=0;i<100;i++){
        if((!visited[i]) && (adj_matrix[node][i]==1)){
            s.push(i);
            visited[i]=true;
        }
    }
}
}



void id_dfs(int start, int goal, vector<bool>& visited, int depth){
    for (int i = 1; i <= depth; i++){
        for(int j=0; j<100; j++){
            visited[j] = false;
        }
        dfs_with_limit(start, goal, visited, i);
        cout<<endl;
    }

}
int main()
{

    int grid_length = 10; // No of elements will be NxN
    int matrix_size = grid_length*grid_length;
    //int obstacles = (10*grid_length)/100;
    int obstacles = 1;

    vector<bool> visited(100, false);
    vector<int> random_nos;

    vector<Node> temp;
    int ctr = 0;


//Randomly Assign Obstacles
for(int i=0;i<obstacles;i++){
    int val = rand()%matrix_size;
    random_nos.push_back(val);
}

//Initialising Grid without Obstacles
    for(int i=0;i<grid_length;i++){
        for(int j=0;j<grid_length;j++){

                struct Node a;
                a.id = ctr;
                a.status = 1;
                for(int k=0;k<random_nos.size();k++){
                    if(random_nos[k]==a.id){
                        a.status = 0;
                    }
                }
                ctr+=1;
                temp.push_back(a);
        }
        grid.push_back(temp);
        temp = {};
    }


cout<<"The Grid"<<endl;
for(int i=0; i<grid_length; i++){
    for(int j=0; j<grid_length; j++){
        cout<<grid[i][j].status;
    }
    cout<<endl;
}
cout<<endl;

//Initialise Adj matrix
for(int i=0; i<matrix_size; i++){
    for(int j=0; j<matrix_size; j++){
        adj_matrix[i][j] = 0;


    }
}

//Convert to Adjacency Matrix.
for(int i=0;i<grid_length;i++){

    for(int j=0;j<grid_length;j++){

            if(grid[i][j].status){

                if(j-1>=0){
                    if(grid[i][j-1].status){
                    int val1 = grid[i][j-1].id;
                    int val2 = grid[i][j].id;
                    adj_matrix[val1][val2] = 1;
                    adj_matrix[val2][val1] = 1;
                }
                }

                if((j+1)<=(grid_length-1)){
                if(grid[i][j+1].status){
                    int val1 = grid[i][j+1].id;
                    int val2 = grid[i][j].id;
                    adj_matrix[val1][val2] = 1;
                    adj_matrix[val2][val1] = 1;
                }
                }

                if((i+1)<=(grid_length-1)){
                    if(grid[i+1][j].status){
                    int val1 = grid[i+1][j].id;
                    int val2 = grid[i][j].id;
                    adj_matrix[val1][val2] = 1;
                    adj_matrix[val2][val1] = 1;
                }
                }

                if(i-1>=0){
                    if(grid[i-1][j].status){
                    int val1 = grid[i-1][j].id;
                    int val2 = grid[i][j].id;
                    adj_matrix[val1][val2] = 1;
                    adj_matrix[val2][val1] = 1;
                }
                }


            }

        }

    }

//Print Adjacency Matrix
cout<<"The Adjacency Matrix"<<endl;
for(int k=0; k<matrix_size; k++){
    for(int l=0; l<matrix_size; l++){
        cout<<adj_matrix[k][l];
    }
    cout<<endl;
}

cout<<endl;

//Perform DFS
//dfs_with_limit(0, 30, visited, 10);

//id_dfs(20, 32, visited, 10);

a_star();

return 0;

}
