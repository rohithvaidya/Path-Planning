#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{

    int grid_length = 10; // No of elements will be NxN
    int matrix_size = grid_length*grid_length;
    int obstacles = (10*grid_length)/100;
    //int obstacles = 1;

    struct Node{
    //int heur;
    int id;
    int status;
    };

    vector<vector<Node>> grid;
    int adj_matrix[matrix_size][matrix_size];

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


return 0;

}
