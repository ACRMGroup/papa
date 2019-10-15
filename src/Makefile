CC = gcc -O3 -Wall -pedantic
OFILES = main.o papanet.o
EXE = papanet

$(EXE) : $(OFILES)
	$(CC) -o $@ $(OFILES) -lm
	cp $@ ../share/papa/

.c.o :
	$(CC) -c -o $@ $<

main.c : papanet.o


papanet.c : final_trained.net
	snns2c $< $@

clean :
	\rm -f $(OFILES)

distclean : clean
	\rm -f $(EXE)
