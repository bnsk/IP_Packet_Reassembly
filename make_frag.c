#include "ip.h"


ip_frag* make_frag(unsigned long ip_addr,int id,int fragoffset,int moreframes,int length)
{
   ip_frag *temp1;     
   temp1=(ip_frag *)malloc(sizeof(ip_frag));  //preparing the ip_pkt
        if(temp1==NULL)
        {
           printf("\nSorry!Fatal Error creating the ip_frag.\n");           
           exit(0);
        }
              temp1->ip_addr=ip_addr;
              temp1->id=id;
              temp1->fragoffset=fragoffset;
              temp1->more_frames=moreframes;
              temp1->length=length;  
    return temp1;
}
