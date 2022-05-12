CXX=g++

SRCDIR=.
BUILDDIR=build

STATIC=main disp prog util
OBJ_STATIC=$(patsubst %, $(BUILDDIR)/%.o, $(STATIC))

GL=-lGLEW -lGL
SDL=-lSDL2
PNG=-lpng
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)
LDFLAGS+=$(PNG)

.PHONY: mk_build clean

all: mk_build make

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

make: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS)

mk_build:
	mkdir -p $(BUILDDIR)

clean:
	rm $(BUILDDIR)/*.o a.out
