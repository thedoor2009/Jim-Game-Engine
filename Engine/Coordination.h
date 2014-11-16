#ifndef COORDINATION_H
#define COORDINATION_H
#include <Windows.h>
#include "DebugPrint.h"
//#include "MemoryPool.h"

namespace JimEngine
{
	//class MemoryPool;
	class Coordination
	{
	public:
		static const Coordination Up;
		static const Coordination Down;
		static const Coordination Right;
		static const Coordination Left;
		static const Coordination Forward;
		static const Coordination Back;
		static const Coordination Stop;

		inline Coordination(const float x = 0.0f,const float y = 0.0f,const float z = 0.0f):c_x(x), c_y(y), c_z(z)	
		{

		}

		inline Coordination( const Coordination &i_other )
		{
			c_x = i_other.c_x;
			c_y = i_other.c_y;
			c_z = i_other.c_z;
		}
	
		~Coordination()
		{

		}

		// Set coordination
		void Cor_Set( const float x, const float y, const float z );
		void Cor_Show( void );

		//Operator reload in class
		void operator = ( const Coordination & b);
		bool operator == (const Coordination &b);
		bool operator != (const Coordination &b);
		void operator += (const Coordination &b);
		void operator -= (const Coordination &b);
		void operator *= (const Coordination &b);
		void operator /= (const Coordination &b);

		//Operator reload out class
		friend Coordination operator + ( const Coordination & a, const Coordination & b);
		friend Coordination operator - ( const Coordination & a, const Coordination & b);
		friend float operator * ( const Coordination &a,const Coordination & b);
	
		// Get the distance between two points
		float Cor_Distance(const Coordination &a, const Coordination &b);
		// Get the angle between two points
		float Cor_Angle(const Coordination &a, const Coordination &b);
		// Normalize the vector
		Coordination Cor_Normalize(void);
		// Get the magnitude of the vector
		float Cor_Magnitude(void);

		// Get coordination
		inline  float Cor_GetX(void) const
		{
			return c_x;
		}

		inline  float Cor_GetY(void) const 
		{
			return c_y;	
		}

		inline  float Cor_GetZ(void) const 
		{
			return c_z;
		}

		inline Coordination Pos_Get( void ) const
		{
			return Coordination( c_x, c_y, c_z );
		}
	
		static void CoorUnitTest(void);

		static void UnityTest(void)
		{
			Coordination *a = new Coordination(0.0f,0.0f,0.0f);
			delete a;
		}
	
	private:
		float  c_x;
		float  c_y;
		float  c_z;
	};

	static const Coordination Zero(0.0f,0.0f,0.0f);

	inline Coordination  operator +( const Coordination & a, const Coordination & b)
	{
		return Coordination ( a.Cor_GetX() + b.Cor_GetX(),a.Cor_GetY() + b.Cor_GetY(),a.Cor_GetZ() + b.Cor_GetZ() );
	}

	inline Coordination operator -( const Coordination & a, const Coordination & b)
	{
		return Coordination(a.Cor_GetX() - b.Cor_GetX(),a.Cor_GetY() - b.Cor_GetY(),a.Cor_GetZ() - b.Cor_GetZ());
	}

	inline float operator * ( const Coordination &a,const Coordination & b)
	{
		return (a.c_x * b.c_x + a.c_y * b.c_y + a.c_z * a.c_z);
	}
}
#endif