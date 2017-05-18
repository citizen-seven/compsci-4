.PHONY: clean run

TARGET = ./example1
FLAGS = -w -g `wx-config --cflags` 
OBJS = example1.o
DEPS = $(OBJS:.o=.d)


$(TARGET): $(OBJS)
	g++ -o $@ $^ `wx-config --libs`

-include $(DEPS)

%.o: %.cpp
	g++ $(FLAGS) -c -o $@ $< 
	g++ $(FLAGS) -MM -o $(patsubst %.o, %.d, $@) $<

clean:
	-rm $(OBJS) $(TARGET)
	-find . -name "*.d" | xargs rm

run:
	$(TARGET)

debug: FLAGS += -DDEBUG
debug: $(TARGET)
