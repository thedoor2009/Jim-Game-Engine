#include <iostream>
#include "Spirte.h"
#include "SpriteController.h"
#include "CollisionInfo.h"
#include "Coordination.h"
#include "DebugPrint.h"

using namespace std;

namespace JimEngine
{
	/***************** Constructors and Destructors *****************/
	MemoryPool *Sprite::pMemoryPool = NULL;
	Sprite::Sprite( void )
	{
		m_position.Cor_Set(0.0f,0.0f,0.0f);
		m_velocity.Cor_Set(0.0f,0.0f,0.0f);
		m_acceleration.Cor_Set(0.0f,0.0f,0.0f);
		m_controller = NULL;

		m_maxVelocity = 100.0f;
		m_pName = NULL;
		m_Death = false;

		m_rotation.Identity();
		m_translate.Identity();

		m_angle = 0.0f;

		m_renderable = true;
	}

	Sprite::Sprite( const char* i_pName, float i_maxVelocity)
	{
		m_position.Cor_Set(0.0f,0.0f,0.0f);
		m_velocity.Cor_Set(0.0f,0.0f,0.0f);
		m_acceleration.Cor_Set(0.0f,0.0f,0.0f);
		m_controller = NULL;

		m_maxVelocity = i_maxVelocity;
		m_pName = const_cast<char*>(i_pName);
		m_Death = false;

		m_rotation.Identity();
		m_translate.Identity();

		m_angle = 0.0f;

		m_renderable = true;
	}
	Sprite::Sprite( const Coordination &p, const Coordination &v,const JimEngine::Coordination &a)
	{
		m_position = p;
		m_velocity = v;
		m_acceleration = a;
		m_controller = NULL;

		m_maxVelocity = 100.0f;
		m_pName = NULL;
		m_Death = false;

		m_rotation.Identity();
		m_translate.Identity();

		m_angle = 0.0f;

		m_renderable = true;
	}

	Sprite::~Sprite( void )
	{	
		if( m_controller )       delete m_controller;
		if( m_collisionHandler ) delete m_collisionHandler;
		if( m_messageHandler )   delete m_messageHandler;
	}

	/***************** Game Behaviors *****************/
	bool Sprite::Input(int i_input)
	{
		switch(i_input)
		{
		case -2:
			{
				return true;
			}
		case 12:
			{
				Set_Direction(1);
				break;
			}
		case 13:
			{
				Set_Direction(2);
				break;
			}
		case 14:
			{
				Set_Direction(3);
				break;
			}
		case 15:
			{
				Set_Direction(4);
				break;
			}
		default:
			break;
		}
		return false;
	
	}

	void Sprite::Update(float i_deltatime, Sprite & i_Target)
	{
		m_controller->UpdateCoordination( *this,i_deltatime,false,i_Target );
	}

	void Sprite::Draw( void )
	{
		m_angle += 0.0001f;
		if( m_angle > 360.0f )
		{
			m_angle -= 360.0f;
		}

		D3DXMATRIX	RotZ, RotY;
		D3DXMATRIX  Translation;
		D3DXMATRIX  LocalToWorld;
		 
		D3DXMatrixRotationZ( &RotZ, m_angle );
		D3DXMatrixRotationY( &RotY, 0.0f    );
		D3DXMatrixTranslation( &Translation, m_position.Cor_GetX(), m_position.Cor_GetY(), m_position.Cor_GetZ() );

		D3DXMatrixMultiply( &LocalToWorld, &RotY, &RotZ );
		D3DXMatrixMultiply( &LocalToWorld, &LocalToWorld, &Translation );
		
		if( m_renderable )
		{
			m_renderSprite.Draw( &LocalToWorld, *m_renderSprite.Actor_Material );
		}
	}

	/***************** Logic Behaviors *****************/
	void Sprite::Move( void )
	{
		m_position = m_position + m_velocity;
	}

	void Sprite::Move( float i_deltatime )
	{
		m_position.Cor_Set( ( m_position.Cor_GetX() +	m_velocity.Cor_GetX() * i_deltatime + m_acceleration.Cor_GetX() * 0.5f * pow( i_deltatime,2.0f ) ),
						    ( m_position.Cor_GetY() +	m_velocity.Cor_GetY() * i_deltatime + m_acceleration.Cor_GetY() * 0.5f * pow( i_deltatime,2.0f ) ),
			                ( m_position.Cor_GetZ() +	m_velocity.Cor_GetZ() * i_deltatime + m_acceleration.Cor_GetZ() * 0.5f * pow( i_deltatime,2.0f ) ) );
		m_translate.Translate(m_position.Cor_GetX(), m_position.Cor_GetY(), m_position.Cor_GetZ() );
		m_rotation.RotateZ( m_angle );

	}

