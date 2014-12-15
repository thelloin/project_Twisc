#Kompilatorn
CC=g++

#Flaggor till kompilatorn
CFLAGS=-std=c++11 -Wall -Wextra -pedantic

#Flaggor till länkaren
LFLAGS= -lSDL2 -lSDL2_image -lSDL2_mixer

all: Twisc

Twisc: game.o Abstract_Gamestate.o Audio.o Level.o Menu.o Play_Screen.o entities/Bullet.o \
entities/Button.o entities/Enemy.o entities/Ground.o entities/Lava.o entities/Player.o \
entities/Shooting_Enemy.o entities/Sprite.o entities/Wall_Of_Death.o
	$(CC) *.o $(LFLAGS) -o Twisc

game.o: game.cpp
	$(CC) $(CFLAGS) -c game.cpp
	
Abstract_Gamestate.o : Abstract_Gamestate.h
	
Audio.o : Audio.cpp Audio.h
	$(CC) $(CFLAGS) -c Audio.cpp
	
Level.o : Level.cpp Level.h
	$(CC) $(CFLAGS) -c Level.cpp
	
Menu.o : Menu.cpp Menu.h
	$(CC) $(CFLAGS) -c Menu.cpp
	
Play_Screen.o : Play_Screen.cpp Play_Screen.h
	$(CC) $(CFLAGS) -c Play_Screen.cpp
	
entities/Bullet.o : entities/Bullet.cpp entities/Bullet.h
	$(CC) $(CFLAGS) -c entities/Bullet.cpp
	
entities/Button.o :  entities/Button.h
	
	
entities/Enemy.o : entities/Enemy.cpp entities/Enemy.h
	$(CC) $(CFLAGS) -c entities/Enemy.cpp
	
entities/Ground.o : entities/Ground.h

entities/Lava.o : entities/Lava.cpp entities/Lava.h
	$(CC) $(CFLAGS) -c entities/Lava.cpp
	
entities/Player.o : entities/Player.cpp entities/Player.h
	$(CC) $(CFLAGS) -c entities/Player.cpp
	
entities/Shooting_Enemy.o : entities/Shooting_Enemy.cpp entities/Shooting_Enemy.h
	$(CC) $(CFLAGS) -c entities/Shooting_Enemy.cpp
	
entities/Sprite.o : entities/Sprite.cpp entities/Sprite.h
	$(CC) $(CFLAGS) -c entities/Sprite.cpp
	
entities/Wall_Of_Death.o : entities/Wall_Of_Death.cpp entities/Wall_Of_Death.h
	$(CC) $(CFLAGS) -c entities/Wall_Of_Death.cpp
	
clean:
	rm -rd *.o Twisc