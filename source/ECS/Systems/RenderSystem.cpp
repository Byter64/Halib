#include "Engine.h"
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <stdexcept>
#include <Hall/Hall.h>
#include "ECS/Helpers/GlyphCache.h"

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
            Render(entity);
        }
    }

    void RenderSystem::Render(Entity entity)
    {
        Renderer& helper = ecsSystem->GetComponent<Renderer>(entity);
        switch (helper.type)
        {
        case Renderer::SPRITE:
            RenderSprite(entity);
            break;
        case Renderer::TEXT:
            RenderText(entity);
            break;
        case Renderer::RECTANGLE:
            RenderRectangle(entity);
        default:
            break;
        }
    }

    void RenderSystem::RenderSprite(Entity entity)
    {
        Transform& transform = ecsSystem->GetComponent<Transform>(entity);
        Sprite& spriteRenderer = ecsSystem->GetComponent<Sprite>(entity);
        glm::ivec2 scale = transform.GetSpriteScale();
        glm::bvec2 flip = transform.GetSpriteFlip();
        glm::vec2 position = transform.GetGlobalTranslation();
        position -= spriteRenderer.size / 2;

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
        Hall::SetColorTable(Hall::CTType::NONE);
        Hall::SetColorSource(Hall::MEMORY);
	    Hall::SetImage((Hall::Color*)image->GetData(), image->GetWidth(), image->GetHeight());
	    Hall::SetExcerpt(frameOffset.x, frameOffset.y, frameSize.x, frameSize.y);
	    Hall::SetScale(scale.x, scale.y);
	    Hall::SetFlip(flip.x, flip.y);
	    Hall::SetScreenPosition(position.x, position.y);

	    Hall::Draw();
    }

    void RenderSystem::RenderRectangle(Entity entity)
    {
        Rectangle& renderer = ecsSystem->GetComponent<Rectangle>(entity);
        Transform& transform = ecsSystem->GetComponent<Transform>(entity);
        glm::ivec2 position = transform.GetGlobalTranslation();
        position -= renderer.size / 2;
        glm::ivec2 size = renderer.size;

    	Hall::SetScale(1, 1);
    	Hall::SetFlip(false, false);
    	Hall::SetColor(renderer.color.GetHallColor());
    	Hall::SetColorTable(Hall::NONE);
    	Hall::SetColorSource(Hall::COLOR);
    	Hall::SetRectangle(position.x, position.y, size.x, size.y);

    	Hall::Draw();
    }

    void RenderSystem::RenderText(Entity entity)
    {
        Text& renderer = ecsSystem->GetComponent<Text>(entity);
        Transform& transform = ecsSystem->GetComponent<Transform>(entity);
        glm::ivec2 position = transform.GetGlobalTranslation();
        position -= renderer.size / 2;

        Hall::COLOR_TABLE_MEMORY[0] = 0;
	    Hall::COLOR_TABLE_MEMORY[1] = renderer.color.GetHallColor();
	    FT_Face face = renderer.font->GetFace();
	    for(char c : renderer.text)
	    {
	    	unsigned int glyphIndex = FT_Get_Char_Index(face, c);
	    	GlyphID glyphID{ face, glyphIndex, renderer.font->GetSize() };
	    	FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
	    	if (!glyphCache.count(glyphID))
	    	{
	    		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);

	    		CacheEntry cacheEntry;

	    		cacheEntry.indexContainers = GlyphToIndexContainer(face->glyph->bitmap);
	    		cacheEntry.width = face->glyph->bitmap.width;
	    		cacheEntry.height = face->glyph->bitmap.rows;
	    		cacheEntry.offsetLeft = face->glyph->bitmap_left;
	    		cacheEntry.offsetTop = face->glyph->bitmap_top;
	    		glyphCache[glyphID] = cacheEntry;
	    	}

	    	CacheEntry cacheEntry = glyphCache[glyphID];
	    	Hall::SetColorTable(Hall::BIT_1, 0);
	    	Hall::SetColorSource(Hall::MEMORY);
	    	Hall::SetImage(cacheEntry.indexContainers.get(), cacheEntry.width, cacheEntry.height);
	    	Hall::SetExcerpt(0, 0, cacheEntry.width, cacheEntry.height);
	    	Hall::SetScreenPosition(position.x - cacheEntry.offsetLeft, position.y - cacheEntry.offsetTop);
	    	Hall::SetScale(1, 1);
	    	Hall::SetFlip(false, false);
	    	Hall::Draw();

	    	position.x += face->glyph->advance.x / 64;
	    	position.y += face->glyph->advance.y / 64;
	    }
    }

    void RenderSystem::Clear(Color color)
    {
    	WaitForGPU();

    	Hall::SetScale(1, 1);
    	Hall::SetFlip(false, false);
    	Hall::SetColor(color.GetHallColor());
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
        Renderer& sr1 = ecsSystem->GetComponent<Renderer>(entity);
        Renderer& sr2 = ecsSystem->GetComponent<Renderer>(other);

        return sr1.GetLayer() < sr2.GetLayer();
    });
        sortedEntities.insert(iter, entity);
        ecsSystem->GetComponent<Renderer>(entity).DetermineType();
    }
    
    void RenderSystem::EntityRemoved(Entity entity)
    {
        auto iter = sortedEntities.begin();
        while(iter != sortedEntities.end() && *iter != entity)
            iter++;
        
        while ((iter + 1) != sortedEntities.end())
        {
            *iter = *(iter + 1);
            iter++; 
        }

        sortedEntities.resize(sortedEntities.size() - 1);
    }

} // Engine