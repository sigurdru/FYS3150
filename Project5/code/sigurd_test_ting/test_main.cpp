#include <cmath>
#include <iostream>

int main(){
    double initial[10][10];
    for (int i = 0; i<10;i++){
        for (int j= 0; j<10; j++){
            initial[i][j] = i;
            std::cout <<initial[i][j] << std::endl;;
        }
    }
}