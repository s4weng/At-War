#include "Button.hpp"
#include <iostream>

#include <SFML/Window.hpp>

Button::Button(FontContainer& fonts, TextureContainer& textureContainer):
callback(),
texture(textureContainer.get(textureSheet::normalButton)),
selectedTexture(textureContainer.get(textureSheet::selectedButton)),
pressedTexture(textureContainer.get(textureSheet::pressedButton)),
sprite(),
text("", fonts.get(Fonts::main), 30),
toggle(false){

	sprite.setTexture(texture);

	sf::FloatRect bounds = sprite.getLocalBounds();
	text.setPosition(bounds.width / 2.f, bounds.height / 2.5f);
}

void Button::setCallback(Callback callback){

	this->callback = std::move(callback);
}

void Button::setText(const std::string& text){

	this->text.setString(text);
	this->text.setColor(sf::Color::Blue);

	sf::FloatRect bounds = this->text.getLocalBounds();
	this->text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setToggle(bool toggle){

	this->toggle = toggle;
}

void Button::activate(){

	Component::activate();

	if (toggle){
		//std::cout << "pressedStateNow" << std::endl;
		sprite.setTexture(pressedTexture);
	}

	if (callback)
		callback();

	//don't keep activated since button is not pressed down
	if (!toggle)
		deactivate();
}

void Button::deactivate(){

	Component::deactivate();

	if (toggle){

		if (isSelected()){
			//std::cout << "selectedStateNow " << std::endl;
			sprite.setTexture(selectedTexture);
		}

		else
			sprite.setTexture(texture);
	}
}

bool Button::isSelectable() const {

	return true;
}

void Button::select(){

	Component::select();
	sprite.setTexture(selectedTexture);
}

void Button::deselect(){

	Component::deselect();
	sprite.setTexture(texture);
}

void Button::handleEvent(const sf::Event& event){
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(sprite, states);
	target.draw(text, states);
}