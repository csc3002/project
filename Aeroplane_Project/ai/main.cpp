
#include <iostream>
#include "define.h"
#include "movegenerator.h"
#include "searchengine.h"
#include <stdlib.h>
using namespace std;

void change(int a[]){
    int b[4] ;
    for(int i = 0; i<4; i++){
        b[i] = i+100;
    }
    memcpy(a,b,4);
}

int main()
{   int a[4] = {0,1,2,3};

    change(a);
    cout << a[0] << endl;
    return 0;
}
