#include <iostream>
#include <math.h>
#include<assert.h>
#include "Coordination.h"
#include "Equal.h"
#include "IsNan.h"


using namespace std;

namespace JimEngine
{

const double Pie = 3.1415926535897932;

const Coordination Coordination::Up( 0.0f, 0.005f, 0.0f );
const Coordination Coordination::Down( 0.0f,-0.005f,0.0f );
const Coordination Coordination::Right( 0.005f,0.0f,0.0f );
const Coordination Coordination::Left( -0.005f,0.0f,0.0f );
const Coordination Coordination::Forward( 0.0f,0.0f,-0.005f );
const Coordination Coordination::Back( 0.0f,0.0f,0.005f );
const Coordination Coordination::Stop( 0.0f,0.0f,0.0f );

//////////////////////////////////////////////////////////////////////////////////

void Coordination::Cor_Set(const float x, const float y, const float z)
{
	c_x = x;
	c_y = y;
	c_z = z;
}

void Coordination::Cor_Show(void) 
{
	cout<<"x:[" <<c_x<<"]";
	cout<<"y:[" <<c_y<<"]";
	cout<<"z:[" <<c_z<<"]";
	cout<<endl;
}

/////////////////////////////////////////////////////////////////////////////////

float Coordination::Cor_Distance(const Coordination &a, const Coordination &b)
{
	return sqrt((pow((a.c_x -b.c_x ),2)+pow((a.c_y - b.c_y),2)+pow((a.c_z - b.c_z ),2)));
}


float Coordination::Cor_Angle(const Coordination &a, const Coordination &b)
{
	float l = Cor_Distance(a,b);
	float angle_pie = asin((a.c_z - b.c_z )/l);
	float angle = (float) (angle_pie * 180 / Pie);
	return angle;
}

Coordination Coordination::Cor_Normalize(void)
{
	float l;
	float t;
	float i_x = c_x;
	float i_y = c_y;
	float i_z = c_z;
	t = pow(c_x,2) + pow(c_y,2) + pow(c_z,2);
	l = sqrt(t);
	i_x /= l;
	i_y /= l;
	i_z /= l;
	return Coordination(i_x,i_y,i_z);
}

float Coordination::Cor_Magnitude(void)
{
	return sqrt(pow(c_x,2) + pow(c_y,2) + pow(c_z,2));
}

//////////////////////////////////////////////////////////////////////////////////

void Coordination::operator = (const Coordination & b)
{
#ifdef _DEBUG
	assert( !(IsNan(b.c_x)) );
	assert( !(IsNan(b.c_y)) );
	assert( !(IsNan(b.c_z)) );
#endif
	
	c_x = b.c_x;
	c_y = b.c_y;
	c_z = b.c_z;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
}

void  Coordination::CoorUnitTest(void)
{
		float t = 0.0f;
		float y = 0.0f;
		bool w_f = IsNan(t);
		cout<<"whether float test: "<<w_f<<endl;

		float a = 1.00000001f;
		float b = 1.00000002f;
		float c = 5.0f;
		float d = 0.2f;
		a = a/c;
		b = b * d;
		bool m_e = areAproxEuql(a,b);
		
		cout<<"euqal test: "<< m_e << endl;

}	

bool Coordination::operator == (const Coordination &a)
{
#ifdef _DEBUG
	assert( !(IsNan(a.c_x)) );
	assert( !(IsNan(a.c_y)) );
	assert( !(IsNan(a.c_z)) );
#endif

	if(!areAproxEuql(c_x,a.c_x))
	{
		return false;
	}

	if(!areAproxEuql(c_y,a.c_y))
	{
		return false;
	}

	if(!areAproxEuql(c_z,a.c_z))
	{
		return false;
	}
	return true;
}

bool Coordination::operator !=(const Coordination &b)
{
#ifdef _DEBUG
	assert( !(IsNan(b.c_x)) );
	assert( !(IsNan(b.c_y)) );
	assert( !(IsNan(b.c_z)) );
#endif

	if(areAproxEuql(c_x,b.c_x))
	{
		return true;
	}

	if(!areAproxEuql(c_y,b.c_y))
	{
		return true;
	}

	if(!areAproxEuql(c_z,b.c_z))
	{
		return true;
	}
	return false;
}

void Coordination::operator += (const Coordination &b)
{
	#ifdef _DEBUG
	assert( !(IsNan(b.c_x)) );
	assert( !(IsNan(b.c_y)) );
	assert( !(IsNan(b.c_z)) );
	#endif

	c_x += b.c_x;
	c_y += b.c_y;
	c_z += b.c_z;
}

void Coordination::operator-= (const Coordination &b)
{
#ifdef _DEBUG
	assert( !(IsNan(b.c_x)) );
	assert( !(IsNan(b.c_y)) );
	assert( !(IsNan(b.c_z)) );
#endif
	
	c_x -= b.c_x;
	c_y -= b.c_y;
	c_z -= b.c_z;
}

void Coordination::operator*= (const Coordination &b)
{
#ifdef _DEBUG
	assert( !(IsNan(b.c_x)) );
	assert( !(IsNan(b.c_y)) );
	assert( !(IsNan(b.c_z)) );
#endif
	
	c_x *= b.c_x;
	c_y *= b.c_y;
	c_z *= b.c_z;
}

void Coordination::operator /= (const Coordination &b)
{
#ifdef _DEBUG
	assert( !(IsNan(b.c_x)) );
	assert( !(IsNan(b.c_y)) );
	assert( !(IsNan(b.c_z)) );
#endif	
	c_x /= b.c_x;
	c_y /= b.c_y;
	c_z /= b.c_z;
}

}