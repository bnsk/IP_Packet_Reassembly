#include "ip.h"


int check_duplicate(unsigned long ip_addr,int id,int fragoffset,int length)
{
   int flag=0;
   int j;
   ip_frag *temp;
    
                  for(j=0;j<count;j++)
                    {
                          temp=iparr[j];
                          while(temp!=NULL)  
                          { 
                            if(temp->ip_addr==ip_addr && temp->id==id && temp->fragoffset==fragoffset)
                           { 
                             flag=1;
                           }//fi
                                                      
                           temp=temp->next;
                          }//end while...
                            
                  }//rof
 
     return flag;                
}

