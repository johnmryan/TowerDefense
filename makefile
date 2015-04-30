#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAMES = main.o Object.o Enemy.o HealthBar.o Goblin.o Troll.o Dragon.o Wizard.o \
Tower.o TowerSpace.o ArcherTower.o CannonTower.o FreezeTower.o WizardTower.o MapDirections.o

#This is the target that compiles our executable
all: main

main: $(OBJ_NAMES)
	$(CC) *.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o main

main.o: main.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c main.cpp

Object.o: Object.cpp Object.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Object.cpp

Enemy.o: Enemies/Enemy.cpp Enemies/Enemy.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Enemy.cpp

HealthBar.o: Enemies/HealthBar.cpp Enemies/HealthBar.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/HealthBar.cpp

Goblin.o: Enemies/Goblin.cpp Enemies/Goblin.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Goblin.cpp

Troll.o: Enemies/Troll.cpp Enemies/Troll.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Troll.cpp

Dragon.o: Enemies/Dragon.cpp Enemies/Dragon.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Dragon.cpp

Wizard.o: Enemies/Wizard.cpp Enemies/Wizard.h MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Enemies/Wizard.cpp

Tower.o: Towers/Tower.cpp Towers/Tower.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Towers/Tower.cpp

TowerSpace.o: Towers/TowerSpace.cpp Towers/TowerSpace.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Towers/TowerSpace.cpp

ArcherTower.o: Towers/ArcherTower.cpp Towers/ArcherTower.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Towers/ArcherTower.cpp

CannonTower.o: Towers/CannonTower.cpp Towers/CannonTower.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Towers/CannonTower.cpp

FreezeTower.o: Towers/FreezeTower.cpp Towers/FreezeTower.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Towers/FreezeTower.cpp

WizardTower.o: Towers/WizardTower.cpp Towers/WizardTower.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c Towers/WizardTower.cpp

MapDirections.o: MapDirections.cpp MapDirections.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c MapDirections.cpp

clean: 
	-rm *.o main
