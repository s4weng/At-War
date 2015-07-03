#include "Button.hpp"
#include "SoundPlayer.hpp"

#include <SFML/Window.hpp>

Button::Button(State::ShareView shareView):
callback(),
texture(shareView.textureContainer->get(TextureSheet::normalButton)),
selectedTexture(shareView.textureContainer->get(TextureSheet::selectedButton)),
pressedTexture(shareView.textureContainer->get(TextureSheet::pressedButton)),
sounds(*(shareView.soundPlayer)),
sprite(),
text("", shareView.fontContainer->get(Fonts::main), 30),
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
	this->text.setColor(sf::Color::White);

	sf::FloatRect bounds = this->text.getLocalBounds();
	this->text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setToggle(bool toggle){

	this->toggle = toggle;
}

void Button::activate(){

	Component::activate();

	if (toggle)
		sprite.setTexture(pressedTexture);

	if (callback)
		callback();

	sounds.play(SoundEffect::buttonPress);

	//don't keep activated since button is not pressed down
	if (!toggle)
		deactivate();
}

void Button::deactivate(){

	Component::deactivate();

	if (toggle){

		if (isSelected())
			sprite.setTexture(selectedTexture);

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