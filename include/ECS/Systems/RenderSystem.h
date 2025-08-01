#pragma once
#include <memory>
#include <stack>
#include <unordered_map>
#include <map>
#include <filesystem>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ECS/System.h"
#include "ECSSystem.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshRenderer.h"
#include "glad/glad.h"
#include "../../../../extern/tinygltf/tiny_gltf.h"

namespace Engine
{
    class RenderSystem : public System
    {
        void EntityAdded(Entity entity) override;
        void EntityRemoved(Entity entity) override;
        void Render(Entity entity);

    public:
        Transform camera;


        RenderSystem();

        void Render();
    };

} // Engine
