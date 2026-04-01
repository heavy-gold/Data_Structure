# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Directory structure
BIN_DIR = bin
OBJ_DIR = obj

# Targets
TARGETS = HashTable_LinearProbing \
		HashTables_SeparateChaining \
		HashTable_QuadraticProbing

# Create binary paths
BINARIES = $(addprefix $(BIN_DIR)/, $(TARGETS))

# Common objects
COMMON_OBJS = $(OBJ_DIR)/common_utils.o

# Create directories
$(shell mkdir $(BIN_DIR) 2>NUL)
$(shell mkdir $(OBJ_DIR) 2>NUL)

all:$(BINARIES)

# Individual targets
$(BIN_DIR)/HashTable_LinearProbing: HashTable_LinearProbing.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $< $(COMMON_OBJS) -o $@

$(BIN_DIR)/HashTables_SeparateChaining: HashTables_SeparateChaining.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $< $(COMMON_OBJS) -o $@

$(BIN_DIR)/HashTable_QuadraticProbing: HashTable_QuadraticProbing.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $< $(COMMON_OBJS) -o $@

# Common object files
$(OBJ_DIR)/common_utils.o: Common/common_utils.cpp Common/common_utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule (Works in Sh/Bash environments)
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

#List targets
list:
	@echo "Available targets:"
	@for %%t in ($(TARGETS)) do @echo   %%t

.PHONY: all clean list