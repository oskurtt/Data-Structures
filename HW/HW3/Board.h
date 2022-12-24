#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

class Board{
    public:
    //All functions we need 
        Board (std::string t1_, std::string t2_, std::string empty_);
        
        int numRows() const;
        int numColumns() const;
        int numTokensInRow(int Rtok);
        int numTokensInColumn(int Ctok);
        std::string** getArr() const;
        std::string getT1() const;
        std::string getT2() const;
        std::string getEmpty() const;
        int* getElem() const;
        std::string insert(int cNum, bool player);
        std::string WinOrNah();
        friend std::ostream& operator<< (std::ostream& os, Board& b);
        void clear();
        //Destructor to destroy all memory if out of scope. 
        ~Board() { 
            for (int i =0; i<c; i++){
                if (arr[i] != NULL) 
                    delete [] arr[i];
            }
            delete [] arr;
            delete [] elem;  
        }

    private:
    //Private variables 
        std::string t1;
        std::string t2;
        std::string empty;
        std::string** arr;
        int r;
        int c;
        int* elem;
        
};
