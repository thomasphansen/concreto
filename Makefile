-include config.mk

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1
CC = gcc
CFLAGS = -Wall -Wextra -O2
VERSION ?= 1.0

SRCDIR = src
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
OUTDIR = $(BUILDDIR)

OBJS = $(OBJDIR)/concreto.o

all: $(OUTDIR)/concreto

$(OBJDIR):
	mkdir -p $@

$(OUTDIR):
	mkdir -p $@

$(OUTDIR)/concreto: $(OBJS) | $(OUTDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

$(OBJDIR)/concreto.o: $(SRCDIR)/concreto.c $(SRCDIR)/concreto.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)/concreto.c

$(OUTDIR)/concreto_test: $(SRCDIR)/concreto_test.c $(SRCDIR)/concreto.c \
$(SRCDIR)/concreto.h | $(OUTDIR)
	$(CC) $(CFLAGS) -DUNIT_TEST -o $@ $(SRCDIR)/concreto_test.c \
$(SRCDIR)/concreto.c -lm

.PHONY: test manpage

test: $(OUTDIR)/concreto_test
	$(OUTDIR)/concreto_test

install: $(OUTDIR)/concreto
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(OUTDIR)/concreto $(DESTDIR)$(BINDIR)/concreto

manpage:
	install -d $(DESTDIR)$(MANDIR)
	install -m 644 concreto.1 $(DESTDIR)$(MANDIR)/concreto.1
	gzip -f $(DESTDIR)$(MANDIR)/concreto.1

clean:
	rm -rf $(BUILDDIR) config.mk

.PHONY: deb

deb: clean all
	mkdir -p $(BUILDDIR)/debian/DEBIAN $(BUILDDIR)/debian$(BINDIR)
	mkdir -p $(BUILDDIR)/debian$(MANDIR)
	echo 'Package: concreto' > $(BUILDDIR)/debian/DEBIAN/control
	echo 'Version: $(VERSION)' >> $(BUILDDIR)/debian/DEBIAN/control
	echo 'Section: utils' >> $(BUILDDIR)/debian/DEBIAN/control
	echo 'Priority: optional' >> $(BUILDDIR)/debian/DEBIAN/control
	echo 'Architecture: amd64' >> $(BUILDDIR)/debian/DEBIAN/control
	echo 'Maintainer: Unknown <unknown@example.com>' >> $(BUILDDIR)/debian/DEBIAN/control
	echo 'Description: Concreto computes concrete mix material quantities.' >> $(BUILDDIR)/debian/DEBIAN/control
	install -m 755 $(OUTDIR)/concreto $(BUILDDIR)/debian$(BINDIR)/concreto
	install -m 644 concreto.1 $(BUILDDIR)/debian$(MANDIR)/concreto.1
	gzip -f $(BUILDDIR)/debian$(MANDIR)/concreto.1
	dpkg-deb --build $(BUILDDIR)/debian $(BUILDDIR)/Concreto.deb
