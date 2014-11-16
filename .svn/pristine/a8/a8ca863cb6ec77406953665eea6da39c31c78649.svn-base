#include "Matrix.h"
#include <assert.h>
#include <math.h>

namespace JimEngine
{
	#define PI 3.14159265359

	Matrix4x4::Matrix4x4( void )
	{
		zRotation = 180.0f;

		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] =0.0f; 
			}
		}
	}

	Matrix4x4::Matrix4x4( const Matrix4x4 & i_other )
	{
		zRotation = 180.0f;
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = i_other.m_Value[i][j]; 
			}
		}
	}

	Matrix4x4::Matrix4x4( float m_11, float m_12, float m_13, float m_14,
						  float m_21, float m_22, float m_23, float m_24,
						  float m_31, float m_32, float m_33, float m_34,
						  float m_41, float m_42, float m_43, float m_44)
	{
		m_Value[0][0] = m_11;
		m_Value[0][1] = m_12;
		m_Value[0][2] = m_13;
		m_Value[0][3] = m_14;
			
		m_Value[1][0] = m_21;
		m_Value[1][1] = m_22;
		m_Value[1][2] = m_23;
		m_Value[1][3] = m_24;
			
		m_Value[2][0] = m_31;
		m_Value[2][1] = m_32;
		m_Value[2][2] = m_33;
		m_Value[2][3] = m_34;
			
		m_Value[3][0] = m_41;
		m_Value[3][1] = m_42;
		m_Value[3][2] = m_43;
		m_Value[3][3] = m_44;
	}
	
	Matrix4x4 & Matrix4x4::operator = ( const Matrix4x4 & i_other )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = i_other.m_Value[i][j]; 
			}
		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Matrix4x4::Set_Value( unsigned int i_row, unsigned int i_column, float i_value )
	{
		m_Value[i_row][i_column] = i_value;
	}

	const float Matrix4x4::Get_Value( unsigned int i_row, unsigned int i_column ) const
	{
		return m_Value[i_row][i_column];
	}

	/////////////////////////////////////////////////////////////////////////////////////

	//Get the Identity Matrix
	void Matrix4x4::Identity( void )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = 0.0f; 
			}
		}

		m_Value[0][0] = 1.0f;
		m_Value[1][1] = 1.0f;
		m_Value[2][2] = 1.0f;
		m_Value[3][3] = 1.0f;
	}

	Matrix4x4 Matrix4x4::Get_Identity( void )
	{
		return( Matrix4x4( 1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f ));
	}

	//Get the Transpose Matrix
	void Matrix4x4::Transpose( void )
	{
		Matrix4x4 temp = *this;
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				this->Set_Value( i, j, temp.Get_Value( j, i ) );
			}
		}
	}

	Matrix4x4 Matrix4x4::Get_Transpose( void )
	{
		return( Matrix4x4( m_Value[0][0], m_Value[1][0], m_Value[2][0], m_Value[3][0],
						   m_Value[0][1], m_Value[1][1], m_Value[2][1], m_Value[3][1],
						   m_Value[0][2], m_Value[1][2], m_Value[2][2], m_Value[3][2],
						   m_Value[0][3], m_Value[1][3], m_Value[2][3], m_Value[3][3] ));
	}

	//Get the Inverse Matrix
	void Matrix4x4::Inverse( void )
	{
		float t_determinant = this->Determinant();
		assert( t_determinant );
	
		float a11,a12,a13,a14,a21,a22,a23,a24,a31,a32,a33,a34,a41,a42,a43,a44;

		a11 = m_Value[0][0];a12 = m_Value[0][1];a13 = m_Value[0][2];a14 = m_Value[0][3];
		a21 = m_Value[1][0];a22 = m_Value[1][1];a23 = m_Value[1][2];a24 = m_Value[1][3]; 
		a31 = m_Value[2][0];a32 = m_Value[2][1];a33 = m_Value[2][2];a34 = m_Value[2][3]; 
		a41 = m_Value[3][0];a42 = m_Value[3][1];a43 = m_Value[3][2];a44 = m_Value[3][3]; 

		m_Value[0][0] = ( a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a42 * a33 * a24 - a43 * a34 * a22 - a44 * a23 * a32 );
		m_Value[1][0] = ( a21 * a33 * a44 + a23 * a34 * a41 + a24 * a31 * a43 - a41 * a33 * a24 - a43 * a34 * a21 - a44 * a23 * a31 ) * ( -1 );
		m_Value[2][0] = ( a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a24 * a32 * a41 - a34 * a42 * a21 - a44 * a22 * a31 ); 
		m_Value[3][0] = ( a21 * a32 * a43 + a22 * a33 * a41 + a23 * a31 * a42 - a23 * a32 * a41 - a33 * a42 * a21 - a43 * a22 * a31 ) * ( -1 );

		m_Value[0][1] = ( a12 * a33 * a44 + a13 * a34 * a42 + a14 * a32 * a43 - a14 * a33 * a42 - a34 * a43 * a12 - a44 * a13 * a32 ) * ( -1 );
		m_Value[1][1] = ( a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a14 * a33 * a41 - a34 * a43 * a11 - a44 * a13 * a31 );
		m_Value[2][1] = ( a11 * a32 * a44 + a12 * a34 * a41 + a14 * a31 * a42 - a14 * a32 * a41 - a34 * a42 * a11 - a44 * a12 * a31 ) * ( -1 );
		m_Value[3][1] = ( a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a13 * a32 * a41 - a33 * a42 * a11 - a43 * a12 * a31 );

		m_Value[0][2] = ( a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a14 * a23 * a42 - a24 * a43 * a12 - a44 * a13 * a22 );
		m_Value[1][2] = ( a11 * a23 * a44 + a13 * a24 * a41 + a14 * a21 * a43 - a14 * a23 * a41 - a24 * a43 * a11 - a44 * a21 * a13 ) * ( -1 );
		m_Value[2][2] = ( a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a14 * a22 * a41 - a24 * a42 * a11 - a44 * a12 * a21 ); 
		m_Value[3][2] = ( a11 * a22 * a43 + a12 * a23 * a41 + a13 * a21 * a42 - a13 * a22 * a41 - a23 * a42 * a11 - a43 * a12 * a21 ) * ( -1 );

		m_Value[0][3] = ( a12 * a23 * a34 + a13 * a24 * a32 + a14 * a22 * a33 - a14 * a23 * a32 - a24 * a33 * a12 - a34 * a13 * a22 ) * ( -1 );
		m_Value[1][3] = ( a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a14 * a23 * a31 - a24 * a33 * a11 - a34 * a13 * a21 );
		m_Value[2][3] = ( a11 * a22 * a34 + a12 * a24 * a31 + a14 * a21 * a32 - a14 * a22 * a31 - a24 * a32 * a11 - a34 * a12 * a21 ) * ( -1 );
		m_Value[3][3] = ( a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31 * a23 * a32 * a11 - a33 * a12 * a21 );

		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] /= t_determinant; 
			}
		}
	}

	Matrix4x4 Matrix4x4::Get_Inverse( void )
	{
		float t_determinant = this->Determinant();
		assert( t_determinant );
	
		float a11,a12,a13,a14,a21,a22,a23,a24,a31,a32,a33,a34,a41,a42,a43,a44;
		float reverse_determinant = 1.0f / t_determinant;

		a11 = m_Value[0][0];a12 = m_Value[0][1];a13 = m_Value[0][2];a14 = m_Value[0][3];
		a21 = m_Value[1][0];a22 = m_Value[1][1];a23 = m_Value[1][2];a24 = m_Value[1][3]; 
		a31 = m_Value[2][0];a32 = m_Value[2][1];a33 = m_Value[2][2];a34 = m_Value[2][3]; 
		a41 = m_Value[3][0];a42 = m_Value[3][1];a43 = m_Value[3][2];a44 = m_Value[3][3]; 

		m_Value[0][0] = ( a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a42 * a33 * a24 - a43 * a34 * a22 - a44 * a23 * a32 );
		m_Value[1][0] = ( a21 * a33 * a44 + a23 * a34 * a41 + a24 * a31 * a43 - a41 * a33 * a24 - a43 * a34 * a21 - a44 * a23 * a31 ) * ( -1 );
		m_Value[2][0] = ( a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a24 * a32 * a41 - a34 * a42 * a21 - a44 * a22 * a31 ); 
		m_Value[3][0] = ( a21 * a32 * a43 + a22 * a33 * a41 + a23 * a31 * a42 - a23 * a32 * a41 - a33 * a42 * a21 - a43 * a22 * a31 ) * ( -1 );

		m_Value[0][1] = ( a12 * a33 * a44 + a13 * a34 * a42 + a14 * a32 * a43 - a14 * a33 * a42 - a34 * a43 * a12 - a44 * a13 * a32 ) * ( -1 );
		m_Value[1][1] = ( a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a14 * a33 * a41 - a34 * a43 * a11 - a44 * a13 * a31 );
		m_Value[2][1] = ( a11 * a32 * a44 + a12 * a34 * a41 + a14 * a31 * a42 - a14 * a32 * a41 - a34 * a42 * a11 - a44 * a12 * a31 ) * ( -1 );
		m_Value[3][1] = ( a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a13 * a32 * a41 - a33 * a42 * a11 - a43 * a12 * a31 );

		m_Value[0][2] = ( a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a14 * a23 * a42 - a24 * a43 * a12 - a44 * a13 * a22 );
		m_Value[1][2] = ( a11 * a23 * a44 + a13 * a24 * a41 + a14 * a21 * a43 - a14 * a23 * a41 - a24 * a43 * a11 - a44 * a21 * a13 ) * ( -1 );
		m_Value[2][2] = ( a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a14 * a22 * a41 - a24 * a42 * a11 - a44 * a12 * a21 ); 
		m_Value[3][2] = ( a11 * a22 * a43 + a12 * a23 * a41 + a13 * a21 * a42 - a13 * a22 * a41 - a23 * a42 * a11 - a43 * a12 * a21 ) * ( -1 );

		m_Value[0][3] = ( a12 * a23 * a34 + a13 * a24 * a32 + a14 * a22 * a33 - a14 * a23 * a32 - a24 * a33 * a12 - a34 * a13 * a22 ) * ( -1 );
		m_Value[1][3] = ( a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a14 * a23 * a31 - a24 * a33 * a11 - a34 * a13 * a21 );
		m_Value[2][3] = ( a11 * a22 * a34 + a12 * a24 * a31 + a14 * a21 * a32 - a14 * a22 * a31 - a24 * a32 * a11 - a34 * a12 * a21 ) * ( -1 );
		m_Value[3][3] = ( a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31 * a23 * a32 * a11 - a33 * a12 * a21 );

		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] *= reverse_determinant; 
			}
		}
		return *this;
	}

	float Matrix4x4::Determinant( void )
	{
		float determinant = 0.0f;
		float a11,a12,a13,a14,a21,a22,a23,a24,a31,a32,a33,a34,a41,a42,a43,a44;
		a11 = m_Value[0][0];a12 = m_Value[0][1];a13 = m_Value[0][2];a14 = m_Value[0][3];
		a21 = m_Value[1][0];a22 = m_Value[1][1];a23 = m_Value[1][2];a24 = m_Value[1][3]; 
		a31 = m_Value[2][0];a32 = m_Value[2][1];a33 = m_Value[2][2];a34 = m_Value[2][3]; 
		a41 = m_Value[3][0];a42 = m_Value[3][1];a43 = m_Value[3][2];a44 = m_Value[3][3]; 
		
		determinant = a14*a23*a32*a41 - a13*a24*a32*a41 - a14*a22*a33*a41 + a12*a24*a33*a41 +
					 a13*a22*a34*a41 - a12*a23*a34*a41 - a14*a23*a31*a42 + a13*a24*a31*a42 +
					 a14*a21*a33*a42 - a11*a24*a33*a42 - a13*a21*a34*a42 + a11*a23*a34*a42 +
					 a14*a22*a31*a43 - a12*a24*a31*a43 - a14*a21*a32*a43 + a11*a24*a32*a43 +
					 a12*a21*a34*a43 - a11*a22*a34*a43 - a13*a22*a31*a44 + a12*a23*a31*a44 +
					 a13*a21*a32*a44 - a11*a23*a32*a44 - a12*a21*a33*a44 + a11*a22*a33*a44;

		return determinant;
	}

