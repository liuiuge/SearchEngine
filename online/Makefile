
EXE:= ./bin/main
INC_DIR:= ./inc ./inc/cppjieba
SRC_DIR:= ./src
SRCS:= $(wildcard $(SRC_DIR)/*.cc)
LIBS:= -lpthread ./lib/libjsoncpp.a
CXXFLAGS:= -std=c++11 -g

$(EXE):$(SRCS)
	g++ -g -o $@ $^  $(LIBS) $(addprefix -I, $(INC_DIR)) $(CXXFLAGS)
clean:
	rm ./bin/main
