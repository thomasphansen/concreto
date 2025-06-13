-include config.mk

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1
CC = gcc
CFLAGS = -Wall -Wextra -O2
VERSION ?= 1.0

OBJS = concreto.o

all: concreto

concreto: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

concreto.o: concreto.c concreto.h

concreto_test: concreto_test.c concreto.c concreto.h
	$(CC) $(CFLAGS) -DUNIT_TEST -o $@ concreto_test.c concreto.c -lm

.PHONY: test manpage

test: concreto_test
	./concreto_test

install: concreto
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 concreto $(DESTDIR)$(BINDIR)/concreto

manpage:
	install -d $(DESTDIR)$(MANDIR)
	install -m 644 concreto.1 $(DESTDIR)$(MANDIR)/concreto.1
	gzip -f $(DESTDIR)$(MANDIR)/concreto.1

clean:
	rm -f concreto concreto_test *.o
	rm -rf debian config.mk Concreto.deb

.PHONY: deb

deb: clean all
	mkdir -p debian/DEBIAN debian$(BINDIR)
	mkdir -p debian$(MANDIR)
	echo 'Package: concreto' > debian/DEBIAN/control
	echo 'Version: $(VERSION)' >> debian/DEBIAN/control
	echo 'Section: utils' >> debian/DEBIAN/control
	echo 'Priority: optional' >> debian/DEBIAN/control
	echo 'Architecture: amd64' >> debian/DEBIAN/control
	echo 'Maintainer: Unknown <unknown@example.com>' >> debian/DEBIAN/control
	echo 'Description: Concreto computes concrete mix material quantities.' >> debian/DEBIAN/control
	install -m 755 concreto debian$(BINDIR)/concreto
	install -m 644 concreto.1 debian$(MANDIR)/concreto.1
	gzip -f debian$(MANDIR)/concreto.1
	dpkg-deb --build debian Concreto.deb