////////////////////////////////////////////////////////////////////////////////////

	Matrix4x4 & Matrix4x4::RotateX( float i_rotation )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = 0.0f; 
			}
		}

		m_Value[0][0] = 1.0f;

		m_Value[1][1] = (float)cos( i_rotation * PI /180.0f );
		m_Value[1][2] = (float)-sin( i_rotation * PI /180.0f ); 
		
		m_Value[2][1] = (float)sin( i_rotation * PI /180.0f );
		m_Value[2][2] = (float)cos( i_rotation * PI /180.0f );

		m_Value[3][3] = 1.0f;

		return *this;
	}

	Matrix4x4 & Matrix4x4::RotateY( float i_rotation )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = 0.0f; 
			}
		}
		
		m_Value[0][0] = (float)cos( i_rotation * PI /180.0f );
		m_Value[0][2] = (float)sin( i_rotation * PI /180.0f ); 
		
		m_Value[1][1] = 1.0f;

		m_Value[2][0] = (float)-sin( i_rotation * PI /180.0f );
		m_Value[2][2] = (float)cos( i_rotation * PI /180.0f );

		m_Value[3][3] = 1.0f;

		return *this;
	}

	Matrix4x4 & Matrix4x4::RotateZ( float i_rotation )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = 0.0f; 
			}
		}

		m_Value[0][0] = (float)cos( i_rotation * PI /180.0f );
		m_Value[0][1] = (float)sin( i_rotation * PI /180.0f );
		
		m_Value[1][0] = -1 * (float)sin( i_rotation * PI /180.0f );
		m_Value[1][1] = (float)cos( i_rotation * PI /180.0f );

		m_Value[2][2] = 1.0f; 

		m_Value[3][3] = 1.0f;

		return *this;
	}

