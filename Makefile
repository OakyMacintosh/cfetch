CC = gcc
CFLAGS = -Wall -O2
TARGET = cfetch

all: $(TARGET)

$(TARGET): cfetch.c
	$(CC) $(CFLAGS) -o $(TARGET) cfetch.c

install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)

cross-compile:
	$(CC) $(CFLAGS) -o $(TARGET) cfetch.c

mirixbuild:
	$(CC) $(CFLAGS) -o cfetch.o cfetch.c
	$(CC) $(CFLAGS) -o $(TARGET) cfetch.o libdist.o libsys.o -lmirix

clean:
	rm -f $(TARGET)
