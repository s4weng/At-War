SRCDIR = Source
INCLUDE = -I${SRCDIR} -I${SRCDIR}/Animation -I${SRCDIR}/Graphics -I${SRCDIR}/Network -I${SRCDIR}/GUI -I${SRCDIR}/Audio -I${SRCDIR}/Control -I${SRCDIR}/Resources -I${SRCDIR}/SceneGraph -I${SRCDIR}/States
CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD
EXEC = At-War
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJ = AtWar.o World.o Animation.o AnimatedSprite.o MusicPlayer.o SoundPlayer.o AnimationData.o HeroSoundPlayer.o PostEffect.o BloomEffect.o Projectile.o Hero.o HeroMover.o HeroAttacker.o GameController.o Data.o Entity.o SceneNode.o SoundNode.o SpriteNode.o Component.o Container.o Button.o Command.o CommandQueue.o PlayerInput.o StateStack.o State.o TitleState.o MenuState.o MultiplayerMenuState.o SettingsState.o GameState.o MultiplayerGameState.o PauseState.o KeyToString.o
OBJECTS = $(addprefix ${SRCDIR}/,${OBJ})
DEPENDS = ${OBJECTS:.o=.d}

${SRCDIR}/%.o: Source/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Animation/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Graphics/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Network/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/GUI/%.cc
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

${SRCDIR}/%.o: Source/Audio/%.cc
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
