CGI  = html.pm
INCLUDES = ../../header.tt ../../footer.tt ../../main_menu.tt ../abs_menu.tt 

all: $(CGI)

clean:
	\rm -f $(CGI) Makefile

%.pm : %.tt $(INCLUDES)  Makefile
	tpage $< > $@
	chmod a+x $@

%.html : %.tt $(INCLUDES)  Makefile
	tpage $< > $@
