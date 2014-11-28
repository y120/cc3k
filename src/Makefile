INCLUDES = 
CXX = g++
CXXFLAGS = -Wall -MMD -std=c++11 -Iinclude
LDLIBS = -lX11
OBJECTS = \
	renderable.o \
		character.o \
			abstractPlayerEffect.o \
				floorBoundEffect.o \
					fbModifyAtkEffect.o fbModifyDefEffect.o \
			abstractEnemy.o \
				human.o dwarf.o elf.o orc.o merchant.o dragon.o halfling.o \
			player.o \
				shade.o drow.o vampire.o troll.o goblin.o \
		abstractItem.o \
			goldPile.o \
				dragonHoard.o \
			abstractPotion.o \
				rhPotion.o baPotion.o bdPotion.o phPotion.o waPotion.o wdPotion.o \
	tile.o chamber.o floor.o inventory.o turnSummary.o utilities.o \
	game.o \
    main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ../cc3k
DBGFLAGS = -Wextra -Werror -ggdb -DDEBUG
ASSIGNMENT = a5

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDLIBS}

-include ${DEPENDS}

clean:
	rm -f *.o *.d ${EXEC} ${ASSIGNMENT}.zip

release: ${EXEC}

debug:
	${CXX} ${CXXFLAGS} ${DBGFLAGS} *.cc -o ${EXEC}

rebuild: clean release

package: rebuild clean
	zip ${ASSIGNMENT} *

.PHONY: clean release debug rebuild package

