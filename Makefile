SRCDIR = Source
INCLUDE = -I${SRCDIR} -I${SRCDIR}/Animation -I${SRCDIR}/Entities -I${SRCDIR}/GUI -I${SRCDIR}/Control -I${SRCDIR}/Resources -I${SRCDIR}/SceneGraph -I${SRCDIR}/States
CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD
EXEC = At-War
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ = AtWar.o World.o Projectile.o Hero.o HeroMover.o HeroAttacker.o GameController.o AnimatedSprite.o Animation.o Data.o Entity.o SceneNode.o SpriteNode.o Component.o Container.o Button.o Command.o CommandQueue.o PlayerInput.o StateStack.o State.o TitleState.o MenuState.o SettingsState.o GameState.o PauseState.o KeyToString.o
OBJECTS = $(addprefix ${SRCDIR}/,${OBJ})
DEPENDS = ${OBJECTS:.o=.d}

${SRCDIR}/%.o: Source/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Animation/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Entities/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/GUI/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Control/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Resources/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/SceneGraph/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/States/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${INCLUDE} ${OBJECTS} -o ${EXEC} ${LIBS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
