#include "../lib/csapp.h"
#include "show_mem.h"

void *show_mem(){
    int i,j,n;

    while(1){

        n = num;
        for(i=0;i<n;i++){
            printf("NO.%s server has %s kb free memory\n",uses[i].ipaddr, uses[i].mems);
        }
        if (num>0) printf("\n");
        usleep(10000000);
    }
}