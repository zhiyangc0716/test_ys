#----------------------------------------------------------
#创建日期：20180428
#作者：高理
#----------------------------------------------------------
# version debug or release
VER ?=release

DESDIR=../bin
TARGET=EsunnyQuoteApiTest

SRC = $(wildcard *.cpp)
SOURCE1=$(SRC:%.cpp=%.o)


APINCL := -I. -I../inc

LIBS = -L../bin -L../linux
LIBS += -lEsunnyQuoteApi -lpthread -Wl,-rpath=.

CC=g++
GCC=g++

CCFLAGS= -std=c++11 -Wall -D__USE_GNU -DUNIXFILE -DDEBUG -DLINUX -DHP_UX

ifeq ($(VER), debug)
CCFLAGS += -ggdb
endif

# =====================================================
all:prepare $(TARGET) clean
	mv $(TARGET) $(DESDIR)
	@echo "all is updated."

prepare:
	mkdir -p $(DESDIR)

$(TARGET):$(SOURCE1)
	rm -rf $(DESDIR)/$@
	$(GCC) $(CCFLAGS) -o $@ $(SOURCE1) $(LIBS) $(SYSLIBS) 


.SUFFIXES:.c
.c.o:
	$(CC) -c $(CCFLAGS) $(APINCL) -fPIC $*.c


.SUFFIXES:.cpp
.cpp.o:
	$(CC) -c $(CCFLAGS) $(APINCL) -fPIC $*.cpp

clean:
	rm -f $(SOURCE1)
# =====================================================
dependence:
