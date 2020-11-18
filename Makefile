ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

CPP		  = g++
CC		  = gcc
OBJ		  = IntBV.o ipint.o
LINKOBJ	  = IntBV.o ipint.o
LIBS	  =
INCS	  = -I"."
CXXINCS   = -I"."
DEFINES	  = -D__GNU__
CXXFLAGS  = -g $(CXXINCS) $(DEFINES)
CFLAGS    = -g $(INCS) $(DEFINES)
GPROF     = gprof.exe
RM        = rm -f
LINK      = ar
BIN		  = libIntBV.a
# LINKFLAGS = -L. -lIntBV -lcppunit -lws2_32
# LINKFLAGS = -L. -lcppunit -lws2_32

ifeq ($(detected_OS),Windows)
    LINKFLAGS = -L. -lIntBV -lcppunit -lws2_32
    # LINKFLAGS = -L. -lcppunit -lws2_32
endif
# ifeq ($(detected_OS),Darwin)        # Mac OS X
#    LINKFLAGS = -L. -latesim -lcppunit
# endif
ifeq ($(detected_OS),Linux)
    LINKFLAGS = -L. -lIntBV -lcppunit
    # LINKFLAGS = -L. -lcppunit
endif

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) TestIntBV all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN) testIntBV.o IntBV.o ipint.o TestIntBV

$(BIN): $(OBJ)
	$(LINK) rcu "$(BIN)" $(LINKOBJ)
	ranlib $@

testIntBV.o: $(GLOBALDEPS) testIntBV.cpp IntBV.h ipint.h
	$(CPP) -c testIntBV.cpp -o testIntBV.o $(CXXFLAGS)

IntBV.o: $(GLOBALDEPS) IntBV.cpp IntBV.h ipint.h
	$(CPP) -c IntBV.cpp -o IntBV.o $(CXXFLAGS)

ipint.o: $(GLOBALDEPS) ipint.cpp ipint.h
	$(CPP) -c ipint.cpp -o ipint.o $(CXXFLAGS)

TestIntBV: testIntBV.o libIntBV.a
	# $(CPP) -o TestIntBV testIntBV.o $(CXXFLAGS) -L. -lIntBV -lcppunit -lws2_32
	$(CPP) $(CXXFLAGS) -o $@ testIntBV.o $(OBJ) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)