	/***************** Set Direction of the Actors *****************/
	void Sprite::Set_Direction( int direction )
	{
		m_direction = direction;
	}

	const int Sprite::Get_Direction( void )
	{
		return m_direction;
	}

	/***************** Set and get position of the Actors *****************/
	void Sprite::Set_Position( const Coordination & i_lhs )
	{
		m_position = i_lhs;
	}

	const Coordination & Sprite::Get_Position( void ) const
	{
		return m_position;
	}


	/***************** Set and get Acceleation of the Actors *****************/
	void Sprite::Set_Acceleration(const Coordination & i_lhs)
	{
		m_acceleration = i_lhs;
	}

	  const Coordination & Sprite::Get_Acceleration( void ) const
	{
		return m_acceleration;
	}

	 /***************** Set and get veloctiy of the Actors *****************/
	void Sprite::Set_Velocity( const Coordination & i_lhs )
	{
		m_velocity = i_lhs;
	}

	void Sprite::Change_Velocity(const Coordination & i_newVelocity)
	{
		m_velocity = i_newVelocity;
	}

	const Coordination & Sprite::Get_Velocity( void ) const
	{
		return m_velocity;
	}

	float Sprite::Get_MaxVelocity( void )
	{
		return m_maxVelocity;
	}

	/***************** Set and get renderable information of the Actors *****************/
	void Sprite::Set_Renderable( bool i_renderable )
	{
		m_renderable = i_renderable;
	}

	const bool Sprite::Get_Renderable( void ) const
	 {
		  return m_renderable;
	 }

	/***************** Set and get rotation angle of the Actors *****************/
	void Sprite::Set_Angle( float i_angle )
	{
		m_angle = i_angle;
	}

	const float Sprite::Get_Angle( void ) const
	{
		return m_angle;
	}

	/***************** Set and get death information of the Actors *****************/
	void Sprite::Set_Death( void )
	{
		m_Death = true;
	}

	bool Sprite::Get_Death( void )
	{
		return m_Death;
	}

	/***************** Get the translate and rotate matrix of the Actors *****************/
	Matrix4x4 Sprite::Get_Translate( void )
	{
		return m_translate;
	}

	Matrix4x4 Sprite::Get_Rotation( void )
	{
		return m_rotation;
	}

	/***************** Set and Get the width,height and thick value of the Actors *****************/
	void Sprite::Set_Bounce_Width( float i_width )
	{
		m_bounce_width = i_width;
	}

	void Sprite::Set_Bounce_Height( float i_height )
	{
		m_bounce_height = i_height;
	}

	void Sprite::Set_Bounce_Thick( float i_thick )
	{
		m_bounce_thick = i_thick;
	}

	const float Sprite::Get_Bounce_Width( void ) const
	{
		return m_bounce_width;
	}

	const float Sprite::Get_Bounce_Height( void ) const
	{
		return m_bounce_height;
	}

	const float Sprite::Get_Bounce_Thick( void ) const
	{
		return m_bounce_thick;
	}


	CollisionInfo & Sprite::Get_CollisionInfo( void )
	{
		return *m_collisionHandler;
	}

	const char* Sprite::SpriteName_Get( void ) const
	{
		return m_pName;
	}

	/***************** Handlers and Controllers of Actors *****************/
	void Sprite::SetController( SpriteController *i_controller )
	{
		m_controller = i_controller;
	}

	void Sprite::SetCollisionHandler( CollisionInfo *i_collision )
	{
		m_collisionHandler = i_collision;
	}

	void Sprite::SetMessageHandler( IMessageHandler *i_messageHandler )
	{
		m_messageHandler = i_messageHandler;
	}
	
	/***************** Rendering Stuff of Actors *****************/
	void Sprite::Create(const Cheesy::Point2D & i_Center, float i_Depth, const Cheesy::Point2D & i_Dimensions, const Cheesy:: ColorRGBA & i_Color, Cheesy::Texture & i_Texture, const Cheesy::UVSet & i_UVs )
	{
		Cheesy::Sprite *temp = Cheesy::Sprite::Create(i_Center,i_Depth,i_Dimensions,i_Color,i_Texture,i_UVs);
		m_renderSprite.Actor_Pointer = temp;
	}

	void Sprite::Set_Material( Cheesy::Material *i_Material )
	{
		m_renderSprite.Actor_Material = i_Material;
	}

	void Sprite::Set_Mesh( Cheesy::Mesh *i_Mesh )
	{
		m_renderSprite.Actor_Mesh = i_Mesh;
	}

	void Sprite::destory()
	{
		delete pMemoryPool;
	}

}

