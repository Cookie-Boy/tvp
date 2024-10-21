CFLAGS = -g -O0
CC = g++
EXEDIR = exec
SRC = $(wildcard *.cpp)
EXECS = $(SRC:.cpp=.exe)

.PHONY: all

all: $(EXEDIR) $(EXECS)
	$(CC) $(CFLAGS) $(EXEDIR)/$(EXECS)

$(EXEDIR): 
	@mkdir $(EXEDIR)

%.exe: %.cpp
	$(CC) $(CFLAGS) $< -o $(EXEDIR)/$@

clean:
	del /Q $(EXEDIR)/*.exe