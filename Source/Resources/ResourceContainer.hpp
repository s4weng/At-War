#ifndef _RESOURCEHOLDER_HPP__
#define _RESOURCEHOLDER_HPP__

#include <map>
#include <string>
#include <cassert>
#include <stdexcept>
#include <memory>

//Resource can be used for both textures and sounds
template <typename Resource, typename ID>
class ResourceContainer {

public:

	void load(ID id, const std::string& fileName);
	void load(ID id, const std::string& fileName, const std::string& secondParam);
	Resource& get(ID id);

private:

	void insertResource(ID id, std::unique_ptr<Resource> resource);

	std::map<ID, std::unique_ptr<Resource>> resourceMap;
};

#include "ResourceContainer.inl"
#endif