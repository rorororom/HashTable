CXX = g++-13
CXXFLAGS =  -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
			-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts       \
			-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal  \
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline          \
			-Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked            \
			-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo  \
			-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                \
			-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default      \
			-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast           \
			-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing   \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation    \
			-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192         \
			-Wstack-usage=8192 -fsanitize=address -fsanitize=undefined -fPIE -Werror=vla

SOURCES = main.cpp list.cpp log.cpp
OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:%.cpp=%.o))

COMMON_DIR_H = ./hash
OUT_SOURCES_H = ./hash/hash_func.cpp ./hash/hash_table.cpp
OUT_OBJECTS_H = $(addprefix $(OBJ_DIR)/, $(OUT_SOURCES_H:$(COMMON_DIR_H)/%.cpp=%.o))

COMMON_DIR = ./text_tools
OUT_SOURCES = ./text_tools/read_file_in_buffer.cpp
OUT_OBJECTS = $(addprefix $(OBJ_DIR)/, $(OUT_SOURCES:$(COMMON_DIR)/%.cpp=%.o))

EXECUTABLE = hash

.PHONY: all clean generate_image

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(OUT_OBJECTS) $(OUT_OBJECTS_H)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(COMMON_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(COMMON_DIR_H)/%.cpp | $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run:
	./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJ_DIR)
