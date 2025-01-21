CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic
INC_DIR = include
LIB_DIR = lib
SRC_DIR = src
APP_DIR = app
OBJ_DIR = obj

TARGET_LIB = $(LIB_DIR)/liblogger.so
TARGET_APP = $(APP_DIR)/app

LIB_OBJS = $(OBJ_DIR)/logger.o
APP_OBJS = $(OBJ_DIR)/main.o


all: library application

library: $(TARGET_LIB)

application: $(TARGET_APP)
	

$(TARGET_LIB): $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^

$(TARGET_APP): $(APP_OBJS) $(TARGET_LIB)
	@mkdir -p $(APP_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -llogger 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(APP_DIR)