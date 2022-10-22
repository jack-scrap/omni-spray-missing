CXX=g++

BUILDDIR=build

PREFIX:=/usr/local

BINDIR:=$(PREFIX)/bin

STATIC=main.cpp disp.cpp prog.cpp glyph.cpp util.cpp
OBJ_STATIC=$(patsubst %.cpp, $(BUILDDIR)/%.o, $(STATIC))

HDR=col.h layout.h

LDFLAGS=-lGLEW -lGL -lSDL2 -lpng

.PHONY: all
all: mk_build mk_o omni_spray_missing

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

omni_spray_missing: $(OBJ_STATIC) $(HDR)
	$(CXX) $(OBJ_STATIC) $(LDFLAGS) -o $@

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: mk_o
mk_o:
	mkdir -p o

.PHONY: install
install:
	sudo cp omni_spray_missing $(BINDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o omni_spray_missing
