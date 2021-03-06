CC = g++
EXE = egend
SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

LDLIBS += -lpthread -lssl -lz -luWS -lpca9685 -lbcm2835

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ)
