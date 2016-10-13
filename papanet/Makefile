CC = gcc -O3 -Wall -pedantic
OFILES = main.o papanet.o

papanet : $(OFILES)
	$(CC) -o $@ $(OFILES) -lm

.c.o :
	$(CC) -c -o $@ $<

main.c : papanet.o


papanet.c : ../papalib/final_trained.net
	snns2c $< $@


clean :
	\rm -f $(OFILES)

distclean : clean
	\rm -f papanet papanet.c papanet.h

