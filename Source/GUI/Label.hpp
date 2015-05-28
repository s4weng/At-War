#ifndef _LABEL_HPP__
#define _LABEL_HPP__

#include "Component.hpp"
#include "TextureInfo.hpp"

#include <string>
#include <SFML/Graphics.hpp>

class Label : public Component {

public:

	typedef std::shared_ptr<Label> labelPtr;

	Label(const std::string text, const FontContainer& fontContainer);

	void setText(const std::string& text);
	virtual bool isSelectable() const;
	virtual void handleEvent(const sf::Event& event);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text text;
};

#endif