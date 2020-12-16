#include <omp.h>
#include <unistd.h>
#include <cmath>
#include <iostream>

using namespace std;
int main(){
    int a[1000001];
    // for (int i = 1; i<1000001; i++) {
    //   a[i] = 0;
    // }
    a[0] = 1;
    omp_set_num_threads(8);
#pragma omp parallel for schedule(static, 1)
    for (int i = 0; i<1000001; i++){
        while (a[i] == 0){
          usleep(5);
        }
        for (int j = 0; j<10; j++) cout<<j;
        float z = 12114123123.112141414144113;
        float x = 1121421413.214214244114115;
        float c = 1/1/1/1/1/z/x*i;
        usleep(20000 * omp_get_thread_num());
        c = 12341234.12341234/1234123412341234.12341234/123412341234123/124*32412334*141234;
        cout << "core " << omp_get_thread_num() << "printed: " << i << endl;
        a[i+1] = 1;
        }
    return 0;
    }
