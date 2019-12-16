#ifndef RESOURCE_H
#define RESOURCE_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

// Resource ID for sf::Texture
namespace Textures
{
	enum ID
	{
		Background,
		Spaceship,
		Enemy,
		Missile
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	
	void						load(Identifier id, const std::string& filename);

	template <typename Parameter> // only gets created when we actually call it, based on how we call it
	void						load(Identifier id, const std::string& filename, const Parameter& secondParam);

	
	
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

	/*
	sf::Sprite					background;
	sf::Sprite					spaceship;
	*/
private:
	void						insertResource(Identifier id, std::unique_ptr<Resource> resource); // being used to add resource to standard map


private:
	std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "resourceholder.inl"

#endif // BOOK_RESOURCEHOLDER_HPP