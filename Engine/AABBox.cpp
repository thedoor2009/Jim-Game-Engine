#include "AABBox.h"
#include "Timer.h"
#include <math.h>

namespace JimEngine
{
	AABBox::AABBox()
	{
		m_target = NULL;
		Coordination angle( 0.0f, 0.0f, 1.0f );
		m_angle = angle;
		
		Coordination center( 0.0f, 0.0f, 0.0f );
		m_center = center;

		m_width = 1.0f;
		m_height = 1.0f;
		m_thick = 1.0f;
	}

	AABBox::AABBox( Sprite *i_target )
	{
		m_target = i_target;

		m_rotation = i_target->Get_Rotation();
		m_translate = i_target->Get_Translate();

		Coordination angle( 0.0f, 0.0f, 1.0f );
		m_angle = angle;

		m_center = m_target->Get_Position();
		
		m_width  = m_target->Get_Bounce_Width() / 2;
		m_height = m_target->Get_Bounce_Height() / 2;
		m_thick  = m_target->Get_Bounce_Thick() / 2;
	}

	Sprite * AABBox::Get_Sprite( void )
	{
		return m_target;
	}
}