#include "ip.h"

void check_duplicate_frags(ip_frag *temp)
{
  ip_frag *temp2;
  char *tempstr;
  ipad.s_addr=temp->ip_addr;
  tempstr=inet_ntoa(ipad);
  temp2=temp;
  while(temp!=NULL)
  {
     if(temp->ipdup_flag==1)
     {
       
       printf("\nError:Duplicate fragment found!!!  %s,%d",tempstr,temp2->id);
       return;
     }
   temp=temp->next;
  }
  
  printf("\nNo duplicates found!!!  %s,%d",tempstr,temp2->id);
 //return;
}          
