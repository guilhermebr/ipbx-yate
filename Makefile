COMPILER = g++ -Wall
CXXLDFLAGS = `yate-config --c-all --ldflags` 
LIBRARIES = `yate-config --libs` 
INCLUDEDIR = -I./src/include

#OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJFILES := $(wildcard src/*.cpp)

all : ipbx

ipbx: $(OBJFILES)
	${COMPILER} ${CXXLDFLAGS} $(OBJFILES) ${LIBRARIES} ${INCLUDEDIR} -o ipbx.yate

clean:
	rm -f *.o ipbx.yate

install:
	cp -rf ipbx.yate /usr/local/lib/yate/

dev:
	cp -rf ipbx.yate ${YATE_DEV}/modules/

