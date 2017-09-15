CC=			g++
CFLAGS=		-g -Wall -std=c++11
LD=			g++
LDFLAGS=	-L.
TARGETS=	rorschach

all:		$(TARGETS)

main.o:		main.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

compare.o:	compare.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

crawl.o:	crawl.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

match_patterns.o:	match_patterns.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

execute.o:	execute.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

parse_rules.o:	parse_rules.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

utils.o:	utils.cpp rorschach.h
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

rorschach:	main.o crawl.o compare.o execute.o match_patterns.o parse_rules.o utils.o
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o
