#ifndef SPRITE_H
#define SPRITE_H

#include "MemoryPool.h"
#include "RenderSprite.h"
#include "CollisionInfo.h"
#include "IMessageHandler.h"
#include "Matrix.h"
#include "Coordination.h"

namespace JimEngine
{
	class SpriteController;
	class Sprite
	{
	public:
		/***************** Constructors and Destructors *****************/
		Sprite( void );
		Sprite( const char* i_pName, float i_maxVelocity );
		Sprite( const JimEngine::Coordination &p, const JimEngine::Coordination &v, const JimEngine::Coordination &a );
		~Sprite();

		/***************** Game Behaviors *****************/
		bool Input( int i_input );
		void Update( float i_deltatime, Sprite & i_Target );
		void Draw( void );

		/***************** Logic Behaviors *****************/
		void Move( void );
		void Move( float i_deltatime );

		/***************** Set Direction of the Actors *****************/
		void  Set_Direction( int direction );
		const int Get_Direction( void );

		/***************** Set and get Acceleation of the Actors *****************/
		void  Set_Acceleration( const Coordination & i_lhs );
		const Coordination & Get_Acceleration( void ) const;

		/***************** Set and get veloctiy of the Actors *****************/
		void  Set_Velocity( const Coordination & i_lhs );
		void  Change_Velocity( const Coordination &i_newVelocity );
		const Coordination & Get_Velocity( void ) const;
		float Get_MaxVelocity(void);

		/***************** Set and get position of the Actors *****************/
		void  Set_Position( const Coordination & i_lhs );
		const Coordination & Get_Position( void ) const;

		/***************** Set and get renderable information of the Actors *****************/
		void Set_Renderable( bool i_renderable );
		const bool Get_Renderable( void ) const;

		/***************** Set and get rotation angle of the Actors *****************/
		void Set_Angle( float i_angle );
		const float Get_Angle( void ) const;
		
		/***************** Set and get death information of the Actors *****************/
		void Set_Death( void );
		bool Get_Death( void );

		/***************** Get the translate and rotate matrix of the Actors *****************/
		Matrix4x4 Get_Translate( void );
		Matrix4x4 Get_Rotation( void );

		/***************** Set and Get the width,height and thick value of the Actors *****************/
		void Set_Bounce_Width( float i_width );
		void Set_Bounce_Height( float i_height );
		void Set_Bounce_Thick( float i_thick );

		const float Get_Bounce_Width( void ) const;
		const float Get_Bounce_Height( void ) const;
		const float Get_Bounce_Thick( void ) const;

		/***************** Rendering Stuff of Actors *****************/
		void Create(const Cheesy::Point2D & i_Center, float i_Depth, const Cheesy::Point2D & i_Dimensions, const Cheesy:: ColorRGBA & i_Color, Cheesy::Texture & i_Texture, const Cheesy::UVSet & i_UVs );
		void Set_Material( Cheesy::Material *i_Material );
		void Set_Mesh( Cheesy::Mesh *i_Mesh );

		/***************** Handlers and Controllers of Actors *****************/
		void SetController( SpriteController *i_controller );
		void SetCollisionHandler( CollisionInfo *i_collision );
		void SetMessageHandler( IMessageHandler *i_messageHandler );

		const char* SpriteName_Get( void ) const;
		CollisionInfo & Get_CollisionInfo( void );

		static void destory();

		#ifdef _DEBUG
		#define DEBUG_NEW new

		void *operator new(const size_t i_size)
		{
			DEBUG_PRINT( "new constructor called\n" );
			if(pMemoryPool == NULL)
			{
				pMemoryPool = MemoryPool::create(sizeof(Sprite),102);
			}
			assert(pMemoryPool != NULL);
			return pMemoryPool->alloc(sizeof(Sprite));

		}

		void operator delete(void *i_ptr)
		{
			pMemoryPool->Free(i_ptr);
		}

		#else
		#define DEBUG_NEW new
		#endif

	private:
		static MemoryPool *pMemoryPool;
		float m_maxVelocity;
		float m_angle;
		float m_bounce_width;
		float m_bounce_height;
		float m_bounce_thick;
		int m_direction;
		char *m_pName;
		bool m_Death;
		bool m_renderable;

	protected:
		Coordination							  m_position;
		Coordination							  m_velocity;
		Coordination							  m_acceleration;

		SpriteController						 *m_controller;
		CollisionInfo							 *m_collisionHandler;
		IMessageHandler							 *m_messageHandler;
		RenderSprite                              m_renderSprite;

		Matrix4x4								  m_translate;
		Matrix4x4								  m_rotation;
	};
}
#endif