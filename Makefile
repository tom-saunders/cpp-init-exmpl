.PHONY: all
all: main

srcs = $(wildcard *.cc)
objs = ${srcs:.cc=.o}


%.o: %.cc %.h
	${CXX} ${cxxflags} ${CPPFLAGS} ${TARGET_ARCH} -c ${OUTPUT_OPTION} $<

main: ${objs}
	${CXX} $^ ${LOADLIBES} ${LDLIBS} -o $@

.PHONY: clean
clean:
	-rm -f ${objs} main

cxxflags := ${NULL}
cxxflags += -g
cxxflags += -std=gnu++17
cxxflags += -Wall
cxxflags += -Wextra
cxxflags += -Werror

cxxflags += ${CXXFLAGS}
