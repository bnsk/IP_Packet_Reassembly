#include "ip.h"


int check_frag_in_rcv_array(unsigned long ip_addr,int id)
{
   int flag=0;
   int j;
  
   ip_frag *temp;  
                  for(j=0;j<count;j++)
                    {
                          temp=iparr[j];
                          if(temp->ip_addr==ip_addr && temp->id==id)
                          { 
                            
                             flag=1;//another frag of same ip_pkt found in the received array...
     	                     }//fi
                     }//rof
                    
     return flag;                
}
