#include "Animation.h"
#include "TimeManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Animation::Animation()
{

	//set sprite to dynamic by default 
	m_spriteType = DYNAMIC;

	//set other default values
	m_isAnimationDead = false;
	m_isAnimationLoopFinal = false;
	m_isAnimationLooping = true;
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
//function that creates and draws the actual animation on screen
//------------------------------------------------------------------------------------------------------
void Animation::Draw()
{

	//store the total time elapsed since animation began which will be used in formula below
	m_timeElapsed += TheTime::Instance()->GetElapsedTimeSeconds();

	//aquire index value of specific texture cell to "cut out" using a formula
	m_textureIndex = (GLint)(m_timeElapsed * m_animationVelocity) %
		             (m_textureDimension.X * m_textureDimension.Y);

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
		     m_textureIndex == (m_textureDimension.X * m_textureDimension.Y - 1))
	{
		m_isAnimationLoopFinal = true;
	}

	//if this is the final animation, flag to kill entire animation
	//because even though the animation is marked final, a few more 
	//frames will be called with the last texture cell set, so only
	//mark it dead when the first texture cell comes around again
	if (m_isAnimationLoopFinal && m_textureIndex == 0)
	{
		m_isAnimationDead = true;
	}

	//if animation is set to run, then render 
	//the sprite using the base class functions
	if (!m_isAnimationDead)
	{

		//clear all buffer data from vectors
		ClearBufferData();

		//create the vertex, texture and color buffer data
		CreateVertices();
		CreateTexCoords();
		CreateColors();

		//fill the VBOs with the buffer data
		FillBuffers();

		//create and draw the sprite
		CreateSprite();

	}

}