#ifndef _MATRIX_H
#define _MATRIX_H
#include "Vector4.h"

namespace JimEngine
{
	class Matrix4x4
	{
		//Matrix4x4 Rotation;
		//Matrix4x4 Translation;

		float m_Value[4][4];
		float zRotation;

	public:
	
		Matrix4x4(void);
		Matrix4x4( const Matrix4x4 & i_other );
		Matrix4x4( float m_11, float m_12, float m_13, float m_14,
						  float m_21, float m_22, float m_23, float m_24,
						  float m_31, float m_32, float m_33, float m_34,
						  float m_41, float m_42, float m_43, float m_44);

		Matrix4x4 & operator = ( const Matrix4x4 & i_other );

		void Identity( void );
		void Inverse( void );
		void Transpose( void );

		Matrix4x4 Get_Identity( void );
		Matrix4x4 Get_Inverse( void );
		Matrix4x4 Get_Transpose( void );

		float Determinant( void );

		Matrix4x4 & RotateX ( float i_rotation );
		Matrix4x4 & RotateY ( float i_rotation );
		Matrix4x4 & RotateZ ( float i_rotation );

		Matrix4x4 & Translate( float i_x, float i_y, float i_z );
		Matrix4x4 & Translate( const JimEngine::Coordination & i_Translate );

		void Multiply( const Matrix4x4 & i_other );
		Matrix4x4 Multiply( const Matrix4x4 & i_matrix , const Matrix4x4 & i_other );

		Vector4 Left_Multiply( const Coordination & i_vector3 );
		Vector4 Left_Multiply( const Vector4 & i_vector4 );
		Vector4 Left_Multiply( const Vector4 & i_vector4, const Matrix4x4 & i_matrix );

		void Set_Value( unsigned int i_row, unsigned int i_column, float i_value );
		const float Get_Value( unsigned int i_row, unsigned int i_column ) const;

		void Unit_Test( void );
	};

	inline Matrix4x4 operator * ( const Matrix4x4 & i_o, const Matrix4x4 & i_other)
	{
		Matrix4x4 temp;
		unsigned int column = 0;
		for( unsigned int i = 0; i < 4; i++ )
		{
			float a = 0.0f;
			for( unsigned int j = 0; j < 4; j++ )
			{
				a = 0.0f;
				a += i_o.Get_Value(i, 0) * i_other.Get_Value(0, j );
				a += i_o.Get_Value(i, 1) * i_other.Get_Value(1, j );
				a += i_o.Get_Value(i, 2) * i_other.Get_Value(2, j );
				a += i_o.Get_Value(i, 3) * i_other.Get_Value(3, j );
				temp.Set_Value( i, column, a ); 
				column++;
			}
			column = 0;
		}
		return temp;
	}

	inline Vector4 operator * ( const Vector4 & i_o, const Matrix4x4 & i_other)
	{
		Matrix4x4 temp;
		return temp.Left_Multiply(i_o, i_other );
	}
}
#endif