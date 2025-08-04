#include "Engine.h"
#include "EntityUtility.h"

#include <iostream>
#include <queue>
#include "ECS/Components/Animation.h"

namespace Engine
{
    /**
     * Finds a child with a name name in root and returns it. Prints a warning. if rot has not both a Name and a Transform component.
     * Uses breadth-first search.
     * @param root A parent of the looked for child. Does not need to be a direct parent.
     * @param name The name of the child which is looked for
     * @return The found entity, or INVALID_ENTITY_ID if none was found.
     */
    Entity FindChild(Entity root, Name name)
    {
        if(!ecsSystem->HasComponent<Name>(root))
        {
            std::cout << "ERROR: FindChild(Entity root, Name name) was called with a root that does not have a Name component. \n"
                      << "EntityID of root is: " << root << "\n";
            return Entity::INVALID_ENTITY_ID;
        }

        if(!ecsSystem->HasComponent<Transform>(root))
        {
            std::cout << "ERROR: FindChild(Entity root, Name name) was called with a root that does not have a Transform component. \n"
                      << "EntityID of root is: " << root << "\n"
                      << "Entity name of root is: " << ecsSystem->GetComponent<Name>(root).c_str() << "\n";
            return Entity::INVALID_ENTITY_ID;
        }

        if(ecsSystem->GetComponent<Name>(root) == name)
            return root;

        std::queue<Entity> entityQueue;
        entityQueue.push(root);

        while(!entityQueue.empty())
        {
            Entity subject = entityQueue.front();
            entityQueue.pop();

            if(ecsSystem->GetComponent<Name>(subject) == name)
                return subject;

            for(Transform* childTransform : ecsSystem->GetComponent<Transform>(subject).GetChildren())
                entityQueue.push(ecsSystem->GetEntity(*childTransform));
        }

        std::cout << "WARNING: No child with name \"" << name << "\" in " << root << " found. \n"
                  << "Root name is: \"" << ecsSystem->GetComponent<Name>(root) << "\".\n";
        return Entity::INVALID_ENTITY_ID;
    }

    Entity CopyEntity(Entity entity, bool copyChildren = true)
    {
        Entity newEntity = ecsSystem->CreateEntity();

        if(ecsSystem->HasComponent<Name>(entity))
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<Name>(entity) + " Cloned");
        if(ecsSystem->HasComponent<SpriteRenderer>(entity))
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<SpriteRenderer>(entity));
        if(ecsSystem->HasComponent<BoxCollider>(entity))
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<BoxCollider>(entity));
        if(ecsSystem->HasComponent<TilemapCollider>(entity))
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<TilemapCollider>(entity));
        //if(ecsSystem->HasComponent<Text>(entity))
        //    ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<Text>(entity));
        if(ecsSystem->HasComponent<Animator>(entity))
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<Animator>(entity));
        if(ecsSystem->HasComponent<Animation>(entity))
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<Animation>(entity));

        if(ecsSystem->HasComponent<Transform>(entity))
        {
            ecsSystem->AddComponent(newEntity, ecsSystem->GetComponent<Transform>(entity));
            Transform& newTransform = ecsSystem->GetComponent<Transform>(newEntity);
            newTransform.GetChildren().clear();

            if(copyChildren)
            {
                Transform& transform = ecsSystem->GetComponent<Transform>(entity);
                for(Transform* childTransform : transform.GetChildren())
                {
                    Entity child = ecsSystem->GetEntity(*childTransform);
                    Entity newChild = CopyEntity(child, copyChildren);
                    Transform& newChildTransform = ecsSystem->GetComponent<Transform>(newChild);
                    newChildTransform.SetParent(&newTransform);
                }
            }
        }

        return newEntity;
    }

    /// Removes the given entity plus all children within the transform hierarchy. In case entity does not have a Transform or no children, RemoveEntityWithChildren will behave identical with ECSSystem.RemoveEntity
    /// \param entity
    void RemoveEntityWithChildren(Entity entity, bool removeParent)
    {
        if(ecsSystem->HasComponent<Transform>(entity))
        {
            Transform& transform = ecsSystem->GetComponent<Transform>(entity);
            for(auto& childTransform : transform.GetChildren())
            {
                Entity child = ecsSystem->GetEntity<Transform>(*childTransform);
                RemoveEntityWithChildren(child, true);
            }
        }

        if(removeParent)
            ecsSystem->RemoveEntity(entity);
    }
} // Engine