#include <iostream>

void complete_squares( unsigned int* a,  unsigned int* b, unsigned int n){
     
    for (int i = 0; i<n; i++){
        b[i] = (*(a+i)) * (*(a+i));
    }
}
int main(){
    unsigned int n = 5;
    unsigned int a[n] = {65535,65536,65537,65538,5};
    unsigned int b[n] = {0,0,0,0,0};
    complete_squares(a, b, n);
    for (int i =0; i<n; i++){
        std::cout<<b[i]<<std::endl;
    }
}
 