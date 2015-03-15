#include "ip.h"


void check_mismatch_length(ip_frag *temp)
{
  int lenflag=0;	
  int sum=0;
  int reqlength;
    
  ip_frag *temp2;
  
  char *tempstr;
  ipad.s_addr=temp->ip_addr;
  tempstr=inet_ntoa(ipad);
  
  if(temp->next==NULL)
  {
    
    printf("\nNo mismatch in length found!!!  %s,%d\n\n",tempstr,temp->id);
    
   return;
  }
  else
  {
     if(temp->fragoffset==0 && temp->more_frames==0)
     {
      temp2=temp;
         while(temp2->next!=NULL)
         {
           if(temp2->length != temp2->next->length)
                lenflag=1;
           temp2=temp2->next;
         }
         if(lenflag==1)
         {
            
             printf("\nError:Mismatch in length found!!!  %s,%d\n\n",tempstr,temp->id);
             
             return;
         }
         else
         { 
            
            printf("\nNo mismatch in length found!!!  %s,%d\n\n",tempstr,temp->id); 
            return;
          }
     }
     temp2=temp;
     while(temp2->next!=NULL)
         temp2=temp2->next;  //Now temp2 is pointing to the last fragment in the list for each of the packets... 
     
    reqlength=temp2->fragoffset+temp2->length;  //This is what is the total length of the ip packet assuming that the last fragment is the last fragment.
     temp2=temp; //Now, temp2 is pointing to the first  in the array...Now let us calculate the actual length of the received fragments...
    while(temp2!=NULL)
    {
      sum=sum+temp2->length;
      temp2=temp2->next;
     
     }

    if(reqlength!=sum)
    {
      
      printf("\nError:MissMatch in length!!!  %s,%d\n\n",tempstr,temp->id);
           
    }
    else
      printf("\nNo mismatch in length!!!  %s,%d\n\n",tempstr,temp->id);
 }  
}        

