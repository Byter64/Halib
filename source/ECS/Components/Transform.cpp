#include "ECS/Components/Transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include <iostream>
#include "Engine.h"
namespace Engine
{
    Transform::Transform(glm::vec2 position, glm::vec2 scale) : translation(position), scale(scale)
    {
        parent = nullptr;
    }

    glm::vec2 Transform::GetTranslation()
    {
        return translation;
    }

    void Transform::SetTranslation(const glm::vec2 &translation)
    {
        this->translation = translation;
        hasTransformChanged = true;
        
        SetIsGlobalTranslationOutdated();
    }

    void Transform::SetGlobalTranslation(const glm::vec2 &translation)
    {
        glm::vec2 localTranslation = translation;
        if(parent != nullptr)
            localTranslation = translation - parent->GetGlobalTranslation();
        SetTranslation(localTranslation);
    }

    void Transform::AddTranslation(const glm::vec2 &translation)
    {
        this->translation += translation;
        hasTransformChanged = true;

        SetIsGlobalTranslationOutdated();
    }

    glm::ivec2 Transform::GetSpriteScale()
    {
        UpdateScales();
        return spriteScale;
    }

    glm::bvec2 Transform::GetSpriteFlip()
    {
        UpdateScales();
        return spriteFlip;
    }

    glm::vec2 Transform::GetScale()
    {
        return scale;
    }

    void Transform::SetScale(const glm::vec2 &scale)
    {
        this->scale = scale;
        hasTransformChanged = true;

        SetIsGlobalTranslationOutdated();
        SetIsGlobalScaleOutdated();
    }

    void Transform::AddScale(const glm::vec2 &scale)
    {
        this->scale += scale;
        hasTransformChanged = true;

        SetIsGlobalTranslationOutdated();
        SetIsGlobalScaleOutdated();
    }

    const glm::mat2x3 &Transform::GetMatrix()
    {
        if(hasTransformChanged)
        {
            glm::mat2 scale = glm::scale(glm::mat3(1.0f), glm::vec2(this->scale));
            glm::mat2 translation = glm::translate(glm::mat3(1.0f), this->translation);

            matrix = translation * scale;
            hasTransformChanged = false;
        }

        return matrix;
    }

    /**
     * Creates (and overwrites the old) parent-child relationship of this transform. Only use this method on components created by the ECS-System.
     * @param parent
     */
    void Transform::SetParent(Transform *parent)
    {
        //Remove old parent-child relationship
        if(this->parent != nullptr)
            this->parent->children.remove(this);

        //Create new parent-child relationship
        this->parent = parent;
        if(parent != nullptr)
            parent->children.push_back(this);

        SetIsGlobalTranslationOutdated();
    }

    Transform *Transform::GetParent()
    {
        return parent;
    }

    Transform* Transform::GetChild(int index)
    {
        auto child = children.begin();
        std::advance(child, index);
        return *child;
    }

    std::list<Transform*> &Transform::GetChildren()
    {
        return children;
    }

    std::string Transform::MatrixToString()
    {
        const glm::mat3x3 &matrix = GetMatrix();
        std::string result = std::to_string(matrix[0][0]) + ",\t ";
        result += std::to_string(matrix[1][0]) + ",\t ";
        result += std::to_string(matrix[2][0]) + ",\t\n";

        result += std::to_string(matrix[0][1]) + ",\t ";
        result += std::to_string(matrix[1][1]) + ",\t ";
        result += std::to_string(matrix[2][1]) + ",\t\n";

        result += std::to_string(matrix[0][2]) + ",\t ";
        result += std::to_string(matrix[1][2]) + ",\t ";
        result += std::to_string(matrix[2][2]) + ",\t\n";

        return result;
    }

    glm::vec2 Transform::GetGlobalTranslation()
    {
        if(isGlobalTranslationOutdated)
        {
            if(parent == nullptr)
            {
                globalTranslation = translation;
            }
            else
            {
                glm::mat3 parent = this->parent->GetGlobalMatrix();
                globalTranslation = parent * glm::vec3(translation, 1);
            }
            isGlobalTranslationOutdated = false;
        }

        return globalTranslation;
    }


    glm::vec2 Transform::GetGlobalScale()
    {
        UpdateScales();

        return globalScale;
    }

