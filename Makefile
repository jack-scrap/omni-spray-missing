CXX=g++

SRCDIR=.
BUILDDIR=build

STATIC=main.cpp disp.cpp prog.cpp util.cpp
OBJ_STATIC=$(patsubst %.cpp, $(BUILDDIR)/%.o, $(STATIC))

HDR=col.h layout.h

LDFLAGS+=-lGLEW -lGL
LDFLAGS+=-lSDL2
LDFLAGS+=-lpng

.PHONY: mk_build mk_o clean

all: mk_build mk_o make

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

make: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS)

mk_build:
	mkdir -p $(BUILDDIR)

mk_o:
	mkdir -p o

clean:
	rm $(BUILDDIR)/*.o a.out
