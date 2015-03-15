#include "ip.h"


int get_pos_in_rcv_array(unsigned long ip_addr,int id)
{ 
   int j,tempo;
   ip_frag *temp;
   
   for(j=0;j<count;j++)
   {
     temp=iparr[j];
        
     if(temp->ip_addr==ip_addr && temp->id==id)
     {
       tempo=j;
       break;
     }
   
   }
   return tempo;
}
