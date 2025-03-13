# 编译器设置
CXX=g++
CXXFLAGS=-std=c++11 -Wall

# 源文件和目标文件
SRC_FILES=main.cpp StockSignalGenerator.cpp
OBJ_FILES=$(SRC_FILES:.cpp=.o)
OUT_FILE=my_program

# 默认目标，编译和链接
all: $(OUT_FILE)

$(OUT_FILE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(OUT_FILE)

# 编译源文件为目标文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理目标文件
clean:
	rm -f $(OBJ_FILES) $(OUT_FILE)

# 运行程序
run: $(OUT_FILE)
	./$(OUT_FILE)
