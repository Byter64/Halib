#pragma once
#include <filesystem>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ECS/System.h"
#include "ECSSystem.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RectangleRenderer.h"
#include "ECS/Components/TextRenderer.h"
#include "ECS/Helpers/Color.h"

namespace Engine
{

    class RenderSystem : public System
    {
        friend class SpriteRenderer;

        void EntityAdded(Entity entity) override;
        void EntityRemoved(Entity entity) override;
        void Render(Entity entity);
        void RenderSprite(Entity entity);
        void RenderText(Entity entity);
        void RenderRectangle(Entity entity);

        /// @brief Clears the whole screen with the given color
	    /// @param color 
	    void Clear(Color color);

        std::vector<Entity> sortedEntities{};
        void ResortEntity(Entity entity);
    public:
        Transform camera;
        Color backgroundColor; //If transparent, background will not be cleared
        
        
        RenderSystem();
        static void WaitForGPU();

        void Render();
    };

} // Engine
