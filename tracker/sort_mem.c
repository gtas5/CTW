#include "../lib/csapp.h"
#include "sort_mem.h"

void sort_mem(){
    int i,j,n;
    n = num;
    char tmp[CSIZE];

    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++){
            if (strcmp(uses[i].mems, uses[j].mems) < 0){
                    strcpy(tmp, uses[i].ipaddr);
                    strcpy(uses[i].ipaddr, uses[j].ipaddr);
                    strcpy(uses[j].ipaddr, tmp);

                    strcpy(tmp, uses[i].mems);
                    strcpy(uses[i].mems, uses[j].mems);
                    strcpy(uses[j].mems, tmp);
            }
        }
}