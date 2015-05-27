#include "Component.hpp"

Component::Component(): active(false), selected(false) {
}

Component::~Component(){
}

bool Component::isActive() const {

	return active;
}

void Component::activate(){

	active = true;
}

void Component::deactivate(){

	active = false;
}

bool Component::isSelected() const {

	return selected;
}

void Component::select(){

	selected = true;
}

void Component::deselect(){

	selected = false;
}