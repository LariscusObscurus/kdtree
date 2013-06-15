CC=g++
NAME=kdtree
CFLAGS=-Wall -Wextra -Wconversion -std=c++0x
LFLAGS=
VERSION=1.0
ARCHIVE=$(NAME)-$(VERSION)

ifdef NDEBUG
CFLAGS+=-O3
else
CFLAGS+=-g -D_DEBUG
endif

SRC = main.cpp 
OBJ = $(SRC:.cpp=.o)

all: $(SRC) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LFLAGS)

clean:
	rm $(OBJ) $(NAME)

dist:
	cd ..; tar czf $(ARCHIVE).tar.gz $(NAME); mv $(ARCHIVE).tar.gz $(NAME)

distclean:
	rm $(ARCHIVE).tar.gz

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