////////////////////////////////////////////////////////////////////////////////////
	
	Matrix4x4 & Matrix4x4::Translate( float i_x, float i_y, float i_z )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = 0.0f; 
			}
		}
		m_Value[0][0] = 1.0f;
		m_Value[1][1] = 1.0f;
		m_Value[2][2] = 1.0f;

		m_Value[3][0] = i_x;
		m_Value[3][1] = i_y;
		m_Value[3][2] = i_z;
		m_Value[3][3] = 1.0f;

		return *this;
	}

	Matrix4x4 & Matrix4x4::Translate( const JimEngine::Coordination & i_Translate )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			for( unsigned int j = 0; j < 4; j++ )
			{
				m_Value[i][j] = 0.0f; 
			}
		}
		m_Value[0][0] = 1.0f;
		m_Value[1][1] = 1.0f;
		m_Value[2][2] = 1.0f;

		m_Value[3][0] = i_Translate.Cor_GetX();
		m_Value[3][1] = i_Translate.Cor_GetY();
		m_Value[3][2] = i_Translate.Cor_GetZ();
		m_Value[3][3] = 1.0f;

		return *this;
	}

//////////////////////////////////////////////////////////////////////////////////////////////
	Vector4 Matrix4x4::Left_Multiply( const Coordination & i_vector3 )
	{
		Vector4 temp;
		unsigned int column = 0;
		float a = 0.0f;
			for( unsigned int j = 0; j < 4; j++ )
			{
				a = 0.0f;
				a += m_Value[0][j] * i_vector3.Cor_GetX();
				a += m_Value[1][j] * i_vector3.Cor_GetY();
				a += m_Value[2][j] * i_vector3.Cor_GetZ();
				a += m_Value[3][j];
				temp.Set_Value( column, a ); 
				column++;
				a = 0.0f;
			}
		return temp;
	}
	
	Vector4 Matrix4x4::Left_Multiply( const Vector4 & i_vector4 )
	{
		Vector4 temp;
		unsigned int column = 0;
		float a = 0.0f;
		for( unsigned int j = 0; j < 4; j++ )
		{
			a = 0.0f;
			a += m_Value[0][j] * i_vector4.Get_ValueX();
			a += m_Value[1][j] * i_vector4.Get_ValueY();
			a += m_Value[2][j] * i_vector4.Get_ValueZ();
			a += m_Value[3][j] * i_vector4.Get_ValueW();
			temp.Set_Value( column, a ); 
			column++;
			a = 0.0f;
		}
		return temp;
	}

	Vector4 Matrix4x4::Left_Multiply( const Vector4 & i_vector4, const Matrix4x4 & i_matrix )
	{
		Vector4 temp;
		unsigned int column = 0;
		float a = 0.0f;
			for( unsigned int j = 0; j < 4; j++ )
			{
				a = 0.0f;
				a += i_matrix.Get_Value(0,j) * i_vector4.Get_ValueX();
				a += i_matrix.Get_Value(1,j) * i_vector4.Get_ValueY();
				a += i_matrix.Get_Value(2,j) * i_vector4.Get_ValueZ();
				a += i_matrix.Get_Value(3,j) * i_vector4.Get_ValueW();
				temp.Set_Value( column, a ); 
				column++;
				a = 0.0f;
			}
		return temp;
	}