    const glm::mat2x3 &Transform::GetGlobalMatrix()
    {
        if(isGlobalMatrixOutdated)
        {
            glm::mat3 scale = glm::scale(glm::mat3(1.0f), glm::vec2(GetGlobalScale()));
            glm::mat3 translation = glm::translate(glm::mat3(1.0f), GetGlobalTranslation());
            globalMatrix = translation * scale;

            isGlobalMatrixOutdated = false;
        }

        return globalMatrix;
    }

    void Transform::SetIsGlobalTranslationOutdated()
    {
        isGlobalTranslationOutdated = true;
        isGlobalMatrixOutdated = true;
        for(Transform* child : children)
        {
            child->SetIsGlobalTranslationOutdated();
        }
    }

    void Transform::SetIsGlobalScaleOutdated()
    {
        isGlobalScaleOutdated = true;
        isGlobalMatrixOutdated = true;
        for(Transform* child : children)
        {
            child->SetIsGlobalScaleOutdated();
        }
    }

    void Transform::SetSpriteVariables(glm::vec2 scale)
    {
        if(::fabs(scale.x) >= 1)
            spriteScale.x = scale.x;
        else
            spriteScale.x = ::roundf(-(1 / scale.x));
        spriteFlip.x = scale.x < 0;

        if(::fabs(scale.y) >= 1)
            spriteScale.y = scale.y;
        else
            spriteScale.y = ::roundf(-(1 / scale.y));
        spriteFlip.y = scale.y < 0;
    }

    void Transform::UpdateScales()
    {
        if(isGlobalScaleOutdated)
        {
            if(parent == nullptr)
            {
                globalScale = scale;
                SetSpriteVariables(scale);
            }
            else
            {
                glm::vec2 parent = this->parent->GetGlobalScale();
                globalScale = glm::vec2(scale.x * parent.x, scale.y * parent.y);
                SetSpriteVariables(globalScale);
            }
            isGlobalScaleOutdated = false;
        }
    }

    std::string Transform::ToString()
    {
        std::string message{"LOCAL\n"};
        message += "\tPosition: (";
        message += std::to_string(translation.x);
        message += ", ";
        message += std::to_string(translation.y);
        message += ")\n";

        message += "\tScale: (";
        message += std::to_string(scale.x);
        message += ", ";
        message += std::to_string(scale.y);
        message += ")\n";

        glm::vec2 globalTranslation = GetGlobalTranslation();
        message += "\nGLOBAL\n";
        message += "\tPosition: (";
        message += std::to_string(globalTranslation.x);
        message += ", ";
        message += std::to_string(globalTranslation.y);
        message += ")\n";

        glm::vec2 globalScale = GetGlobalScale();
        message += "\tScale: (";
        message += std::to_string(globalScale.x);
        message += ", ";
        message += std::to_string(globalScale.y);
        message += ")\n";

        return message;
    }

    std::string Transform::GlobalTranslationToString()
    {
        glm::vec2 pos = GetGlobalTranslation();
        return "(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")";
    }

    Transform &Transform::operator=(Transform &&other)
    {
        if(this == &other) return *this;

        hasTransformChanged = other.hasTransformChanged;
        matrix = other.matrix;
        translation = other.translation;
        scale = other.scale;

        isGlobalTranslationOutdated = other.isGlobalTranslationOutdated;
        isGlobalScaleOutdated = other.isGlobalScaleOutdated;
        isGlobalMatrixOutdated = other.isGlobalMatrixOutdated;
        globalMatrix = other.globalMatrix;
        globalTranslation = other.globalTranslation;
        globalScale = other.globalScale;

        children.clear();
        std::copy(other.children.begin(), other.children.end(), std::back_inserter(children));
        other.children.clear();
        for(Transform* child : children)
        {
            child->parent = this;
        }

        parent = other.parent;
        if(parent != nullptr)
        {
            //Find child index of old transform (other)
            auto iter = parent->children.begin();
            int index = 0;
            Transform* pointer = &other;
            while(*iter != &other)
            {
                iter++;
                index++;
            }
            parent->children.remove(&other);

            //Set child index of new transform (this)
            iter = parent->children.begin();
            std::advance(iter, index);
            parent->children.insert(iter,this);
        }
        return *this;
    }
} // Engine