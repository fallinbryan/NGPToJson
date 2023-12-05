# Path to zlib source
ZLIB_DIR = ./dependencies/zlib

# zlib source files
ZLIB_SRCS = $(wildcard $(ZLIB_DIR)/*.c)

# Source file for your program
SRC = main.cpp

# Object file for your program (replace .cpp with .o)
OBJ = main.o

# Include directory for zlib headers
CPPFLAGS += -I$(ZLIB_DIR)

# Object files for zlib
ZLIB_OBJS = $(ZLIB_SRCS:.c=.o)

# Your project's object files
OBJS = $(OBJ) $(ZLIB_OBJS)

# Rule to compile zlib object files
$(ZLIB_DIR)/%.o: $(ZLIB_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rule to compile your main.cpp
$(OBJ): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Link your program with zlib
ngp2json: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)
