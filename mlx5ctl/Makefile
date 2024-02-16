CC=gcc
CFLAGS=-Wall -Wno-gnu-variable-sized-type-not-at-end
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

# Source files
SRCS = $(wildcard *.c)
HDRS = $(wildcard *.h)
RSRC = README.md LICENSE Makefile
OBJS = $(SRCS:.c=.o)
TARGET=mlx5ctl
VERSION:=0.1

.PHONY: all clean install

all: mlx5ctl

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

srctar:
	mkdir -p SOURCE/$(TARGET)-$(VERSION)
	cp -r $(SRCS) $(HDRS) $(RSRC) SOURCE/$(TARGET)-$(VERSION)
	cd SOURCE && tar -czvf $(TARGET)-$(VERSION).tar.gz $(TARGET)-$(VERSION)
	rm -rf SOURCE/$(TARGET)-$(VERSION)
