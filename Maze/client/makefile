#SRC_DIR := /Users/dhruvtyagi/Desktop/mazeverse/SDL_Game
#export SRC_DIR=$(pwd)
#SRC_FILES := $(wildcard $(SRC_DIR)/.cpp) $(wildcard $(SRC_DIR)/ECS/.cpp)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) 
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
incpath := /opt/homebrew/Cellar/
ecspath := $(SRC_DIR)/ECS
LDFLAGS := -I$(incpath) -L$(incpath) 
play: $(SRC_FILES)
	@#echo $(SRC_FILES)
	#echo $(SRC_DIR)
	@g++ -std=c++17 $(LDFLAGS) $^ -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $@
