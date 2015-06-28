template <typename Resource, typename ID>
void ResourceContainer<Resource, ID>::load(ID id, const std::string& fileName){

	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(fileName))
		throw std::runtime_error("Failed to load: " + fileName);

	insertResource(id, std::move(resource));
}

template <typename Resource, typename ID>
void ResourceContainer<Resource, ID>::load(ID id, const std::string& fileName, const std::string& secondParam){

	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(fileName, secondParam))
		throw std::runtime_error("Failed to load " + fileName);

	insertResource(id, std::move(resource));
}

template <typename Resource, typename ID>
Resource& ResourceContainer<Resource, ID>::get(ID id){

	auto found = resourceMap.find(id);
	
	//map.find(id) returns map.end() if id not found
	assert(found != resourceMap.end());
	return *found->second;
}

template <typename Resource, typename ID>
void ResourceContainer<Resource, ID>::insertResource(ID id, std::unique_ptr<Resource> resource){

	//map.insert(pair) returns a pair where pair.second is a bool denoting result of insertion
	auto result = resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(result.second);
}