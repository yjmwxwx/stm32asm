CXX = g++
LD = g++
OBJS = $(CXXFILES:.cc=.o)

LIBS = -lGL -lGLU `pkg-config --libs gl glew glfw3 openal ogg vorbis vorbisfile`

CXXFLAGS = `pkg-config --cflags gl glew glfw3 openal ogg vorbis vorbisfile` -Wall -g -O2 -std=c++11

CXXFILES =  \
	main.cc \
	demo.cc \
	glutil.cc \
	panic.cc \
	ogg_player.cc

TARGET = demo

all: depend $(TARGET)

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

depend: .depend

.depend: $(CXXFILES)
	rm -f .depend
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f *o $(TARGET) .depend

include .depend

.PHONY: all clean depend
