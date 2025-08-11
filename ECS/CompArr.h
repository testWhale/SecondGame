#ifndef COMPARR_H
#define COMPARR_H
#include "EntityManager.h"
#include <unordered_map>
class IComponentArray
{
public:
	// destructor that uses virtual to destroy both *IComponentArray & NewComponent
	// IComponentArray* comp= new Component();
	// delete comp;
	virtual ~IComponentArray() = default;
	//
	virtual void EntityDestroyed(Entity entity) = 0;
};

// CompArr = [Transfrom1, Transform2, Transform3 , ...];
// EntityMang Creates the entity-> comp map n vice versa
// Entity only has signature that shows 0b111 (Transform: True, RigidBody: True, ...)
// So we nd a way to take signature n assign the right comp.
// CompArr stores our Component in a dense easy to access way
template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end and update the maps
		size_t newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentArray[newIndex] = component;
		++mSize;
	}
	
	//rmv element ??? frm Entity and mv the last element to the missing spot. 
	// mantain density, O(1) deletion 
	void RemoveData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1;
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		--mSize;
	}

	T& GetData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

		// Return a reference to the entity's component 
		return mComponentArray[mEntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
		{
			// Remove the entity's component if it existed
			RemoveData(entity);
		}
	}

private:
	// The packed array of components (of generic type T),
	// set to a specified maximum amount, matching the maximum number
	// of entities allowed to exist simultaneously, so that each entity
	// has a unique spot.
	// looks like = [Transfrom1, Transform2, Transform3];
	std::array<T, MAX_ENTITIES> mComponentArray;
	// so when matched with EntityToIndexMap
	// Map from an entity ID to an array index.
	std::unordered_map<Entity, size_t> mEntityToIndexMap;
	//looks like: { 1001: 0, 1002: 1, 1003: 2 }

	// Map from an array index to an entity ID.
	std::unordered_map<size_t, Entity> mIndexToEntityMap;

	// Total size of valid entries in the array.
	size_t mSize;
};
#endif 