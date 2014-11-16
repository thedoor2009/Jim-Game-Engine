#ifndef _AABBOX_H
#define _AABBOX_H

#include "Matrix.h"
#include "Spirte.h"
#include "Coordination.h"

namespace JimEngine
{
	class AABBox
	{
	public:
		AABBox();
		AABBox( Sprite * i_target );

		bool Collision(   AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA,  AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RatationB );
		bool SwapCollision( AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA,  AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RatationB );
		bool AABBCollision( AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA,  AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RatationB );
		Sprite * Get_Sprite( void );
		
		Sprite *m_target;
		Coordination m_angle;

		Matrix4x4 m_rotation;
		Matrix4x4 m_translate;
		
		Coordination m_center;
		float m_width;
		float m_height;
		float m_thick;
	};
}
#endif