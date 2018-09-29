#!bin/bash

ifndef PREFIX
  PREFIX=/usr
endif
CXX := g++
CXXFLAGS := -c -std=c++11 -O2 -march=native -Wall -Wextra -pedantic
LD := g++
LDFLAGS := -std=gnu++11 -lX11

NAME := LWAHotCorner
SRCDIR := src
OBJDIR := obj

OBJ := $(OBJDIR)/Manager.o $(OBJDIR)/Corner.o $(OBJDIR)/main.o
EXE := $(NAME)
DEPS := $(SRCDIR)/Utils.h

.PHONY: all clean

all: $(EXE)

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXE) main.o

install:
	install -m 755 -D $(EXE) $(DESTDIR)$(PREFIX)/bin/$(EXE)


$(EXE): $(OBJDIR) $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
