CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD
OBJECTS = Main.o Game.o AnimatedSprite.o Animation.o Entity.o Hero.o SceneNode.o SpriteNode.o World.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = At-War
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBS}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${DEPENDS} ${EXEC}