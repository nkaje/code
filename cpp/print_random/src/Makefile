# Where to find user code
USER_DIR = .

CXX = g++
INC = -I$(USER_DIR)

CPPFLAGS += -isystem ./
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Werror -Wextra -Wconversion -Wl,-rpath=$(INC) -pthread

# Executable produced by this Makefile
TESTS = pr

# House-keeping build targets.
all : $(TESTS)
clean :
	rm -f $(TESTS) $(USER_DIR)/*.o $(USER_DIR)/*.so

SRCS = $(wildcard ${USER_DIR}/*.cc)
OBJS = $(SRCS:*.cc=.o)
$(OBJS) = $(USER_DIR)/*.h

# Make an object file for each cc file found
#.cc.o: $(CXX) $(CXXFLAGS) -c $(USER_DIR)/$^  ${CPPFLAGS}

pr: $(OBJS)
	$(CXX) $(CXXFLAGS) -lpthread $^ -ldl -o $@ $(CPPFLAGS)
