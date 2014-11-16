#include "Collision.h"
#include "Messaging.h"
#include "Profiling.h"

namespace JimEngine
{
	void Collision::Update( void )
	{
		#ifndef _PROFILE
			JimEngine::Profiling::ScopedTimer test_timer("Collision");
		#endif

			//JimEngine::Profiling::ScopedTimer test_timer("Collision");

		unsigned int i;
		for( i = 0; i < m_CollisionSpriteArray.size();i++ )
		{
			for( unsigned int j = i+1; j < m_CollisionSpriteArray.size(); j++ )
			{
				AABBox a(m_CollisionSpriteArray.at(i).Get_Pointer());
				AABBox b(m_CollisionSpriteArray.at(j).Get_Pointer());

				Coordination VelocityA = m_CollisionSpriteArray.at(i).Get_Pointer()->Get_Velocity();
				Coordination VelocityB = m_CollisionSpriteArray.at(j).Get_Pointer()->Get_Velocity();

				float RotationA = m_CollisionSpriteArray.at(i).Get_Pointer()->Get_Angle();
				float RotationB = m_CollisionSpriteArray.at(j).Get_Pointer()->Get_Angle();

				if( CollisionDetect( a, VelocityA, RotationA, b, VelocityB, RotationB ) )
				{
					if ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID & b.Get_Sprite()->Get_CollisionInfo().m_CollisionSet )
					{
						if( ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x01 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x02)||
							( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x02 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x01) )
						{
							// Release the monster
							JimEngine::Messaging::Get_Messaging()->SendtheMessage( "ReleaseMonster", m_CollisionSpriteArray.at(j));
						}
						else if( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x02 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x02)
						{
							// Bounce back
							JimEngine::Messaging::Get_Messaging()->SendtheMessage( "BounceBack", m_CollisionSpriteArray.at(i), m_CollisionSpriteArray.at(j));
						}
						else if ( ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x01 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x08)||
								  ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x08 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x01) ) 
						{
							// Bounce back
							JimEngine::Messaging::Get_Messaging()->SendtheMessage( "BounceBack", m_CollisionSpriteArray.at(i), m_CollisionSpriteArray.at(j));
						}
						else if ( ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x02 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x08)||
								  ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x08 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x02 ) ) 
						{
							// Bounce back
							JimEngine::Messaging::Get_Messaging()->SendtheMessage( "ReleaseLove", m_CollisionSpriteArray.at(i));
						}
						else if( ( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x01 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x03)||
							( a.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x03 && b.Get_Sprite()->Get_CollisionInfo().m_CollisionID == 0x01) )
						{
							JimEngine::Messaging::Get_Messaging()->SendtheMessage( "Trigger", m_CollisionSpriteArray.at(i));
						}
					}
					break;
				}
			}
			isMarkDeath();
		}
	}

	void Collision::Add( JimEngine::Ptr::SharePtr< JimEngine::Sprite > i_collider )
	{
		m_CollisionSpriteArray.push_back(i_collider);
	}

	void Collision::isMarkDeath( void )
	{
		for(unsigned int i = 0; i < m_CollisionSpriteArray.size(); i++)
		{
			if(m_CollisionSpriteArray.at(i)->Get_Death())
			{
				m_CollisionSpriteArray.erase(m_CollisionSpriteArray.begin() + i);
			}
		}
	}

	bool Collision::CollisionDetect(  AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA, AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RotationB )
	{
		if (AABBCollision( i_BoxA,  i_VelocityA, i_RotationA, i_BoxB,  i_VelocityB, i_RotationB ) )
		{
			return true;
		}
		else if ( SwapCollision( i_BoxA,  i_VelocityA, i_RotationA, i_BoxB,  i_VelocityB, i_RotationB ) )
		{
			return true;
		}
		return false;
	}

	bool Collision::AABBCollision(  AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA, AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RotationB )
	{
		bool isCollide = true;
		Matrix4x4 AtoB,BtoA;

		Matrix4x4 A_Rotation = i_BoxA.m_rotation;
		Matrix4x4 B_Rotation = i_BoxB.m_rotation;
		Matrix4x4 A_Translate = i_BoxA.m_translate;
		Matrix4x4 B_Translate = i_BoxB.m_translate;
		BtoA = A_Rotation * A_Translate;
		AtoB = B_Rotation * B_Translate;
		AtoB.Inverse();
		BtoA.Inverse();

		Vector4 A_Center;
		Vector4 B_Center;
		Vector4 AtoB_Center;
		Vector4 BtoA_Center;
		
		A_Center.m_x = i_BoxA.m_center.Cor_GetX();
		A_Center.m_y = i_BoxA.m_center.Cor_GetY();
		A_Center.m_z = i_BoxA.m_center.Cor_GetZ();
		A_Center.m_w = 1.0f;
		B_Center.m_x = i_BoxB.m_center.Cor_GetX();
		B_Center.m_y = i_BoxB.m_center.Cor_GetY();
		B_Center.m_z = i_BoxB.m_center.Cor_GetZ();
		B_Center.m_w = 1.0f;

		AtoB_Center = AtoB.Left_Multiply( A_Center );
		BtoA_Center = BtoA.Left_Multiply( B_Center );

		Coordination AtoB_Vel = i_VelocityB - i_VelocityA;
		Coordination BtoA_Vel = i_VelocityA - i_VelocityB;

		Matrix4x4 Matr_RotationA, Matr_RotationB;
		Matrix4x4 RotationA = Matr_RotationA.RotateZ( i_RotationA );
		Matrix4x4 RotationB = Matr_RotationB.RotateZ( i_RotationB );

		float A_HalfX1 =  i_BoxA.m_width * RotationA.Get_Value( 0, 0 ) + i_BoxA.m_height * RotationA.Get_Value( 1, 0 );
		float A_HalfY1 =  i_BoxA.m_width * RotationA.Get_Value( 0, 1 ) + i_BoxA.m_height * RotationA.Get_Value( 1, 1 );
		float A_HalfZ1 =  i_BoxA.m_width * RotationA.Get_Value( 0, 2 ) + i_BoxA.m_height * RotationA.Get_Value( 1, 2 );
		
		float B_HalfX1 =  i_BoxB.m_width * RotationB.Get_Value( 0, 0 ) + i_BoxB.m_height * RotationB.Get_Value( 1, 0 );
		float B_HalfY1 =  i_BoxB.m_width * RotationB.Get_Value( 0, 1 ) + i_BoxB.m_height * RotationB.Get_Value( 1, 1 );
		float B_HalfZ1 =  i_BoxB.m_width * RotationB.Get_Value( 0, 2 ) + i_BoxB.m_height * RotationB.Get_Value( 1, 2 );


		float A_HalfX2 =  i_BoxA.m_width * RotationA.Get_Value( 0, 0 ) - i_BoxA.m_height * RotationA.Get_Value( 1, 0 );
		float A_HalfY2 =  i_BoxA.m_width * RotationA.Get_Value( 0, 1 ) - i_BoxA.m_height * RotationA.Get_Value( 1, 1 );
		float A_HalfZ2 =  i_BoxA.m_width * RotationA.Get_Value( 0, 2 ) - i_BoxA.m_height * RotationA.Get_Value( 1, 2 );
		
		float B_HalfX2 =  i_BoxB.m_width * RotationB.Get_Value( 0, 0 ) - i_BoxB.m_height * RotationB.Get_Value( 1, 0 );
		float B_HalfY2 =  i_BoxB.m_width * RotationB.Get_Value( 0, 1 ) - i_BoxB.m_height * RotationB.Get_Value( 1, 1 );
		float B_HalfZ2 =  i_BoxB.m_width * RotationB.Get_Value( 0, 2 ) - i_BoxB.m_height * RotationB.Get_Value( 1, 2 );

		//A
		float A_extentXY_X1 = abs( A_HalfX1 * AtoB.Get_Value(0,0) + A_HalfY1 * AtoB.Get_Value(1,0) );
		float A_extentXY_X2 = abs( A_HalfX2 * AtoB.Get_Value(0,0) + A_HalfY2 * AtoB.Get_Value(1,0) );
		float A_extentXY_X = A_extentXY_X1;
		if(A_extentXY_X1 < A_extentXY_X2 )
		{
			A_extentXY_X = A_extentXY_X2;
		}
		float A_extentXY_Y1 = abs( A_HalfX1 * AtoB.Get_Value(0,1) + A_HalfY1 * AtoB.Get_Value(1,1) );
		float A_extentXY_Y2 = abs( A_HalfX2 * AtoB.Get_Value(0,1) + A_HalfY2 * AtoB.Get_Value(1,1) );
		float A_extentXY_Y = A_extentXY_Y1;
		if(A_extentXY_Y1 < A_extentXY_Y2 )
		{
			A_extentXY_Y = A_extentXY_Y2;
		}
		float A_extentXY_Z1 = abs( A_HalfX1 * AtoB.Get_Value(0,2) + A_HalfY1 * AtoB.Get_Value(1,2) );
		float A_extentXY_Z2 = abs( A_HalfX2 * AtoB.Get_Value(0,2) + A_HalfY2 * AtoB.Get_Value(1,2) );
		float A_extentXY_Z = A_extentXY_Z1;
		if(A_extentXY_Z1 < A_extentXY_Z2 )
		{
			A_extentXY_Z = A_extentXY_Z2;
		}

		//B
		float B_extentXY_X1 = abs( B_HalfX1 * BtoA.Get_Value(0,0) + B_HalfY1 * BtoA.Get_Value(1,0) );
		float B_extentXY_X2 = abs( B_HalfX2 * BtoA.Get_Value(0,0) + B_HalfY2 * BtoA.Get_Value(1,0) );
		float B_extentXY_X = B_extentXY_X1;
		if(B_extentXY_X1 < B_extentXY_X2 )
		{
			B_extentXY_X = B_extentXY_X2;
		}
		float B_extentXY_Y1 = abs( B_HalfX1 * BtoA.Get_Value(0,1) + B_HalfY1 * BtoA.Get_Value(1,1) );
		float B_extentXY_Y2 = abs( B_HalfX2 * BtoA.Get_Value(0,1) + B_HalfY2 * BtoA.Get_Value(1,1) );
		float B_extentXY_Y = B_extentXY_Y1;
		if( B_extentXY_Y1 < B_extentXY_Y2 )
		{
			B_extentXY_Y = B_extentXY_Y2;
		}
		float B_extentXY_Z1 = abs( B_HalfX1 * BtoA.Get_Value(0,2) + B_HalfY1 * BtoA.Get_Value(1,2) );
		float B_extentXY_Z2 = abs( B_HalfX2 * BtoA.Get_Value(0,2) + B_HalfY2 * BtoA.Get_Value(1,2) );
		float B_extentXY_Z = B_extentXY_Z1;
		if(B_extentXY_Z1 < B_extentXY_Z2 )
		{
			B_extentXY_Z = B_extentXY_Z2;
		}

		float A_min_AX = AtoB_Center.m_x - A_extentXY_X;
		float A_max_AX = AtoB_Center.m_x + A_extentXY_X;
		float A_min_AY = AtoB_Center.m_y - A_extentXY_Y;
		float A_max_AY = AtoB_Center.m_y + A_extentXY_Y;
		float A_min_AZ = AtoB_Center.m_z - A_extentXY_Z;
		float A_max_AZ = AtoB_Center.m_z + A_extentXY_Z;
		//////////////////////////////////////////////////
		float B_min_AX = BtoA_Center.m_x - B_extentXY_X;
		float B_max_AX = BtoA_Center.m_x + B_extentXY_X;
		float B_min_AY = BtoA_Center.m_y - B_extentXY_Y;
		float B_max_AY = BtoA_Center.m_y + B_extentXY_Y;
		float B_min_AZ = BtoA_Center.m_z - B_extentXY_Z;
		float B_max_AZ = BtoA_Center.m_z + B_extentXY_Z;

		RotationA.Get_Inverse();
		RotationB.Get_Inverse();

		float AtoB_Vel_X = AtoB_Vel.Cor_GetX() * RotationB.Get_Value( 0, 0 ) + AtoB_Vel.Cor_GetX() * RotationB.Get_Value( 0, 1 );
		float AtoB_Vel_Y = AtoB_Vel.Cor_GetY() * RotationB.Get_Value( 1, 0 ) + AtoB_Vel.Cor_GetY() * RotationB.Get_Value( 1, 1 );
		float BtoA_Vel_X = BtoA_Vel.Cor_GetX() * RotationA.Get_Value( 0, 0 ) + BtoA_Vel.Cor_GetX() * RotationA.Get_Value( 0, 1 );
		float BtoA_Vel_Y = BtoA_Vel.Cor_GetY() * RotationA.Get_Value( 1, 0 ) + BtoA_Vel.Cor_GetY() * RotationA.Get_Value( 1, 1 );

			if( ( i_BoxB.m_width < A_min_AX ) || ( - i_BoxB.m_width > A_max_AX) )
			{
				//No Collision
				return false;
			}
			else if( ( i_BoxA.m_width < B_min_AX) || ( - i_BoxA.m_width > B_max_AX) )
			{
				//No Collision
				return false;
			}
			else if( ( i_BoxB.m_height < A_min_AY ) || ( - i_BoxB.m_height > A_max_AY) )
			{
				//No Collisison
				return false;
			}
			else if( ( i_BoxA.m_height < B_min_AY) || ( - i_BoxA.m_height > B_max_AY) )
			{
				//No Collisison
				return false;
			}
			else if( ( i_BoxB.m_thick < A_min_AZ ) || ( - i_BoxB.m_thick > A_max_AZ) )
			{
				//No Collisison
				return false;
			}
			else if( ( i_BoxA.m_thick < B_min_AZ ) || ( - i_BoxA.m_thick > B_max_AZ) )
			{
				//No Collisison
				return false;
			}
		return true;
	}


	bool Collision::SwapCollision(  AABBox & i_BoxA, const Coordination & i_VelocityA, const float i_RotationA, AABBox & i_BoxB, const Coordination & i_VelocityB, const float i_RotationB )
	{
		JimEngine::Timer timer;
		timer.startTimer();
		
		bool isCollide = true;
		Matrix4x4 AtoB,BtoA;

		Matrix4x4 A_Rotation = i_BoxA.m_rotation;
		Matrix4x4 B_Rotation = i_BoxB.m_rotation;
		Matrix4x4 A_Translate = i_BoxA.m_translate;
		Matrix4x4 B_Translate = i_BoxB.m_translate;
		BtoA = A_Rotation * A_Translate;
		AtoB = B_Rotation * B_Translate;
		AtoB.Inverse();
		BtoA.Inverse();

		Vector4 A_Center;
		Vector4 B_Center;
		Vector4 AtoB_Center;
		Vector4 BtoA_Center;
		
		A_Center.m_x = i_BoxA.m_center.Cor_GetX();
		A_Center.m_y = i_BoxA.m_center.Cor_GetY();
		A_Center.m_z = i_BoxA.m_center.Cor_GetZ();
		A_Center.m_w = 1.0f;
		B_Center.m_x = i_BoxB.m_center.Cor_GetX();
		B_Center.m_y = i_BoxB.m_center.Cor_GetY();
		B_Center.m_z = i_BoxB.m_center.Cor_GetZ();
		B_Center.m_w = 1.0f;

		AtoB_Center = AtoB.Left_Multiply( A_Center );
		BtoA_Center = BtoA.Left_Multiply( B_Center );

		Coordination AtoB_Vel = i_VelocityB - i_VelocityA;
		Coordination BtoA_Vel = i_VelocityA - i_VelocityB;

		Matrix4x4 Matr_RotationA, Matr_RotationB;
		Matrix4x4 RotationA = Matr_RotationA.RotateZ( i_RotationA );
		Matrix4x4 RotationB = Matr_RotationB.RotateZ( i_RotationB );

		float A_HalfX1 =  i_BoxA.m_width * RotationA.Get_Value( 0, 0 ) + i_BoxA.m_height * RotationA.Get_Value( 1, 0 );
		float A_HalfY1 =  i_BoxA.m_width * RotationA.Get_Value( 0, 1 ) + i_BoxA.m_height * RotationA.Get_Value( 1, 1 );
		float B_HalfX1 =  i_BoxB.m_width * RotationB.Get_Value( 0, 0 ) + i_BoxB.m_height * RotationB.Get_Value( 1, 0 );
		float B_HalfY1 =  i_BoxB.m_width * RotationB.Get_Value( 0, 1 ) + i_BoxB.m_height * RotationB.Get_Value( 1, 1 );
		float A_HalfX2 =  i_BoxA.m_width * RotationA.Get_Value( 0, 0 ) - i_BoxA.m_height * RotationA.Get_Value( 1, 0 );
		float A_HalfY2 =  i_BoxA.m_width * RotationA.Get_Value( 0, 1 ) - i_BoxA.m_height * RotationA.Get_Value( 1, 1 );
		float B_HalfX2 =  i_BoxB.m_width * RotationB.Get_Value( 0, 0 ) - i_BoxB.m_height * RotationB.Get_Value( 1, 0 );
		float B_HalfY2 =  i_BoxB.m_width * RotationB.Get_Value( 0, 1 ) - i_BoxB.m_height * RotationB.Get_Value( 1, 1 );

		//A
		float A_extentXY_X1 = abs( A_HalfX1 * AtoB.Get_Value(0,0) + A_HalfY1 * AtoB.Get_Value(1,0) );
		float A_extentXY_X2 = abs( A_HalfX2 * AtoB.Get_Value(0,0) + A_HalfY2 * AtoB.Get_Value(1,0) );
		float A_extentXY_X = A_extentXY_X1;
		if(A_extentXY_X1 < A_extentXY_X2 )
		{
			A_extentXY_X = A_extentXY_X2;
		}
		float A_extentXY_Y1 = abs( A_HalfX1 * AtoB.Get_Value(0,1) + A_HalfY1 * AtoB.Get_Value(1,1) );
		float A_extentXY_Y2 = abs( A_HalfX2 * AtoB.Get_Value(0,1) + A_HalfY2 * AtoB.Get_Value(1,1) );
		float A_extentXY_Y = A_extentXY_Y1;
		if(A_extentXY_Y1 < A_extentXY_Y2 )
		{
			A_extentXY_Y = A_extentXY_Y2;
		}
		//B
		float B_extentXY_X1 = abs( B_HalfX1 * BtoA.Get_Value(0,0) + B_HalfY1 * BtoA.Get_Value(1,0) );
		float B_extentXY_X2 = abs( B_HalfX2 * BtoA.Get_Value(0,0) + B_HalfY2 * BtoA.Get_Value(1,0) );
		float B_extentXY_X = B_extentXY_X1;
		if(B_extentXY_X1 < B_extentXY_X2 )
		{
			B_extentXY_X = B_extentXY_X2;
		}
		float B_extentXY_Y1 = abs( B_HalfX1 * BtoA.Get_Value(0,1) + B_HalfY1 * BtoA.Get_Value(1,1) );
		float B_extentXY_Y2 = abs( B_HalfX2 * BtoA.Get_Value(0,1) + B_HalfY2 * BtoA.Get_Value(1,1) );
		float B_extentXY_Y = B_extentXY_Y1;
		if( B_extentXY_Y1 < B_extentXY_Y2 )
		{
			B_extentXY_Y = B_extentXY_Y2;
		}

		float A_min_AX = AtoB_Center.m_x - A_extentXY_X;
		float A_max_AX = AtoB_Center.m_x + A_extentXY_X;
		float A_min_AY = AtoB_Center.m_y - A_extentXY_Y;
		float A_max_AY = AtoB_Center.m_y + A_extentXY_Y;

		float B_min_AX = BtoA_Center.m_x - B_extentXY_X;
		float B_max_AX = BtoA_Center.m_x + B_extentXY_X;
		float B_min_AY = BtoA_Center.m_y - B_extentXY_Y;
		float B_max_AY = BtoA_Center.m_y + B_extentXY_Y;

		RotationA.Get_Inverse();
		RotationB.Get_Inverse();

		float AtoB_Vel_X = AtoB_Vel.Cor_GetX() ;
		float AtoB_Vel_Y = AtoB_Vel.Cor_GetY() ;
		float BtoA_Vel_X = BtoA_Vel.Cor_GetX() ;
		float BtoA_Vel_Y = BtoA_Vel.Cor_GetY() ;

		float A_t_x1 = ( AtoB_Center.m_x - ( i_BoxB.m_width + A_extentXY_X ) ) / AtoB_Vel_X ;
		float A_t_x2 = ( AtoB_Center.m_x + ( i_BoxB.m_width + A_extentXY_X ) ) / AtoB_Vel_X ;
		float A_t_y1 = ( AtoB_Center.m_y - ( i_BoxB.m_height + A_extentXY_Y ) ) / AtoB_Vel_Y ;
		float A_t_y2 = ( AtoB_Center.m_y + ( i_BoxB.m_height + A_extentXY_Y ) ) / AtoB_Vel_Y ;

		float A_tx_enter = A_t_x1;
		float A_tx_exit = A_t_x1;
		float A_ty_enter = A_t_y1;
		float A_ty_exit = A_t_y1;

		if( A_t_x2 < A_t_x1 ) A_tx_enter = A_t_x2;
		if( A_t_x2 > A_t_x1 ) A_tx_exit = A_t_x2;
		if( A_t_y2 < A_t_y1 ) A_ty_enter = A_t_y2;
		if( A_t_y2 > A_t_y1 ) A_ty_exit = A_t_y2;

		float B_t_x1 = ( BtoA_Center.m_x - ( i_BoxA.m_width + B_extentXY_X ) ) / ( BtoA_Vel_X );
		float B_t_x2 = ( BtoA_Center.m_x + ( i_BoxA.m_width + B_extentXY_X ) ) / ( BtoA_Vel_X );
		float B_t_y1 = ( BtoA_Center.m_y - ( i_BoxA.m_height + B_extentXY_Y ) ) /( BtoA_Vel_Y );
		float B_t_y2 = ( BtoA_Center.m_y + ( i_BoxA.m_height + B_extentXY_Y ) ) /( BtoA_Vel_Y );

		float B_tx_enter = B_t_x1;
		float B_tx_exit = B_t_x1;
		float B_ty_enter = B_t_y1;
		float B_ty_exit = B_t_y1;

		if( B_t_x2 < B_t_x1 ) B_tx_enter = B_t_x2;
		if( B_t_x2 > B_t_x1 ) B_tx_exit = B_t_x2;
		if( B_t_y2 < B_t_y1 ) B_ty_enter = B_t_y2;
		if( B_t_y2 > B_t_y1 ) B_ty_exit = B_t_y2;

		float delta_time = (float)timer.stopTimer();
			
		isCollide = false;
		if(	BtoA_Vel_X == 0.0f && BtoA_Vel_Y == 0.0f)
		{
			if( ( BtoA_Center.m_y < i_BoxA.m_height &&  BtoA_Center.m_y > -i_BoxA.m_height ) && ( BtoA_Center.m_x < i_BoxA.m_width &&  BtoA_Center.m_x > -i_BoxA.m_width ) )
			{
				isCollide = true;
			}
		}
		else if(	BtoA_Vel_X == 0.0f )
		{
			if( ( B_ty_enter < delta_time * 1000 ) && ( BtoA_Center.m_x < i_BoxA.m_width &&  BtoA_Center.m_x > -i_BoxA.m_width ) )
			{
				if( B_ty_exit > 0.0f )
				{
					isCollide = true;
				}
			}

		}
		else if ( BtoA_Vel_Y == 0.0f )
		{
			if( ( B_tx_enter < delta_time * 1000 ) && ( BtoA_Center.m_y < i_BoxA.m_height &&  BtoA_Center.m_y > -i_BoxA.m_height ) ) 
			{
				if( B_tx_exit > 0.0f )
				{
					isCollide = true;
				}
			}
		}
		else
		{
			if( ( B_tx_enter > B_ty_exit ) || ( B_ty_enter > B_tx_exit ) )
			{
				isCollide = false;
			}
			else
			{
				if ( abs( B_ty_enter ) < delta_time && abs( B_tx_enter ) < delta_time ) 
					isCollide = true;
			}
		}
		return isCollide;
	}
}