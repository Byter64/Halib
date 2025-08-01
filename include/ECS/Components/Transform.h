#pragma once
#include "glm/glm.hpp"
#include "glm/ext/quaternion_float.hpp"
#include <list>
#include <string>

namespace Engine
{

    struct Transform
    {
    private:
        bool hasTransformChanged = true;
        glm::mat3 matrix = glm::mat3(1);
        glm::vec2 translation = glm::vec2(0, 0);
        glm::vec2 scale = glm::vec2(1, 1);

        glm::ivec2 spriteScale = glm::ivec2(1, 1); //The wueHans GPU demands a special format for the scaling factors
        glm::bvec2 spriteFlip = glm::bvec2(false, false);

        bool isGlobalTranslationOutdated = true;
        bool isGlobalScaleOutdated = true;
        bool isGlobalMatrixOutdated = true;
        glm::mat3 globalMatrix = glm::mat3(1);
        glm::vec2 globalTranslation = glm::vec2(0, 0);
        glm::vec2 globalScale = glm::vec2(1, 1);

        Transform* parent = nullptr;
        std::list<Transform*> children;

        void SetIsGlobalTranslationOutdated();
        void SetIsGlobalScaleOutdated();

        void SetSpriteVariables(glm::vec2 scale);
        void UpdateScales();

    public:
        Transform() = default;
        Transform(glm::vec2 position, glm::vec2 scale);
        Transform(Transform& other) = default;

        Transform& operator= (Transform& other) = default;
        Transform& operator= (Transform&& other);

        glm::vec2 GetTranslation();
        glm::vec2 GetGlobalTranslation();
        void SetTranslation(const glm::vec2& translation);
        void SetGlobalTranslation(const glm::vec2& translation);
        void AddTranslation(const glm::vec2& translation);

        glm::ivec2 GetSpriteScale();
        glm::bvec2 GetSpriteFlip();
        glm::vec2 GetScale();
        glm::vec2 GetGlobalScale();
        void SetScale(const glm::vec2& scale);
        void AddScale(const glm::vec2& scale);

        const glm::mat2x3& GetMatrix();
        const glm::mat2x3& GetGlobalMatrix();

        void SetParent(Transform* parent);
        Transform* GetParent();

        Transform* GetChild(int index);
        std::list<Transform*>& GetChildren();

        std::string ToString();
        std::string MatrixToString();
        std::string GlobalTranslationToString();
    };

} // Engine
