# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Directory structure
BIN_DIR = bin
OBJ_DIR = obj

# Targets
TARGETS = HashTable_LinearProbing \
		HashTables_SeparateChaining

# Create binary paths
BINARIES = $(addprefix $(BIN_DIR)/, $(TARGETS))

# Common objects
COMMON_OBJS = $(OBJ_DIR)/common_utils.o

# Create directories
$(shell if not exist $(BIN_DIR) mkdir $(BIN_DIR))
$(shell if not exist $(OBJ_DIR) mkdir $(OBJ_DIR))

all:$(BINARIES)

# Individual targets
$(BIN_DIR)/HashTable_LinearProbing: HashTable_LinearProbing.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $< $(COMMON_OBJS) -o $@

$(BIN_DIR)/HashTables_SeparateChaining: HashTables_SeparateChaining.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $< $(COMMON_OBJS) -o $@

# Common object files
$(OBJ_DIR)/common_utils.o: Common/common_utils.cpp Common/common_utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	if exist $(BIN_DIR)\* del /Q $(BIN_DIR)\*
	if exist $(OBJ_DIR)\* del /Q $(OBJ_DIR)\*

#List targets
list:
	@echo "Available targets:"
	@for %%t in ($(TARGETS)) do @echo   %%t

.PHONY: all clean list