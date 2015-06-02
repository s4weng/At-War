#ifndef _CONTAINER_HPP__
#define _CONTAINER_HPP__

#include "Component.hpp"

#include <vector>
#include <memory>

class Container : public Component {

public:

	typedef std::shared_ptr<Container> containerPtr;

	Container();

	void pack(componentPtr component);
	virtual bool isSelectable() const;
	
	virtual void handleEvent(const sf::Event& event);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool hasSelection() const;
	void select(int index);
	void selectNext();
	void selectPrevious();

	std::vector<componentPtr> children;
	int selectedChild;
};

#endif