#ifndef _VECTOR4_H
#define _VECTOR4_H
#include "Coordination.h"

namespace JimEngine
{
	class Vector4
	{
		public:
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		inline Vector4( void )
		{
			m_x = 0.0f;
			m_y = 0.0f;
			m_z = 0.0f;
			m_w = 1.0f;
		}
		
		inline Vector4( float i_x, float i_y, float i_z, float i_w = 1.0f)
		{
			m_x = i_x;
			m_y = i_y;
			m_z = i_z;
			m_w = i_w;
		}

		Vector4( const JimEngine::Coordination & i_other, float i_w = 1.0f )
		{
			m_x = i_other.Cor_GetX();
			m_y = i_other.Cor_GetY();
			m_z = i_other.Cor_GetZ();
			m_w = i_w;
		}

		void operator = ( const Vector4 & i_other )
		{
			m_x = i_other.Get_ValueX();
			m_y = i_other.Get_ValueY();
			m_z = i_other.Get_ValueZ();
			m_w = i_other.Get_ValueW();
		}

		void Set_Value( unsigned int i, float i_value)
		{
			switch( i)
			{
			case 0:
				{
					m_x = i_value;
					break;
				}
			case 1:
				{
					m_y = i_value;
					break;
				}
			case 2:
				{
					m_z = i_value;
					break;
				}
			case 3:
				{
					m_w = i_value;
					break;
				}
			}
		}

		const float Get_ValueX( void ) const
		{
			return m_x;
		}

		const float Get_ValueY( void ) const 
		{
			return m_y;
		}

		const float Get_ValueZ( void ) const 
		{
			return m_z;
		}

		const float Get_ValueW( void ) const 
		{
			return m_w;
		}
	};
}
#endif