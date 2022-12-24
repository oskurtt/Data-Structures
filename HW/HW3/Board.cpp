#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Board.h"
Board::Board(std::string t1_, std::string t2_, std::string empty_){
    /* Defualt constructor
    I set rows to 5 and columns to 4. I made a elem variable to keep track of number of 
    elements in each column and I also pointed my arr (grid) to a pointer of arrays (columns)
    I set each arr[column] to NULL first so it doesnt take up any data
    */
    t1 = t1_;
    t2 = t2_;
    empty = empty_;
    r = 5;
    c = 4;
    elem = new int [c];
    arr = new std::string*[c];
    for (int i = 0; i<c; i++){
        arr[i] = NULL;
        elem[i] = 0;
    }
}

std::ostream& operator<< (std::ostream& os, Board& b){
    /*<< operator to print out board
    I started at the top left corner of the board and printed the board
    If it got to the last element, you wouldn't print an extra space, else print 
    an extra space.
    */
    for (int i = b.numRows()-1; i >= 0; i--){
        for (int j = 0; j<b.numColumns(); j++){
            if (b.getElem()[j]>i){
                if (j == (b.numColumns()-1)){
                    os<<b.getArr()[j][i];
                }
                else{
                    os<<b.getArr()[j][i]<<' ';
                }
            }
            else{
                if (j== (b.numColumns()-1)){
                    os<<b.getEmpty();
                }
                else{
                    os<<b.getEmpty()<<' ';
                }
            }
        }
       os<<std::endl;
    }
    return os<<"";
}

int Board::numTokensInRow(int Rtok){
    /*Used for loop to loop through the row specified and counted whether or not it 
    was a token or an empty space
    */
    int count = 0;
    if (Rtok >= r){
            return -1;
        }
    for (int i = 0; i<c; i++){
        if (elem[i]==0){
            continue;
        }        
        if ((arr[i][Rtok] == t1) || (arr[i][Rtok] == t2)){
            count += 1;
        }
    } 
    return count;
}

int Board::numTokensInColumn(int Ctok){
    /*Used for loop to loop through the column specified and counted whether or not it 
    was a token or an empty space
    */
    int count = 0;
    if (Ctok >= c){
            return -1;
        }    
    for (int i = 0; i < elem[Ctok]; i++){
        if (elem[Ctok]==0){
            return 0;
        }
        else if ((arr[Ctok][i] == t1) || (arr[Ctok][i] == t2)){
            count += 1;
        }
    }
    return count;
}

std::string Board::insert(int cNum, bool player){
    /*Check for if the inserted column exceeds the amount of columns we have right now.
    If it does, you create a temporary elem and expand it's size as well as a temporary grid
    with resizing. Then you copy over the old grid and elements to the new ones and finally
    delete the old grid and elements and set it equal to the new ones
    */
    if (cNum >= c){
        std::string** tarr = new std::string* [cNum+1];
        int* telem = new int [cNum+1];
        telem[cNum] = 1;
        tarr[cNum] = new std::string [1];
        for (int i = 0; i< cNum; i++){
            tarr[i] = NULL;
        }
        for (int i = c; i < cNum; i++){
            telem[i] = 0;
        }
        for (int i = 0; i<c; i++){
            telem[i] = elem[i];
            tarr[i] = arr[i];
        }
        if (player){
            tarr[cNum][0] = t1;
        }
        else {
            tarr[cNum][0] = t2;
        }
        delete [] arr;
        arr = tarr;
        delete [] elem;
        elem = telem;
        c= (cNum+1);
    }
    /*Checks if specified column has tokens in it. If not, you create a new column with a size of 1
    and make that equal to the dropped token.
    */
    else if (elem[cNum] == 0){
        elem[cNum] += 1;
        arr[cNum] = new std::string [1];
        if (player == true){
            arr[cNum][0] = t1;
        }
        else{
            arr[cNum][0] = t2;
        }
    }
    /*If you are at max height, expand the row by one. If not, you create a column with an extra space 
    and make that the dropped token.
    */
    else{
        if (elem[cNum] == r){
            r+=1;
        }
        elem[cNum] += 1;
        std::string* temp = new std::string [elem[cNum]];
        for (int i = 0; i< (elem[cNum]-1); i++){
                temp[i] = arr[cNum][i];
        }
        if (player){
            temp[elem[cNum]-1] = t1;
        }
        else {
            temp[elem[cNum]-1] = t2;
        }
        delete [] arr[cNum];
        arr[cNum] = temp;     
    }      
    return Board::WinOrNah();
}
std::string Board::WinOrNah(){
    //Checks for verticle connect 4
    //Uses may if statements to check if there are enough space to check for four tokens
    for (int i = 0; i < c; i++){
        if (elem[i] > 0){
            for (int j = 0; j < elem[i]; j++){
                if (elem[i] > (j+3)){
                    if ((arr[i][j] == arr[i][j+1]) && (arr[i][j] == arr[i][j+2]) \
                        && (arr[i][j] == arr[i][j+3])){
                        std::string win = arr[i][j];
                        return win;
                    }
                }
            }    
        }
    }
    //checks for horizontal connect 4
    //Uses may if statements to check if there are enough space to check for four tokens
    for (int i = 0; i < c; i++){
        if (elem[i] > 0){
            for (int j = 0; j < elem[i]; j++){
                if (elem[i]>j){                   
                    if ((i+3) < c){
                        if ((elem[i+1] > j) && (elem[i+2] > j) && (elem[i+3] > j)){                           
                            if ((arr[i][j] == arr[i+1][j]) && (arr[i][j] == arr[i+2][j]) \
                                && (arr[i][j] == arr[i+3][j])){
                                    std::string win = arr[i][j];
                                    return win;
                            }   
                        }
                    }
                }    
            }
        }
    }
    return empty;
}
void Board::clear(){
    //Clears board and set it to the original 4x5 grid
    for (int i =0; i<c; i++){
        delete [] arr[i];
    }
    delete [] arr;
    delete [] elem;
    r = 5;
    c = 4;
    elem = new int [c];
    arr = new std::string*[c];
    for (int i = 0; i<c; i++){
        arr[i] = NULL;
        elem[i] = 0;
    }
}   
//Returns certain variables if needed
int Board::numColumns() const{return c;}
int Board::numRows() const{return r;}
std::string** Board::getArr() const{return arr;}
std::string Board::getT1() const {return t1;}
std::string Board::getT2() const {return t2;}
std::string Board::getEmpty() const {return empty;}
int* Board::getElem() const {return elem;}