#include "Label.hpp"

#include <SFML/Graphics.hpp>

Label::Label(const std::string text, const FontContainer& fontContainer) : text(text, fontContainer.get(Fonts::main), 30){
}

void Label::setText(const std::string& text){

	this->text = text;
}

void Label::isSelectable() const {

	return false;
}

void Label::handleEvent(const sf::Event& event){
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	states.transform *= getTransform();
	target.draw(text, states);
}