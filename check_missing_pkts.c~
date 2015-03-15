#include"ip.h"

void check_missing_pkts(ip_frag *temp)
{
  char *tempstr;
  ipad.s_addr=temp->ip_addr;
  tempstr=inet_ntoa(ipad);
  if(temp->next==NULL)
    printf("\nNo missing packets!!!   %s,%d",tempstr,temp->id);
  else if(temp->fragoffset==0 && temp->more_frames==0)
          printf("\nNo missing packets!!!   %s,%d",tempstr,temp->id);
  else
  {
   while(temp->next!=NULL)
   {
     
     if(temp->fragoffset + temp->length != temp->next->fragoffset) 	  
     {
       
       printf("\nError:Missing packets!!!  %s,%d",tempstr,temp->id);
       return;
     } 
     
  temp=temp->next;
  }
  printf("\nNo missing packets!!! %s,%d",tempstr,temp->id);
 }
}
