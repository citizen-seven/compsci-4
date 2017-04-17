.PHONY: clean run

TARGET = ./fraction
FLAGS = -Wall -g 
OBJS = fraction.o
DEPS = $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	g++ -o $@ $^

-include $(DEPS)

%.o: %.cpp
	g++ $(FLAGS) -c -o $@ $<
	g++ $(FLAGS) -MM -o $(patsubst %.o, %.d, $@) $<


clean:
	-rm $(OBJS) $(TARGET)
	-find . -name "*.d" | xargs rm

run:
	$(TARGET)
