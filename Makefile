CC = g++
CFLAGS = -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations   \
		 -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy     \
		 -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2     \
		 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith       \
		 -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
		 -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef   \
		 -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range 			     \
		 -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast 			 \
		 -Wno-varargs -Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant \
		 -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector 		 \
		 -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector  \
		 -fPIE -Werror=vla

LDFLAGS =

BUILD_DIR = build
GRAPH_DIR = graph
TREE_DIR = tree
PATH_DIR = path
COMMON_DIR = common

SOURCES_GRAPH = main.cpp graph.cpp
SOURCES_TREE = tree.cpp
SOURCES_COMMON = circular_buffer.cpp logger.cpp
SOURCES_PATH = path.cpp


SRC_GRAPH = $(addprefix $(GRAPH_DIR)/, $(SOURCES_GRAPH))
SRC_TREE = $(addprefix $(TREE_DIR)/, $(SOURCES_TREE))
SRC_COMMON = $(addprefix $(COMMON_DIR)/, $(SOURCES_COMMON))
SRC_PATH = $(addprefix $(PATH_DIR)/, $(SOURCES_PATH))

SOURCES = $(SRC_GRAPH) $(SRC_TREE) $(SRC_COMMON) $(SRC_PATH)

OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))
DEPS_STACK = $(OBJECTS:%.o=%.d)

EXECUTABLE = build/meow

CFLAGS += -I$(GRAPH_DIR) -I$(TREE_DIR) -I$(COMMON_DIR) -I$(PATH_DIR)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif
