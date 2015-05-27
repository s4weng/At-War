#include "Container.hpp"

#include <SFML/Window.hpp>
#include <iostream>

Container::Container() : children(), selectedChild(-1){
}

void Container::pack(componentPtr component){

	children.push_back(component);

	if(!hasSelection() && component->isSelectable())
		select(children.size() - 1);
}

bool Container::isSelectable() const{

	return false; //container is not selectable component
}

void Container::handleEvent(const sf::Event& event){

	if (hasSelection() && children[selectedChild]->isActive()){

		std::cout << "letting child handle event" << std::endl;
		children[selectedChild]->handleEvent(event);
	}

	else if (event.type == sf::Event::KeyPressed){

		if (event.key.code == sf::Keyboard::Up)
			selectPrevious();
		
		else if (event.key.code == sf::Keyboard::Down)
			selectNext();
		
		else if (event.key.code == sf::Keyboard::Return){

			//std::cout << "activating child!" << std::endl;
			if (hasSelection())
				children[selectedChild]->activate();
		}
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();

	for (const componentPtr& child : children)
		target.draw(*child, states);
}

bool Container::hasSelection() const{

	return selectedChild >= 0;
}

void Container::select(int index){

	if (children[index]->isSelectable()){

		if (hasSelection())
			children[selectedChild]->deselect();

		children[index]->select();
		selectedChild = index;
	}
}

void Container::selectNext(){

	if (!hasSelection())
		return;

	int next = selectedChild;

	do
		next = (next + 1) % children.size();
	while (!children[next]->isSelectable());

	select(next);
}

void Container::selectPrevious(){

	if (!hasSelection())
		return;

	int previous = selectedChild;

	do
		previous = (previous + children.size() - 1) % children.size();
	while (!children[previous]->isSelectable());

	select(previous);
}