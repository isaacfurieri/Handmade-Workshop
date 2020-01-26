#include "Game.h"
#include "Animation.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Animation::Animation()
{

	m_spriteType = DYNAMIC;

	m_isAnimationDead = false;
	m_isAnimationLoopFinal = false;
	m_isAnimationLooping = true;

	m_timeElapsed = 0.0;
	m_animationVelocity = 0.0f;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag variable stating if animation is dead 
//------------------------------------------------------------------------------------------------------
bool Animation::IsAnimationDead()
{

	return m_isAnimationDead;

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
//function that determines which image "cel" in sprite sheet to cut out
//------------------------------------------------------------------------------------------------------
void Animation::Update()
{

	//store the total time elapsed since animation began which will be used in formula below
	m_timeElapsed += 0.016; // Game::Instance()->GetElapsedTime() / 1000.0f;

	//aquire index value of specific texture cell to "cut out" using a formula
	//the texture index is zero based and is a whole number value counting from
	//top left and going right and down the spritesheet, and is capable of "wrapping"
	GLuint textureIndex = (GLint)(m_timeElapsed * m_animationVelocity) %
		                  (GLint)(m_textureDimension.x * m_textureDimension.y);

	//use modulo and divide with the texture index to get exact column/row 
	//index to "cut out", because with animations, the texture cell is dynamic
	m_textureCell.x = (GLfloat)(textureIndex % (GLint)m_textureDimension.x);
	m_textureCell.y = (GLfloat)(textureIndex / (GLint)m_textureDimension.x);

	//if animation is set to cycle endlessly then set the kill and final flags
	//to false so that no other final checks are made and that the animation loops
	if (m_isAnimationLooping)
	{
		m_isAnimationDead = false;
		m_isAnimationLoopFinal = false;
	}

	//otherwise if animation is set to cycle once and the last texture
	//cell has been reached then flag this as the final animation loop
	else if (!m_isAnimationLooping && 
		     textureIndex == (m_textureDimension.x * m_textureDimension.y - 1))
	{
		m_isAnimationLoopFinal = true;
	}

	//if this is the final animation, flag to kill entire animation
	//because even though the animation is marked final, a few more 
	//frames will be called with the last texture cell set, so only
	//mark it dead when the first texture cell comes around again
	if (m_isAnimationLoopFinal && textureIndex == 0)
	{
		m_isAnimationDead = true;
	}

	//if animation is set to run, then render 
	//the sprite using the base class function
	if (!m_isAnimationDead)
	{
		Sprite::Update();
	}

}