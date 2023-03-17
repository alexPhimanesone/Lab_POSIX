OS := $(shell uname)
ifeq ($(OS), Darwin)
CFG_FOR_DARWIN=-DDARWIN
else
CFG_FOR_DARWIN=-UDARWIN
endif

TEACHER=true
CC=gcc
CFLAGS=-g -Wall -DTEACHER=$(TEACHER) $(CFG_FOR_DARWIN)
LDFLAGS=-g -DTEACHER=$(TEACHER) -pthread

PRESOURCES_1=\
main_protected_buffer.c\
protected_buffer.c\
protected_buffer.h\
cond_protected_buffer.c\
cond_protected_buffer.h\
sem_protected_buffer.c\
sem_protected_buffer.h\
utils.c\
utils.h\

SOURCES_1 = \
circular_buffer.h\
circular_buffer.c\

OBJECTS_1 = \
circular_buffer.o\
main_protected_buffer.o\
protected_buffer.o\
cond_protected_buffer.o\
sem_protected_buffer.o\
utils.o\

PRESOURCES = \
$(PRESOURCES_1)\

SOURCES = \
$(SOURCES_1)\

OBJECTS = \
$(OBJECTS_1)\

PROGS = \
main_protected_buffer\

%.c: %.p.c
	awk -f presources.awk -v TEACHER=$(TEACHER) $< >$@

%.h: %.p.h
	awk -f presources.awk -v TEACHER=$(TEACHER) $< >$@

.c.o:
	$(CC) -c $(CFLAGS) $<

default : $(PROGS)

clean : 
	$(RM) $(OBJECTS) $(PROGS) deps *~

veryclean: clean
	$(RM) $(PRESOURCES)

main_protected_buffer : $(PRESOURCES_1) $(OBJECTS_1)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS_1) 

deps: $(SOURCES) $(PRESOURCES)
	$(CC) -M $(SOURCES) $(PRESOURCES) >deps

student:
	@make veryclean
	@make TEACHER=false $(PRESOURCES)

teacher:
	@make veryclean
	@make TEACHER=true $(PRESOURCES)

index.html: index.texi
	makeinfo \
	        --no-headers --html --ifinfo --no-split \
		--css-include=style.css $< > $@

error :
	$(error "PREFIX variable not set")

install : veryclean index.html
	@if test -z "$(PREFIX)"; then \
	   make error; \
	fi
	@make student
	-mkdir -p $(PREFIX)
	chmod og=u-w $(PREFIX)
	tar zcf src.tar.gz `cat MANIFEST` Makefile
	chmod og=u-w style.css index.html src.tar.gz
	cp -p style.css index.html src.tar.gz $(PREFIX)

-include deps
