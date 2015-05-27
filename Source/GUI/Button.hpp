#ifndef _BUTTON_HPP__
#define _BUTTON_HPP__

#include "Component.hpp"
#include "TextureInfo.hpp"

#include <memory>

#include <functional>
#include <string>

class Button : public Component {

public:

	typedef std::shared_ptr<Button> buttonPtr;
	typedef std::function<void()> Callback;

	Button(FontContainer& fonts, TextureContainer& textureContainer);

	void setCallback(Callback callback);
	void setText(const std::string& text);
	void setToggle(bool toggle);

	virtual void activate();
	virtual void deactivate();
	virtual bool isSelectable() const;
	virtual void select();
	virtual void deselect();

	virtual void handleEvent(const sf::Event& event);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Callback callback;
	const sf::Texture& texture;
	const sf::Texture& selectedTexture;
	const sf::Texture& pressedTexture;
	sf::Sprite sprite;
	sf::Text text;
	bool toggle;
};


#endif