#include "Sudoku.h"
#include <time.h>
#include<stdlib.h>
using namespace std;
static int init_map[12][12];

bool Sudoku::Solve(){
    int loc=0;
    int sudoku_board[12][12];
    int pseudo_board[12][12];
    int anwser_board[12][12];
    int block_lineat;
    int block_colat;
    int break_state=0;
    vector<int> sudoku_probable[12][12];

    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
        for(int k=0;k<9;k++)
        sudoku_probable[i][j].push_back(k+1);

    int solve_state=0;
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            sudoku_board[i][j]=init_map[i][j];

     for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            if(sudoku_board[i][j]>0)
            {
                sudoku_probable[i][j].clear();
            }
            else if(sudoku_board[i][j]==-1)
            {
                sudoku_probable[i][j].clear();
            }
            else
            {
                for(int k=0;k<12;k++)
                {
                    if(sudoku_board[i][k]>0)
                    {
                        for(int l=0;l<sudoku_probable[i][j].size();l++)
                        {
                            if(sudoku_probable[i][j].at(l)==sudoku_board[i][k])
                            {
                                sudoku_probable[i][j].erase(sudoku_probable[i][j].begin()+l);
                                break;
                            }
                        }
                    }
                    if(sudoku_board[k][j]>0)
                    {
                        for(int l=0;l<sudoku_probable[i][j].size();l++)
                        {
                            if(sudoku_probable[i][j].at(l)==sudoku_board[k][j])
                            {
                                sudoku_probable[i][j].erase(sudoku_probable[i][j].begin()+l);
                                break;
                            }
                        }
                    }
                }
                block_lineat=i-i%3;
                block_colat=j-j%3;
                for(int k=0;k<9;k++)
                {
                    if(sudoku_board[block_lineat+k/3][block_colat+k%3]>0)
                    {
                        for(int l=0;l<sudoku_probable[i][j].size();l++)
                        {
                            if(sudoku_probable[i][j].at(l)==sudoku_board[block_lineat+k/3][block_colat+k%3])
                            {
                                sudoku_probable[i][j].erase(sudoku_probable[i][j].begin()+l);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    //======delete probable==========

    //======check_only_one==========
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
           if(sudoku_probable[i][j].size()==1)
           {
               sudoku_board[i][j]=sudoku_probable[i][j].at(0);
               sudoku_probable[i][j].clear();
           }
        }
    }
    //======check_only_one==========

    //======copy to pseudo board======
     for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            pseudo_board[i][j]=sudoku_board[i][j];
        }
    }
    //======copy to pseudo board======

    int unsolve_number=0;
    //======check unsolve number=========
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            if(sudoku_board[i][j]==0)
             unsolve_number++;
        }
    }
    //======check unsolve number=========
    int array_desided[unsolve_number];

    for(int i=0;i<unsolve_number;i++) array_desided[i]=0;

    int put_vectorloc=0;
    int run_time=0;
    //======solve======
    while(1)
    {
        put_vectorloc=0;
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<12;j++)
            {
                if(sudoku_board[i][j]==0)
                {
                pseudo_board[i][j]=sudoku_probable[i][j].at(array_desided[put_vectorloc]);
                put_vectorloc++;
                }
            }
        }
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<12;j++)
            {
                if(pseudo_board[i][j]!=-1)
                {
                    for(int k=0;k<12;k++)
                {

                    if(pseudo_board[i][k]==pseudo_board[i][j]&&k!=j)
                    {
                        break_state=1;
                        break;
                    }
                    if(pseudo_board[k][j]==pseudo_board[i][j]&&k!=i)
                    {
                        break_state=1;
                        break;
                    }
                }
                if(pseudo_board[i][j]==-1) break;
                if(break_state==1) break;
                else
                {
                block_lineat=i-i%3;
                block_colat=j-j%3;
                for(int k=0;k<9;k++)
                {
                    if(pseudo_board[block_lineat+k/3][block_colat+k%3]==pseudo_board[i][j]
                       &&(block_lineat+k/3)!=i&&(block_colat+k%3)!=j)
                    {
                        break_state=1;
                        break;
                    }
                }
                }
                }
                if(break_state==1) break;
            }
            if(break_state==1) break;
        }
        if(break_state==0)
        {
            solve_state++;
            if(solve_state>1) break;
            else
            {
            for(int i=0;i<12;i++)
            {
            for(int j=0;j<12;j++)
            {
                anwser_board[i][j]=pseudo_board[i][j];
            }
            }
            }
        break_state==0;
        }
        array_desided[unsolve_number-1]++;
        loc=0;
        while(1)
        {
            put_vectorloc=0;
            for(int i=0;i<12;i++)
            {
                for(int j=0;j<12;j++)
                {
                    if(sudoku_probable[i][j].size()>0)
                    {
                        if(array_desided[put_vectorloc]>=sudoku_probable[i][j].size())
                        {
                            loc=1;
                            break_state=1;
                            break;
                        }
                        else put_vectorloc++;
                    }
                    if(break_state==1) break;
                }
                if(break_state==1) break;
            }
            if(break_state==0) break;
            else
            {
                if(loc==1&&put_vectorloc==0) break;
                if(loc==1)
                {
                    array_desided[put_vectorloc]=0;
                    array_desided[put_vectorloc-1]++;
                    }
                    break_state=0;
            }
            if(break_state==1) break;
        }
        if(put_vectorloc==0) break;
    }
    //======solve======

    //======print result======
    if(solve_state==1)
    {
        cout<<"1"<<endl;
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<12;j++)
            {
                cout<<anwser_board[i][j]<< " ";
            }
            cout<<endl;
        }
    }
    else if(solve_state==2)
    {
        cout<<solve_state;
    }
}

