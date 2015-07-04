#ifndef _STATE_HPP__
#define _STATE_HPP__

#include "ResourceInfo.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

enum class StateID {

	None,
	Title,
	Menu,
	Game,
	MultiplayerMenu,
	HostGame,
	JoinGame,
	Pause,
	Settings
};

namespace sf {

	class RenderWindow;
}

class StateStack;
class PlayerInput;
class MusicPlayer;
class SoundPlayer;

class State {

public:

	typedef std::unique_ptr<State> statePtr;

	struct ShareView {

		ShareView(sf::RenderWindow& window, TextureContainer& textureContainer, FontContainer& fontContainer, PlayerInput& playerInput, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer);
		sf::RenderWindow* window;
		TextureContainer* textureContainer;
		FontContainer* fontContainer;
		PlayerInput* playerInput;
		MusicPlayer* musicPlayer;
		SoundPlayer* soundPlayer;
	};

	State(StateStack& stateStack, ShareView shareView);
	virtual ~State() = 0;

	virtual void draw() = 0;

	//have the state return false if it's not active
	virtual bool update(sf::Time deltaTime) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:

	void requestStackPush(StateID stateID);
	void requestStackPop();
	void requestStateClear();

	ShareView getSharedView() const;

private:

	StateStack* stateStack;
	ShareView shareView;
};

#endif