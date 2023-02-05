#include <iostream>
#include <vector>
#include <cstdlib>
#include<stack>

using namespace std;

int adj_matrix[100][100];

struct Node{
    int heur=0;
    int total_cost=0;
    int start_curr_dist = 0;

    int id;
    int status;
    };
    
vector<vector<Node>> grid;

void a_star(int goal){
    vector<Node> open_list;
    vector<Node> closed_list;



    open_list.push_back(grid[0][0]);
    struct Node curr_node = grid[0][0];
    struct Node child_node;

    int curr_pos=0;


    while(!open_list.empty()){

        curr_node = open_list[0];
        curr_pos = 0;

        for(int i=0; i< open_list.size(); i++){
            if(open_list[i].total_cost <= curr_node.total_cost){
                curr_node = open_list[i];
                curr_pos = i;
            }
        }
        closed_list.push_back(curr_node);
        open_list.erase(open_list.begin()+curr_pos);

        if(curr_node.id == goal){
            cout<<"Goal Found"<<endl;
            cout<<"Cost "<<curr_node.total_cost;
            cout<<endl;
            cout<<"Distance from start "<<curr_node.start_curr_dist;
            return;
        }


        int no_ch = 0;
        for(int i=0; i<100; i++){
            if(adj_matrix[curr_node.id][i] == 1){
                for(auto j:closed_list){
                    if(i == j.id){
                        continue;
                    }
                }

                //get Child
                for(int k=0; k<10; k++){
                    for(int l=0; l<10; l++){

                        if(grid[k][l].id == i)
                            child_node = grid[k][l];

                    }
                }

                child_node.start_curr_dist = curr_node.start_curr_dist + 1;
                child_node.heur = 14; //To be changed
                child_node.total_cost = child_node.start_curr_dist + child_node.heur;

                for(auto k:open_list){
                    if(child_node.id == k.id){
                        if(child_node.start_curr_dist > k.start_curr_dist){
                            continue;
                        }
                    }
                }

                open_list.push_back(child_node);
                no_ch+=1;

            }
        }


    }

}

void dfs_with_limit(int start, int goal, vector<bool>& visited, int limit)
{
    if(limit<=0){
        return;
    }

    // Print the current node
    cout << start << " ";

    // Set current node as visited
    visited[start] = true;

    // For every node of the graph
    for (int i = 0; i < 100; i++) {

        // If some node is adjacent to the current node
        // and it has not already been visited
        if (adj_matrix[start][i] == 1 && (!visited[i])) {
            dfs_with_limit(i, goal, visited, limit-1);
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
    int obstacles = (10*grid_length)/100;

    vector<bool> visited(100, false);
    //int obstacles = 1;




    vector<Node> temp;
    int ctr = 0;

//Initialising Grid with Obstacles
    for(int i=0;i<grid_length;i++){
        for(int j=0;j<grid_length;j++){
            int val = rand()%2;
            if((obstacles>0) && (val==0)){
                struct Node a;
                a.id = ctr;
                ctr+=1;
                a.status = 0;
                temp.push_back(a);
                obstacles-=1;
            }
            else if(obstacles!=0 && val==1){
                struct Node a;
                a.id = ctr;
                ctr+=1;
                a.status = 1;
                temp.push_back(a);
            }
            else{
                struct Node a;
                a.id = ctr;
                ctr+=1;
                a.status = 1;
                temp.push_back(a);
            }
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
        if(i==j){
           adj_matrix[i][j] = 1;
        }
        else{
            adj_matrix[i][j] = 0;
        }

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
//dfs_with_limit(0, visited, 3);

//id_dfs(0, 99, visited, 10);

a_star(52);

return 0;

}
