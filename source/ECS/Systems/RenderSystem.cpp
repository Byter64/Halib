#include "Engine.h"
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <stdexcept>

namespace Engine
{
    RenderSystem::RenderSystem()
    {
        Hall::Init();

        camera.SetTranslation(glm::vec3(0));
        camera.SetScale(glm::vec3(1));
        camera.SetRotation(glm::identity<glm::quat>());
    }

    void RenderSystem::Render()
    {
        if(backgroundColor != Engine::Color::TRANSPARENT)
            Clear(backgroundColor);

        for(Entity entity : entities)
        {
            SpriteRenderer& spriteRenderer = ecsSystem->GetComponent<SpriteRenderer>(entity);
            Render(entity);
        }
    }

    void RenderSystem::Render(Entity entity)
    {
        Transform& transform = ecsSystem->GetComponent<Transform>(entity);
        MeshRenderer& meshRenderer = ecsSystem->GetComponent<MeshRenderer>(entity);

        for(int i = 0; i < meshRenderer.mesh->primitives.size(); i++)
        {
            const tinygltf::Primitive &primitive = meshRenderer.mesh->primitives[i];
            MeshRenderer::PrimitiveData &data = meshRenderer.primitiveData[i];
            const Material &material = data.material;

            //I doubt that updating the shader should be handled here. But I don't know any better place right now
            //hello World!!
            if(data.shader.id == 0)
            {
                CreateShaderProgram(data.shader);
            }
            else if(data.shader.hasChanged)
            {
                const auto& bla = std::find(loadedShaders.begin(), loadedShaders.end(), data.shader);
                if(bla != loadedShaders.end())
                {
                    data.shader.id = bla->id;
                }
                else
                {
                    CreateShaderProgram(data.shader);
                }
            }

            GLuint newShader = data.shader.id;
            if(newShader != activeShader)
            {
                glUseProgram(newShader);
                activeShader = newShader;
            }

            GLint projectionViewMatrixLocation = glGetUniformLocation(newShader, "projectionView");
            glm::mat4x4 projectionViewMatrix = projectionMatrix * camera.GetMatrix();
            glUniformMatrix4fv(projectionViewMatrixLocation, 1, false, &projectionViewMatrix[0][0]);

            GLint orthographicMatrixLocation = glGetUniformLocation(newShader, "orthographic");
            glUniformMatrix4fv(orthographicMatrixLocation, 1, false, &this->orthographicMatrix[0][0]);

            GLint modelMatrixLocation = glGetUniformLocation(activeShader, "model");
            glUniformMatrix4fv(modelMatrixLocation, 1, false, &transform.GetGlobalMatrix()[0][0]);

            //█████████████████████████████████████████████████████████████████████████████████████
            //██████████Setting Material data for Rendering████████████████████████████████████████
            //█████████████████████████████████████████████████████████████████████████████████████

            //BaseColor
            GLint baseColorFactorLocation = glGetUniformLocation(activeShader, "baseColorFactor");

            glUniform4fv(baseColorFactorLocation, 1, &material.baseColorFactor.x);
            if (material.baseColorID > 0)
            {
                glActiveTexture(GL_TEXTURE0);
                GLint test = glGetUniformLocation(activeShader, "baseColor");
                glUniform1i(test, 0);
                glBindTexture(GL_TEXTURE_2D, material.baseColorID);
            }

            //MetallicRoughness
            GLint metallicFactorLocation = glGetUniformLocation(activeShader, "metallicFactor");
            glUniform1fv(metallicFactorLocation, 1, &material.metallicFactor);

            GLint roughnessFactorLocation = glGetUniformLocation(activeShader, "roughnessFactor");
            glUniform1fv(roughnessFactorLocation, 1, &material.roughnessFactor);
            if(material.metallicRoughnessID > 0)
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, material.metallicRoughnessID);
            }

            //Normal
            GLint normalScaleLocation = glGetUniformLocation(activeShader, "normalScale");
            glUniform1fv(normalScaleLocation, 1, &material.normalScale);
            if(material.normalID > 0)
            {
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, material.normalID);
            }

            //Occlusion
            GLint occlusionStrengthLocation = glGetUniformLocation(activeShader, "occlusionStrength");
            glUniform1fv(occlusionStrengthLocation, 1, &material.occlusionStrength);
            if(material.occlusionID > 0)
            {
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, material.occlusionID);
            }

            //Emissive
            GLint emissiveFactorLocation = glGetUniformLocation(activeShader, "emissiveFactor");
            glUniform3fv(emissiveFactorLocation, 1, &material.emissiveFactor.x);
            if(material.emissiveID > 0)
            {
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, material.emissiveID);
            }

            glBindVertexArray(data.vaoID);
            if(data.material.isDoubleSided)
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);

            if(data.indexBufferID > 0)
            {
                const tinygltf::Accessor& indices = meshRenderer.model->accessors[primitive.indices];
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.indexBufferID);
                glDrawElements(primitive.mode, indices.count, indices.componentType, (void *) indices.byteOffset);
            }
            else
            {
                glDrawArrays(primitive.mode, 0, data.vertexCount);
            }
        }
    }


    void RenderSystetm::Clear(Color color)
    {
    	WaitForGPU();

    	//This is ugly but I want to hide color.color. I hope the compiler optimises this away
    	Hall::Color* hallColor = (Hall::Color*)(&color);

    	Hall::SetScale(1, 1);
    	Hall::SetFlip(false, false);
    	Hall::SetColor(*hallColor);
    	Hall::SetColorTable(Hall::NONE);
    	Hall::SetColorSource(Hall::COLOR);
    	Hall::SetShape(Hall::RECTANGLE);
    	Hall::SetRectangle(0, 0, Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);

    	Hall::Draw();
    }

    void RenderSystem::WaitForGPU()
    {
        while(Hall::GetIsGPUBusy());
    }

    void RenderSystem::EntityAdded(Entity entity)
    {

    }

    void RenderSystem::EntityRemoved(Entity entity)
    {

    }

} // Engine