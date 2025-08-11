#ifndef ENTITYMANAGER_H  
#define ENTITYMANAGER_H  
#include <cstdint>  
#include <queue>  
#include <bitset>  
#include <array> // Include the array header to resolve the incomplete type error  
#include <cassert>  

// A simple type alias  
using Entity = std::uint32_t;
// Used to define the size of arrays later on  
const Entity MAX_ENTITIES = 5000;
// A simple type alias  
using ComponentType = std::uint8_t;
// Used to define the size of arrays later on  
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

//This creates and deletes LivingEntities n Available Entities
// It gives Signature value to the Entity id(index), and can get it from SIgnature
class EntityManager {
public:
    EntityManager() {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            // Queue that pushes entity into it  
            mAvailableEntities.push(entity);
        }
    }

    // CreateEntity  
    Entity CreateEntity() {
        assert(mLivingEntityCount < MAX_ENTITIES && "Too Many existing Living Entities.");
        Entity id = mAvailableEntities.front(); //id = [0]... 
        mAvailableEntities.pop();  // Entity not Available, now mLiving
        ++mLivingEntityCount;
        return id;
    }

   // DeleteEntity  
   void DeleteEntity(Entity entity) {  
       assert(entity < MAX_ENTITIES && "Entity out of Range.");  
       mSignatures[entity].reset();  //mSignatures clear
       mAvailableEntities.push(entity);  // push to back of queue
       --mLivingEntityCount;  
   }  

   // SetSignature  Signature= What components an Entity uses. 
   // Using bitset: std::bitset<num of component>
   // so if Player Entity has all 3 types.
   // Signature sig; sig.set(0); // Transform || sig.set(1); // RigidBody || sig.set(2); // Gravity
   // 0b111. Bit 0 is 1 ? has Transform, 
   // Bit 1 is 1 ? has RigidBody
   // Bit 2 is 1 ? has Gravity
   void SetSignature(Entity entity, Signature signature) {  
       assert(entity < MAX_ENTITIES && "Entity out of Range.");  
       mSignatures[entity] = signature;  // dont set here, we just def msignature here
   }  

   // GetSignature  
   Signature GetSignature(Entity entity) {  
       assert(entity < MAX_ENTITIES && "Entity out of Range.");  
       return mSignatures[entity];  
   }  

private:  
   std::queue<Entity> mAvailableEntities{};  
   std::array<Signature, MAX_ENTITIES> mSignatures{};  
   uint32_t mLivingEntityCount = 0; // Initialize mLivingEntityCount to 0  
};  

#endif
