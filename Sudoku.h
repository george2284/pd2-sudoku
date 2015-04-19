#include<iostream>
#include<vector>
class Sudoku{
private:
    bool checkUnity(int arr[]);
    int map[12][12];
public:
    void setMap(const int set_map[]);
    int getElement(int index);
    void setElement(int index,int value);
    int getFirstZeroIndex();
    bool isCoorect();
    //static const int sudokuSize=144;
    void GiveQuestion();
    void ReadIn();
    bool Solve();
};
