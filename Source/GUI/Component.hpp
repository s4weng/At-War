#ifndef _COMPONENT_HPP__
#define _COMPONENT_HPP__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {

public:

	typedef std::shared_ptr<Component> componentPtr;

	Component();
	virtual ~Component();

	virtual bool isActive() const;
	virtual void activate();
	virtual void deactivate();
	
	virtual bool isSelectable() const = 0;
	bool isSelected() const;
	virtual void select();
	virtual void deselect();

	virtual void handleEvent(const sf::Event& event) = 0;

private:

	bool active, selected;
};


#endif