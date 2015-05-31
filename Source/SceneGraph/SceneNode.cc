#include "SceneNode.hpp"

#include <algorithm> //std::find_if
#include <cassert>

SceneNode::SceneNode(): children(), parent(nullptr) {
}

void SceneNode::attachNode(sceneNodePtr nodePtr){

	nodePtr->parent = this;
	children.push_back(std::move(nodePtr));
}

SceneNode::sceneNodePtr SceneNode::detachNode(SceneNode& node){

	auto result = std::find_if(children.begin(), children.end(),
		[&] (sceneNodePtr& foundNode) -> bool { 

			return foundNode.get() == &node;
		});

	assert (result != children.end()); //find_if returns children.end() if not found

	sceneNodePtr foundNode = std::move(*result);
	foundNode->parent = nullptr;
	children.erase(result);
	return foundNode;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//parent's absolute transform * current node's relative transform == current node's placement
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

//delegate to entity to draw itself
void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const {
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates	states) const {

	//reference to std::unique_ptr to avoid copying
	for (auto& nodePtr : children)
		nodePtr->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const {

	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {

	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* sceneNode = this; sceneNode != nullptr; sceneNode = sceneNode->parent)
		transform = sceneNode->getTransform() * transform;

	return transform;
}

void SceneNode::update(sf::Time deltaTime, CommandQueue& commandQueue){

	updateCurrent(deltaTime, commandQueue);
	updateChildren(deltaTime, commandQueue);
}

void SceneNode::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue){
}

void SceneNode::updateChildren(sf::Time deltaTime, CommandQueue& commandQueue){

	for (auto& nodePtr: children)
		nodePtr->update(deltaTime, commandQueue);
}

int SceneNode::getReceiver() const {

	return Receiver::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time deltaTime){

	//bitwise & to check if current scenenode is receiver of command
	if (command.receiver & getReceiver())
		command.action(*this, deltaTime);

	//forward command to child nodes
	for (auto& nodePtr : children)
		nodePtr->onCommand(command, deltaTime);
}