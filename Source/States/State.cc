#include "StateStack.hpp"

State::ShareView::ShareView(sf::RenderWindow& window, TextureContainer& textureContainer, FontContainer& fontContainer, PlayerInput& playerInput):
window(&window),
textureContainer(&textureContainer),
fontContainer(&fontContainer),
playerInput(&playerInput){	
}

State::State(StateStack& stateStack, ShareView shareView):
stateStack(&stateStack),
shareView(shareView){
}

State::~State(){
}

void State::requestStackPush(StateID stateID){

	stateStack->pushState(stateID);
}

void State::requestStackPop(){

	stateStack->popState();
}

void State::requestStateClear(){

	stateStack->clearStates();
}

State::ShareView State::getSharedView() const {

	return shareView;
}