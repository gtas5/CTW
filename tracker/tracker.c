#include "../lib/csapp.h"
#include "to_client.h"
#include "sort_mem.h"
#include "show_mem.h"
#include "listening_from_worker.h"



int main()
{  
              memset(uses,0,sizeof(uses));  
              num = 0;
              pthread_t clit;
              int cl;
              cl = pthread_create(&clit, NULL, to_client, NULL);

              listening_from_worker();
/*
              pthread_t outt;
              int temp = pthread_create(&outt , NULL, show_mem, NULL); 
*/
        return 0;
}