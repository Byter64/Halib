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
        camera.SetTranslation(glm::vec3(0));
        camera.SetScale(glm::vec3(1));
    }

    void RenderSystem::Render()
    {
        if(backgroundColor != Engine::Color::TRANSPARENT)
        Clear(backgroundColor);
        
        WaitForGPU();
        Hall::SetColorTable(Hall::NONE);
        Hall::SetColorSource(Hall::MEMORY);
        Hall::SetShape(Hall::RECTANGLE);

        for(Entity entity : sortedEntities)
        {
            SpriteRenderer& spriteRenderer = ecsSystem->GetComponent<SpriteRenderer>(entity);
            Render(entity);
        }
    }

    void RenderSystem::Render(Entity entity)
    {
        Transform& transform = ecsSystem->GetComponent<Transform>(entity);
        SpriteRenderer& spriteRenderer = ecsSystem->GetComponent<SpriteRenderer>(entity);
        glm::vec2 position = transform.GetGlobalTranslation();
        glm::ivec2 scale = transform.GetSpriteScale();
        glm::bvec2 flip = transform.GetSpriteFlip();

        auto& image = spriteRenderer.image;
	    if(image == nullptr) return;
	    glm::ivec2 frameOffset = spriteRenderer.offset;
	    glm::ivec2 frameSize = spriteRenderer.size;
	    WaitForGPU();

#ifdef DESKTOP
	    if(image->GetWasDataRequested())
	    {
	    	Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->GetWidth(), image->GetHeight());
	    }
#endif

	    Hall::SetImage((Hall::Color*)image->GetData(), image->GetWidth(), image->GetHeight());
	    Hall::SetExcerpt(frameOffset.x, frameOffset.y, frameSize.x, frameSize.y);
	    Hall::SetScale(scale.x, scale.y);
	    Hall::SetFlip(flip.x, flip.y);
	    Hall::SetScreenPosition(position.x, position.y);

	    Hall::Draw();
    }


    void RenderSystem::Clear(Color color)
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

    void RenderSystem::ResortEntity(Entity entity)
    {
        //This could be made a bit more efficient
        EntityRemoved(entity);
        EntityAdded(entity);
    }

    void RenderSystem::EntityAdded(Entity entity)
    {
        auto iter = std::upper_bound(sortedEntities.begin(), sortedEntities.end(), entity,
        [](Entity entity, Entity other)
    {
        SpriteRenderer& sr1 = ecsSystem->GetComponent<SpriteRenderer>(entity);
        SpriteRenderer& sr2 = ecsSystem->GetComponent<SpriteRenderer>(other);

        return sr1.GetLayer() < sr2.GetLayer();
    });
        sortedEntities.insert(iter, entity);
        ecsSystem->GetComponent<RenderHelper>(entity).DetermineType();
    }
    
    void RenderSystem::EntityRemoved(Entity entity)
    {
        auto iter = sortedEntities.begin();
        while(iter != sortedEntities.end() && *iter != entity)
            iter++;
        
        while((iter + 1) != sortedEntities.end())
            *iter = *(iter + 1);

        sortedEntities.resize(sortedEntities.size() - 1);
    }

} // Engine