CC = gcc
CFLAG = -Wall -c
INCPATH = ./include
INCLUDE = -I./include

ip_reassembly : ip_reassembly.o check_mismatch_length.o check_duplicate_frags.o  check_missing_pkts.o check_duplicate.o             check_frag_in_rcv_array.o make_frag.o get_pos_in_rcv_array.o 
	$(CC) ip_reassembly.o check_mismatch_length.o check_duplicate_frags.o  check_missing_pkts.o check_duplicate.o             check_frag_in_rcv_array.o make_frag.o get_pos_in_rcv_array.o -o ip_reassembly       

ip_reassembly.o : ip_reassembly.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) ip_reassembly.c

check_mismatch_length.o : check_mismatch_length.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) check_mismatch_length.c

check_duplicate_frags.o  : check_duplicate_frags.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) check_duplicate_frags.c

check_missing_pkts.o : check_missing_pkts.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) check_missing_pkts.c

check_duplicate.o : check_duplicate.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) check_duplicate.c

check_frag_in_rcv_array.o: check_frag_in_rcv_array.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) check_frag_in_rcv_array.c

make_frag.o : make_frag.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) make_frag.c

get_pos_in_rcv_array.o : get_pos_in_rcv_array.c $(INCPATH)/ip.h
	$(CC) $(CFLAG) $(INCLUDE) get_pos_in_rcv_array.c

clean:
	rm -f *.o *~ip_reassembly











