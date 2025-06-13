-include config.mk

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJS = concreto.o

all: concreto

concreto: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

concreto.o: concreto.c concreto.h

concreto_test: concreto_test.c concreto.c concreto.h
	$(CC) $(CFLAGS) -DUNIT_TEST -o $@ concreto_test.c concreto.c -lm

.PHONY: test

test: concreto_test
	./concreto_test

install: concreto
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 concreto $(DESTDIR)$(BINDIR)/concreto

clean:
	rm -f concreto concreto_test *.o
	rm -rf debian config.mk Concreto.deb

.PHONY: deb

deb: clean all
	mkdir -p debian/DEBIAN debian$(BINDIR)
	echo 'Package: concreto' > debian/DEBIAN/control
	echo 'Version: 1.0' >> debian/DEBIAN/control
	echo 'Section: utils' >> debian/DEBIAN/control
	echo 'Priority: optional' >> debian/DEBIAN/control
	echo 'Architecture: amd64' >> debian/DEBIAN/control
	echo 'Maintainer: Unknown <unknown@example.com>' >> debian/DEBIAN/control
	echo 'Description: Concreto computes concrete mix material quantities.' >> debian/DEBIAN/control
	install -m 755 concreto debian$(BINDIR)/concreto
	dpkg-deb --build debian Concreto.deb

