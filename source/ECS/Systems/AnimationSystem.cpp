#include "ECS/Systems/AnimationSystem.h"
#include "Engine.h"

namespace Engine
{
    void AnimationSystem::EntityAdded(Entity entity)
    {

    }

    void AnimationSystem::EntityRemoved(Entity entity)
    {

    }

    void AnimationSystem::Update(float deltaTime)
    {
        for(Entity entity : entities)
        {
            Animator &animator = ecsSystem->GetComponent<Animator>(entity);
            Animation &animation = ecsSystem->GetComponent<Animation>(entity);
            SpriteRenderer &spriteRenderer = ecsSystem->GetComponent<SpriteRenderer>(entity);

            if(!animator.isPlaying) return;

	        animator.timer += deltaTime * animator.framesPerSecond;
	        while(animator.timer >= 1)
	        {
	        	animator.timer -= 1;
	        	animator.animationCounter++;
	        	if(animator.animationCounter >= animation.animationFrameCount)
	        	{
	        		animator.animationCounter = 0;
	        		animator.frameIndex = animation.animationStartIndex;
	        	}
	        	else
	        	{
	        		switch (animation.animationDirection)
	        		{
	        			case Animation::UP		: animator.frameIndex.y--; break;
	        			case Animation::DOWN	: animator.frameIndex.y++; break;
	        			case Animation::LEFT	: animator.frameIndex.x--; break;
	        			case Animation::RIGHT	: animator.frameIndex.x++; break;
	        		}
	        	}
                spriteRenderer.offset = animator.frameIndex * spriteRenderer.size;
	        }
        }
    }
} // Engine