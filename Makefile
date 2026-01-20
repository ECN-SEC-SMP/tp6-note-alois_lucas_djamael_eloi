SRCDIR := src
INCDIR := include
BUILDDIR := build
ASSETSDIR := assets

all: $(BUILDDIR)/main.out

# Build the final executable
$(BUILDDIR)/main.out: $(BUILDDIR)/main.o | $(BUILDDIR)
	g++ -o $@ $^

# Build main.o
$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/main.cpp -o $(BUILDDIR)/main.o


# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rfv $(BUILDDIR)