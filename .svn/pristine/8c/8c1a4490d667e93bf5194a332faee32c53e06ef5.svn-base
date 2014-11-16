#ifndef _TRIGGER_BOX_H
#define _TRIGGER_BOX_H

#include "Matrix.h"
#include "Spirte.h"
#include "Coordination.h"

namespace JimEngine
{
	class TriggerBox
	{
	public:
		TriggerBox();
		TriggerBox( Sprite * i_target );

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