//////////////////////////////////////////////////////////////////////////////////////////////

	void Matrix4x4::Multiply( const Matrix4x4 & i_other )
	{
		Matrix4x4 temp;
		unsigned int column = 0;
		for( unsigned int i = 0; i < 4; i++ )
		{
			float a = 0.0f;
			for( unsigned int j = 0; j < 4; j++ )
			{
				a = 0.0f;
				a += m_Value[i][0] * i_other.Get_Value(0, j );
				a += m_Value[i][1] * i_other.Get_Value(1, j );
				a += m_Value[i][2] * i_other.Get_Value(2, j );
				a += m_Value[i][3] * i_other.Get_Value(3, j );
				temp.Set_Value( i, column, a ); 
				column++;
			}
			column = 0;
		}
		*this = temp;
	}

	Matrix4x4 Matrix4x4::Multiply( const Matrix4x4 & i_matrix, const Matrix4x4 & i_other )
	{
		Matrix4x4 temp;
		unsigned int column = 0;
		for( unsigned int i = 0; i < 4; i++ )
		{
			float a = 0.0f;
			for( unsigned int j = 0; j < 4; j++ )
			{
				a = 0.0f;
				a += i_matrix.Get_Value(i,0) * i_other.Get_Value(0, j );
				a += i_matrix.Get_Value(i,1) * i_other.Get_Value(1, j );
				a += i_matrix.Get_Value(i,2) * i_other.Get_Value(2, j );
				a += i_matrix.Get_Value(i,3) * i_other.Get_Value(3, j );
				temp.Set_Value( i, column, a ); 
				column++;
			}
			column = 0;
		}
		return temp;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void Matrix4x4::Unit_Test( void )
	{
		Coordination t(1.0f,2.0f,2.0f);
		Vector4 ori_position(2.0f,1.0f,1.0f);
		
		//Test the constructor
		Matrix4x4 matrix_one( 3.0f, 2.0f, 3.0f, 0.0f,
						      2.0f, 1.0f, 1.0f, 2.0f,
						      5.0f, 3.0f, 1.0f, 1.0f,
						      4.0f, 3.0f, 0.0f, 1.0f );
		Matrix4x4 matrix_two(matrix_one);
		
		//Test the matirx multiply 
		Matrix4x4 matrix_three = matrix_two * matrix_one;
		Matrix4x4 matrix_four = matrix_two.Multiply(matrix_two,matrix_one);
		matrix_two.Multiply(matrix_one);
		matrix_four = matrix_two;
		
		//Test the left vector4 multiply matrix 4x4
		Vector4 new_position =  matrix_two.Left_Multiply(ori_position);
		new_position = matrix_two.Left_Multiply( ori_position, matrix_three );

		Vector4 new_position2 = ori_position * matrix_two;
		
		//Test the inverse
		Matrix4x4 matrix_inverse( 2.0f, 3.0f, 1.0f, 1.0f,
						      2.0f, 2.0f, 2.0f, 2.0f,
						      1.0f, 1.0f, 5.0f, 1.0f,
						      2.0f, 5.0f, 1.0f, 1.0f );
		Matrix4x4 inverse = matrix_inverse.Get_Inverse();
		matrix_inverse.Inverse();
		inverse = matrix_inverse;

		//Test the identity
		Matrix4x4 identity = matrix_one.Get_Identity();
		matrix_one.Identity();
		identity = matrix_one;

		//Test the transpose
		Matrix4x4 transpose = matrix_two.Get_Transpose();
		matrix_two.Transpose();
		transpose = matrix_two;

		//Test the rotation
		Matrix4x4 rotatex = matrix_four.RotateX(30.0f);
		Matrix4x4 rotatey = matrix_four.RotateY(30.0f);
		Matrix4x4 rotatez = matrix_four.RotateZ(30.0f);

		//Test the translation
		Matrix4x4 translation = matrix_four.Translate( t );
		translation = matrix_four.Translate(3.0f,4.0f,5.0f);

	}
}

