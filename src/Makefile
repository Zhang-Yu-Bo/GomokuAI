OBJECTS = Game.o Board.o Player.o Common.o Human.o Computer.o
GAME_SYS_DIR = ./GameSystem
PLAYER_SYS_DIR = ./PlayerSystem

Computer.o: $(PLAYER_SYS_DIR)/Computer.cpp $(PLAYER_SYS_DIR)/Computer.h
	g++ -c $(PLAYER_SYS_DIR)/Computer.cpp

Human.o: $(PLAYER_SYS_DIR)/Human.cpp $(PLAYER_SYS_DIR)/Human.h
	g++ -c $(PLAYER_SYS_DIR)/Human.cpp

Common.o: Common.cpp Common.h
	g++ -c Common.cpp

Player.o: $(PLAYER_SYS_DIR)/Player.cpp $(PLAYER_SYS_DIR)/Player.h
	g++ -c $(PLAYER_SYS_DIR)/Player.cpp

Board.o: $(GAME_SYS_DIR)/Board.cpp $(GAME_SYS_DIR)/Board.h
	g++ -c $(GAME_SYS_DIR)/Board.cpp

Game.o: $(GAME_SYS_DIR)/Game.cpp $(GAME_SYS_DIR)/Game.h
	g++ -c $(GAME_SYS_DIR)/Game.cpp

start: $(OBJECTS)
	g++ -o main.exe main.cpp $(OBJECTS)

clean:
	del *.o
	del *.exe