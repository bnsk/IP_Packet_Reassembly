#include"ip.h"


 int k=0;
 int count=0;

int main(int argc,char *argv[])
{
        char buff[MAX]; 
        unsigned long ip_addr;
        char ip_address[16];
        int id,i;
        int more_frames;
        int fragoffset,frag_pos;
        int length;
        int dup,frag_flag;
        //char tempstr[MAX];
       

        ip_frag *temp=NULL,*temp1=NULL;
       
        if(argc>2)
        {
          printf("\nError:Usage is ./ip_reassembly inputfile\n");
          exit(0);    
         
        }
        for(i=0;i<MAX;i++)      //Initializing all the pointers to NULL...
            iparr[i]=NULL;          
 	FILE *inputfile=fopen(argv[1],"r");   //opening the input file....


 	if(!inputfile)
	{
 		printf("\nSorry couldnot open the input file\n");    //Error opening the input file....
 	        exit(0);
        }
         
        
           while(fgets(buff,MAX,inputfile)!=NULL)
           {
           	sscanf(buff,"%s %d %d %d %d",ip_address,&id,&fragoffset,&more_frames,&length); 
                     
        	ip_addr=inet_addr(ip_address);   //we have the ip-address..
                     //first we check if the received pkt is a full pkt or is frag???...
           	
                
                if(fragoffset==0 && more_frames==0)  //this means the received pkt is a full pkt...
                {
                    //now we want to check if it is already present in the array of received ip_pkts....
                     dup=check_duplicate(ip_addr,id,fragoffset,length);  //checking if it is a duplicate...
                     
                     temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);  //making the packet...
                           temp1->next=NULL;
                          
                     if(dup==1)
                     {     
                          //This means that we have a duplicate...
                               
                        temp1->ipdup_flag=1;   //Since we have a duplicate, we set the duplicate flag in the received packet...
                         //Now we shall insert this at its rightful place in the iparr...
                         frag_pos=get_pos_in_rcv_array(ip_addr,id);
                         temp=iparr[frag_pos];
                          while(temp->next!=NULL)
                              temp=temp->next;  
                         //Since it is a full frag it can be inserted anywhere, we will insert it at the end!!!
                         temp->next=temp1;
                     }
                     else if(dup==0)       //Here duplicate is not found.So,we deal with the case when we receive a full pkt but not a duplicate.
                          {                  
                                  
                            temp1->ipdup_flag=0;
                              iparr[k++]=temp1;//here we have inserted the pkt into the array....:-)
                             
                            count++;
                          }// else fi
                   
                   
                    
                 }//fi...We have checked the case where the received pkt is a full pkt and also the cases when it is and it is not a duplicate.
                  //Now, let us check the case when the received is a frag.->1)first frag,2)last frag,3)middle frag
                 else if(fragoffset==0 && more_frames==1)  //1)this means the received packet is the first fragment of the whole ip_packet...
                      {
                         //we need to check if it is a duplicate first...
                        dup=check_duplicate(ip_addr,id,fragoffset,length);
                         //There can be a case that there is another frag from the same ip_pkt received out of order and
                                //is hence in the received array...
                         frag_flag=check_frag_in_rcv_array(ip_addr,id);
                                if(frag_flag==1) //This means that there is another frag from same ip_pkt already in the list but this is the
                                {                  //fragment right???so insert it in the list first...
                                
                                     frag_pos=get_pos_in_rcv_array(ip_addr,id);
                                     temp=iparr[frag_pos];
                                     temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);
                                     temp1->next=temp;
                                     iparr[frag_pos]=temp1;
                                 }//fi
                                 else if(frag_flag==0) //This means that frst pkt arrived frst...                                                  
                                      {
                                         temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);
                                         temp1->next=NULL;
                                         iparr[k++]=temp1;
                                         count++;
                                       }//else fi 
                        
                         if(dup==1)
                         {     
                           //This means that we have a duplicate and hence we set the flag...
                                 
                           temp1->ipdup_flag=1;
                         }                                      
                         else if(dup==0)
                              { 
                                //This means that there is no duplicate....
                                temp1->ipdup_flag=0;

                             }//end else if(dup==0)...                 
                       }//end else if(fragoffset==0 && ...     

                    else if(fragoffset>0 && more_frames==0) //2)this means that the received packet is the last fragment in the ip_pkt...
                         {  //here also we need to deal with duplicate case 
                               dup=check_duplicate(ip_addr,id,fragoffset,length);
                         	//We need to check the case if there is another frag from the same ip_pkt or is this the frst received out-
                                       //of-order???
                                         frag_flag=check_frag_in_rcv_array(ip_addr,id);
                                          if(frag_flag==1) //This means that there is another frag from same ip_pkt already but this is the last
                                          {                //fragment right???so insert it in the list last...
                                
                                     		frag_pos=get_pos_in_rcv_array(ip_addr,id);
                                     		temp=iparr[frag_pos];
                                    		temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);
                                     		temp1->next=NULL;
                                     		while(temp->next!=NULL)
                                                   temp=temp->next;
                                                temp->next=temp1;   //Hence,we have inserted the frag at its right place...
                                          }//fi
                                           else if(frag_flag==0)   //This means that the last packet arrived first...
                                                {
                                                     temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);
                                                     temp1->next=NULL;
                                                     iparr[k++]=temp1;
                                                     count++;
                                                 }//else fi
                                if(dup==1)
                         	{     
                         	  //This means that we have a duplicate and hence we set the flag...
                         	      
                         	  temp1->ipdup_flag=1;
                                }                                      
                         	else if(dup==0)
                         	     { 
                         	       //This means that there is no duplicate....
                                       temp1->ipdup_flag=0;

                                     }  //end else if(dup==0)
                            }  //end else if(fragoffset>0 && ... 
                            
                            else if(fragoffset>0 && more_frames==1) //3)this means that the received packet is one of the middle fragments...
                            {  //here also we need to deal with duplicate case 
                            	   dup=check_duplicate(ip_addr,id,fragoffset,length);
                         	   //We need to check the case if there is another frag from the same ip_pkt or is this the frst received out-
                                       //of-order???
                                         frag_flag=check_frag_in_rcv_array(ip_addr,id);
                                          if(frag_flag==1) //This means that there is another frag from same ip_pkt already but this is the middle
                                          {                //fragment right???so insert it in the list last...
                                
                                     		frag_pos=get_pos_in_rcv_array(ip_addr,id);
                                     		temp=iparr[frag_pos];
                                    		temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);
                                     		while(temp->fragoffset<temp1->fragoffset)
                                                   temp=temp->next;
                                                temp1->next=temp->next; 
                                                temp->next=temp1;          //Hence we have inserted the frag in its place...
                                           }//fi
                                           else if(frag_flag==0)   //This means that the middle packet arrived first...
                                                {
                                                     temp1=make_frag(ip_addr,id,fragoffset,more_frames,length);
                                                     temp1->next=NULL;
                                                     iparr[k++]=temp1;
                                                     count++;
                                                 }//else fi
                                if(dup==1)
                         	{     
                         	  //This means that we have a duplicate and hence we set the flag...
                         	     
                         	   temp1->ipdup_flag=1;
                                }                                      
                         	else if(dup==0)
                         	     { 
                         	       //This means that there is no duplicate....
                                       temp1->ipdup_flag=0;

                                     }  //end else if(dup==0)
                            }  //end else if(fragoffset>0 && ... 





        }//end of while  
            
   printf("\n\n\nThe different fragments are on the same line and the different packets are on different lines....\n");

   for(i=0;i<count;i++)   //printing the ip-fragments received..
   {
     temp=iparr[i];
     printf("\n");
     while(temp!=NULL)
     {
       
       ipad.s_addr=temp->ip_addr;
       char *tempstr=inet_ntoa(ipad);
       printf("%s,%d,%d,%d,%d\t",tempstr,temp->id,temp->fragoffset,temp->more_frames,temp->length);
       temp=temp->next;
     }
     
   }

   printf("\n\n\nThe result(success/Error) for each of the packets received...\n");   

   for(i=0;i<count;i++)   //printing the final result of success or error for the ip-fragments received..
   {
     temp=iparr[i];
     
      check_duplicate_frags(temp);
      check_missing_pkts(temp);
      check_mismatch_length(temp);
     
   }
 return 0;  

}//end of main...