void Sudoku::GiveQuestion(){
    srand(time(NULL));
    int a=rand()%4;
    int init_map[12][12];
    switch(a){
        case 0:{
        cout<<"4 2 6 8 7 3 9 5 1 -1 -1 -1"<<endl;
    cout<<"0 0 3 9 5 0 6 0 4 -1 -1 -1"<<endl;
    cout<<"9 0 1 6 2 4 8 0 0 -1 -1 -1"<<endl;
    cout<<"-1 -1 -1 1 3 2 0 8 7 9 5 6"<<endl;
    cout<<"-1 -1 -1 0 8 0 1 9 0 4 2 0"<<endl;
    cout<<"-1 -1 -1 4 9 6 2 3 0 8 7 1"<<endl;
    cout<<"1 0 0 0 4 0 -1 -1 -1 6 9 5"<<endl;
    cout<<"0 0 4 0 6 0 -1 -1 -1 1 3 7"<<endl;
    cout<<"6 9 5 0 1 7 -1 -1 -1 2 8 4"<<endl;
    cout<<"3 1 2 -1 -1 -1 7 4 0 5 0 9"<<endl;
    cout<<"7 4 8 -1 -1 -1 0 6 9 3 0 2"<<endl;
    cout<<"0 6 0 -1 -1 -1 3 1 0 7 0 8"<<endl;
        };
           break;
        case 1:{
            cout<<"4,0,9,-1,-1,-1,1,0,6,3,7,0"<<endl;
    cout<<"2,0,0,-1,-1,-1,0,0,9,1,4,6"<<endl;
    cout<<"6,3,1,-1,-1,-1,0,4,5,2,8,0"<<endl;
    cout<<"8,9,6,1,0,4,0,0,0,-1,-1,-1"<<endl;
    cout<<"7,5,2,3,8,9,4,6,1,-1,-1,-1"<<endl;
    cout<<"3,0,4,2,0,6,0,0,7,-1,-1,-1"<<endl;
    cout<<"9,6,8,0,1,2,-1,-1,-1,7,0,3"<<endl;
    cout<<"5,0,0,8,9,3,-1,-1,-1,4,6,1"<<endl;
    cout<<"1,4,0,7,0,0,-1,-1,-1,0,9,0"<<endl;
    cout<<"-1,-1,-1,9,4,8,6,1,2,5,3,7"<<endl;
    cout<<"-1,-1,-1,5,2,7,9,3,8,0,0,0"<<endl;
    cout<<"-1,-1,-1,6,0,1,5,7,4,9,2,8"<<endl;
        };
            break;
        case 2:{
            cout<<"-1,-1,-1,6,0,1,5,7,4,9,2,8"<<endl;
    cout<<"-1,-1,-1,5,2,7,9,3,8,0,0,0"<<endl;
    cout<<"-1,-1,-1,9,4,8,6,1,2,5,3,7"<<endl;
    cout<<"1,4,0,7,0,0,-1,-1,-1,0,9,0"<<endl;
    cout<<"5,0,0,8,9,3,-1,-1,-1,4,6,1"<<endl;
    cout<<"9,6,8,0,1,2,-1,-1,-1,7,0,3"<<endl;
    cout<<"3,0,4,2,0,6,0,0,7,-1,-1,-1"<<endl;
    cout<<"7,5,2,3,8,9,4,6,1,-1,-1,-1"<<endl;
    cout<<"8,9,6,1,0,4,0,0,0,-1,-1,-1"<<endl;
    cout<<"6,3,1,-1,-1,-1,0,4,5,2,8,0"<<endl;
    cout<<"2,0,0,-1,-1,-1,0,0,9,1,4,6"<<endl;
    cout<<"4,0,9,-1,-1,-1,1,0,6,3,7,0"<<endl;
        };
            break;
        case 3:{
            cout<<"0 6 0 -1 -1 -1 3 1 0 7 0 8"<<endl;
    cout<<"7 4 8 -1 -1 -1 0 6 9 3 0 2"<<endl;
    cout<<"3 1 2 -1 -1 -1 7 4 0 5 0 9"<<endl;
    cout<<"6 9 5 0 1 7 -1 -1 -1 2 8 4"<<endl;
    cout<<"0 0 4 0 6 0 -1 -1 -1 1 3 7"<<endl;
    cout<<"1 0 0 0 4 0 -1 -1 -1 6 9 5"<<endl;
    cout<<"-1 -1 -1 4 9 6 2 3 0 8 7 1"<<endl;
    cout<<"-1 -1 -1 0 8 0 1 9 0 4 2 0"<<endl;
    cout<<"-1 -1 -1 1 3 2 0 8 7 9 5 6"<<endl;
    cout<<"9 0 1 6 2 4 8 0 0 -1 -1 -1"<<endl;
    cout<<"0 0 3 9 5 0 6 0 4 -1 -1 -1"<<endl;
    cout<<"4 2 6 8 7 3 9 5 1 -1 -1 -1"<<endl;
        };
            break;
    }
    /*for(int i=0;i<12;i++){
        for(int j=0;j<12;j++){
        cout<<init_map[i][i]<<" ";
        }
        cout<<"\n";
    }*/
}

void Sudoku::ReadIn(){
    for(int i=0;i<12;i++){
        for(int j=0;j<12;j++){
        cin>>init_map[i][j];
        }
    }
}
