#include "Animation.h"
#include "TimeManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
Animation::Animation()
{

	//set sprite to dynamic by default 
	//as the textures will change constantly
	m_spriteType = DYNAMIC;

	//set other default values
	m_killAnimation = false;
	m_finalAnimationLoop = false;
	m_isAnimationLooping = true;
	m_animationVelocity = 0.0f;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns looping flag variable reference
//------------------------------------------------------------------------------------------------------
bool& Animation::IsAnimationLooping()
{

	return m_isAnimationLooping;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns speed of animation
//------------------------------------------------------------------------------------------------------
void Animation::SetAnimationVelocity(GLfloat velocity)
{

	m_animationVelocity = velocity;

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual animation on screen
//------------------------------------------------------------------------------------------------------
void Animation::Draw()
{

	//store the total time elapsed since timer began which will be used in formula below
	GLdouble timeElapsed = TheTime::Instance()->GetTotalTimeSeconds();

	//aquire index value of specific texture cell to "cut out" using a formula
	m_textureIndex = (GLint)(timeElapsed * m_animationVelocity) % 
		             (m_textureDimension.X * m_textureDimension.Y);

	//if animation is set to cycle endlessly then set the kill and final flags to false
	//this will ensure that no other final checks are made and that the animation draws normally
	//this also ensures that if a sprite is reset to loop animation then the flags are reset
	if (m_isAnimationLooping)
	{
		m_killAnimation = false;
		m_finalAnimationLoop = false;
	}

	//otherwise if animation is only set to cycle once and we have 
	//reached the last texture cell then flag this as the final animation loop
	else if (!m_isAnimationLooping && 
		     m_textureIndex == (m_textureDimension.X * m_textureDimension.Y - 1))
	{
		m_finalAnimationLoop = true;
	}

	//if this is the final animation, flag to kill entire animation and reset the clock
	//we do this because even though the animation is marked final, a few more frames will be called 
	//with the last texture cell set, so only kill it when the first texture cell comes around again
	if (m_finalAnimationLoop && m_textureIndex == 0)
	{
		m_killAnimation = true;
	}

	//if animation is still set to run, then do all the 
	//normal sprite rendering using the base class functions
	if (!m_killAnimation)
	{
		CreateVertices();
		CreateTexCoords();
		CreateColors();
		CreateSprite();
	}

}