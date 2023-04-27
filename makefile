PYTHONFLAGS = -I/usr/include/python3.9 -lpython3.9
EXAMPLE_FILE = plot

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXAMPLES_DIR := examples
OBJ_EXAMPLES_DIR := $(OBJ_DIR)/$(EXAMPLES_DIR)
EXAMPLE := $(OBJ_EXAMPLES_DIR)/$(EXAMPLE_FILE).o

EXE := $(BIN_DIR)/$(EXAMPLE_FILE)

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXXFLAGS := -Iinclude/ $(PYTHONFLAGS) -MMD -MP
CFLAGS := -Wall
LDFLAGS := -Llib/
LDLIBS := 

.PHONY: all clean
all: $(EXE)

$(EXE): $(OBJ) $(EXAMPLE) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(PYTHONFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXAMPLE): $(EXAMPLES_DIR)/$(EXAMPLE_FILE).cpp | $(OBJ_EXAMPLES_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(OBJ_EXAMPLES_DIR)/%.o: $(EXAMPLES_DIR)/%.cpp | $(OBJ_EXAMPLES_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(OBJ_EXAMPLES_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) $(BIN_DIR)

-include $(OBJ:.o=.d)
