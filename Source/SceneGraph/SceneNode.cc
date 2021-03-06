#include "SceneNode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

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

	for (auto& nodePtr : children)
		nodePtr->draw(target, states);
}

//pass every node in scenegraph to checkNodeCollision (so every node comparse to every other node)
void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs){

	checkNodeCollision(sceneGraph, collisionPairs);

	for (sceneNodePtr& child : sceneGraph.children)
		checkSceneCollision(*child, collisionPairs);
}

//check every node in scenegraph against the given node
void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs){

	if (this != &node && collision(*this, node))
		collisionPairs.insert(std::minmax(this, &node));

	for (sceneNodePtr& child : children)
		child->checkNodeCollision(node, collisionPairs);
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

sf::FloatRect SceneNode::getBoundingRect() const {

	return sf::FloatRect();
}

void SceneNode::removeDead(){

	auto removeBegin = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::isDead));
	children.erase(removeBegin, children.end());

	std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::removeDead));
}


bool SceneNode::isDead() const {

	return false;
}


void SceneNode::setIsAttack(bool attack){

	isAttack = attack;
}

bool SceneNode::getIsAttack(){

	return isAttack;
}

void SceneNode::update(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData){

	updateCurrent(deltaTime, commandQueue, animationData);
	updateChildren(deltaTime, commandQueue, animationData);
}

void SceneNode::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData){
}

void SceneNode::updateChildren(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData){

	for (auto& nodePtr: children)
		nodePtr->update(deltaTime, commandQueue, animationData);
}

unsigned int SceneNode::getReceiver() const {

	return Receiver::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time deltaTime){
	
	//bitwise & to check if current scenenode is receiver of command
	if (command.receiver & getReceiver())
		command.action(*this, deltaTime);

	else {
	//forward command to child nodes
	for (auto& nodePtr : children)
		nodePtr->onCommand(command, deltaTime);
	}
}


void SceneNode::sortChildren(){

	std::sort(children.begin(), children.end(),
		[] (const sceneNodePtr& a, const sceneNodePtr& b) -> bool {

			return a->getPosition().y < b->getPosition().y;
		});
}


bool collision(const SceneNode& node1, const SceneNode& node2){

	sf::FloatRect bound1 = node1.getBoundingRect();
	sf::FloatRect bound2 = node2.getBoundingRect();

	//projectile has to intersect hero sprite center, not just intersect the boundaries
	return (bound1.intersects(bound2) && abs(node1.getPosition().x - node2.getPosition().x) < 5.f && abs(node1.getPosition().y - node2.getPosition().y) < 20.f); //change 20.f to node2.getSize().y * 0.5 (i.e. within 50 percent of hero sprite center)
}