#include "TriggerBox.h"
#include "Timer.h"
#include <math.h>

namespace JimEngine
{
	TriggerBox::TriggerBox()
	{
		m_target = NULL;
		Coordination angle( 0.0f, 0.0f, 1.0f );
		m_angle = angle;

		Coordination center( 0.0f, 0.0f, 0.0f );
		m_center = center;

		m_width = 25.0f;
		m_height = 25.0f;
		m_thick = 25.0f;
	}

	TriggerBox::TriggerBox( Sprite *i_target )
	{
		m_target = i_target;

		m_rotation = i_target->Get_Rotation();
		m_translate = i_target->Get_Translate();

		Coordination angle( 0.0f, 0.0f, 1.0f );
		m_angle = angle;

		m_center = m_target->Get_Position();
		
		m_width = 25.0f;
		m_height = 25.0f;
		m_thick = 25.0f;
	}

	Sprite * TriggerBox::Get_Sprite( void )
	{
		return m_target;
	}
}