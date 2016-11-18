/*MIT License

Copyright (c) 2016 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef APE_ENTITY_H
#define APE_ENTITY_H

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace Ape
{
	class Entity
	{ 
	public:
		enum Type
		{
			LIGHT,
			GEOMETRY_FILE,
			GEOMETRY_MANUAL,
			GEOMETRY_TEXT,
			GEOMETRY_PRIMITVE_BOX,
			MATERIAL_FILE,
			MATERIAL_MANUAL,
			TEXTURE,
			CAMERA,
			COLLISION,
			INVALID
		};
		
	protected:
		Entity(std::string name, std::string parentNodeName, Type type) : mName(name), mParentNodeName(parentNodeName), mType(type) {};
		
		virtual ~Entity() {};
		
		std::string mName;
		
		std::string mParentNodeName;
		
		Type mType;
		
	public:
		std::string getName() { return mName; };

		Type getType() { return mType; };

		std::string getParentNodeName() { return mParentNodeName; };
	};

	typedef std::shared_ptr<Entity> EntitySharedPtr;

	typedef std::weak_ptr<Entity> EntityWeakPtr;

	typedef std::vector<EntitySharedPtr> EntitySharedPtrVector;
	
	typedef std::vector<EntityWeakPtr> EntityWeakPtrVector;
	
	typedef std::map<std::string, EntityWeakPtr> EntityWeakPtrNameMap;
	
	typedef std::map<std::string, EntitySharedPtr> EntitySharedPtrNameMap;
}

#endif