#include <iostream>
#include <vector>
#include <cstdlib>
#include<stack>
#include<set>
#include <fstream>
#define GRID_SIZE 10
#define MAT_SIZE 100

using namespace std;

int adj_matrix[MAT_SIZE][MAT_SIZE];
//vector<vector<int>> adj_list(GRID_SIZE,0);

struct Node{
    int h=0;
    int f=0; //Total Cost
    int g = 0; //Start to Current Distance
//Pos
    int x;
    int y;

    struct Node* parent;

    int id;
    int status;
    };

vector<vector<Node>> grid;
vector<Node> final_path;
set<int> dfs_path;

void a_star(){

    vector<Node> open_list;
    vector<Node> closed_list;
    vector<Node> successors;

    struct Node goal_node = grid[8][8];
    goal_node.h = 0;
    goal_node.x = 8;
    goal_node.y = 8;
    int goal_x = 8;
    int goal_y = 8;

    struct Node start_node = grid[0][1];
    start_node.h = 15;
    start_node.g = 0;
    start_node.f = 15;
    start_node.x = 0;
    start_node.y = 0;

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


    for(int i=0;i<MAT_SIZE;i++){
        if(adj_matrix[q.id][i]==1){
            for(int j=0;j<GRID_SIZE;j++){
                for(int k=0;k<GRID_SIZE;k++){
                    if(grid[j][k].id == i){
                        grid[j][k].x = j;
                        grid[j][k].y = k;
                        grid[j][k].parent = &q;
                        successors.push_back(grid[j][k]);
                    }
                }

            }
        }
    }

    for(auto i:successors){
        if(i.id==q.id){
            continue;
        }

        for(auto l:closed_list){
            if((l.id == i.id)){
                continue;
            }
        }

        if(i.id == goal_node.id){
                cout<<"Goal Reached "<<i.id;
                //Compute for goal node

                for(int p=0;p<q.g;p++){
                    cout<<q.parent<<" ";
                    q = *q.parent;

                }
                i.g = q.g + 1;
            i.h = abs(goal_x - i.x) + abs(goal_y-i.y); //Manhattan Distance
            i.f = i.g + i.h;

                cout<<endl;

            cout<<"Distance "<<i.g;
            cout<<"Total Cost "<<i.f;
            cout<<endl;


            cout<<closed_list.size();
            return;
        }

        else{

            i.g = q.g + 1;
            i.h = abs(goal_x - i.x) + abs(goal_y-i.y);
            i.f = i.g + i.h;

        }

        for(auto k:open_list){
            if((k.id == i.id)){
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

 int node;
    if(limit<0){
        cout<<"Not found at depth";
        return;

    }
    stack<int> s;
    s.push(start);
    visited[start] = true;

while(!s.empty()){
    node = s.top();
    s.pop();
    limit-=1;
    dfs_path.insert(node);
    if(node==goal){
        cout<<"Goal"<<endl;
        return;
    }

    for(int i=0;i<MAT_SIZE;i++){
        if((!visited[i]) && (adj_matrix[node][i]==1) && (limit>=0)){
            s.push(i);
            visited[i]=true;
        }
        else{
            continue;
        }
    }
}


cout<<"Not found"<<endl;
}



void id_dfs(int start, int goal, vector<bool>& visited, int depth){
    for (int i = 1; i <= depth; i++){
        for(int j=0; j<MAT_SIZE; j++){
            visited[j] = false;
        }
        dfs_with_limit(start, goal, visited, i);


        cout<<endl;
    }

}
int main()
{
    //int obstacles = (10*grid_length)/100;
    int obstacles = 10;

    vector<bool> visited(MAT_SIZE, false);
    vector<int> random_nos;

    vector<Node> temp;
    int ctr = 0;

cout<<endl;
//Randomly Assign Obstacles
for(int i=0;i<obstacles;i++){
    int val = rand()%MAT_SIZE;
    random_nos.push_back(val);
    cout<<val<<" ";
}

//Initialising Grid without Obstacles
    for(int i=0;i<GRID_SIZE;i++){
        for(int j=0;j<GRID_SIZE;j++){

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
for(int i=0; i<GRID_SIZE; i++){
    for(int j=0; j<GRID_SIZE; j++){
        cout<<grid[i][j].status;
    }
    cout<<endl;
}
cout<<endl;

//Initialise Adj matrix
for(int i=0; i<MAT_SIZE; i++){
    for(int j=0; j<MAT_SIZE; j++){
        adj_matrix[i][j] = 0;


    }
}

//Convert to Adjacency Matrix.
for(int i=0;i<GRID_SIZE;i++){

    for(int j=0;j<GRID_SIZE;j++){

            if(grid[i][j].status){

                if(j-1>=0){
                    if(grid[i][j-1].status){
                    int val1 = grid[i][j-1].id;
                    int val2 = grid[i][j].id;
                    adj_matrix[val1][val2] = 1;
                    adj_matrix[val2][val1] = 1;
                    //adj_list[val1].push_back(val2);
                    //adj_list[val2].push_back(val1);
                }
                }

                if((j+1)<=(GRID_SIZE-1)){
                if(grid[i][j+1].status){
                    int val1 = grid[i][j+1].id;
                    int val2 = grid[i][j].id;
                    adj_matrix[val1][val2] = 1;
                    adj_matrix[val2][val1] = 1;
                    //adj_list[val1].push_back(val2);
                    //adj_list[val2].push_back(val1);
                }
                }

                if((i+1)<=(GRID_SIZE-1)){
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
/*cout<<"The Adjacency Matrix"<<endl;
for(int k=0; k<MAT_SIZE; k++){
    for(int l=0; l<MAT_SIZE; l++){
        cout<<adj_matrix[k][l];
    }
    cout<<endl;
}*/

cout<<"Adjacency Computed";

cout<<endl;

//Perform DFS

//dfs_with_limit(1, 88, visited, 19);

id_dfs(1, 99, visited, 20);
cout<<dfs_path.size();
cout<<endl;


int temp1 = 0;

for(int i=0;i<GRID_SIZE;i++){
    for(int j=0;j<GRID_SIZE;j++){
        if(grid[i][j].status == 0){
            cout<<"|";
            continue;
        }
        for(auto k:dfs_path){

            if(grid[i][j].id == k){
                cout<<1;
                temp1 = 1;
            }
        }

        if(temp1 != 1){
            cout<<0;
        }
        temp1 = 0;

    }
    cout<<endl;
}

//id_dfs(20, 32, visited, 10);
//a_star();
ofstream myfile;
myfile.open ("E:/Course work/Foundations of AI/Path-Planning/f.txt");
for(auto v:dfs_path){
    myfile<<v<<endl;
}
myfile.close();


return 0;

}
