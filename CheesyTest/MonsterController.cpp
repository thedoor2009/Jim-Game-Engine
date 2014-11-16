#include "MonsterController.h"
#include "Spirte.h"
#include "Equal.h"

void MonsterController::UpdateCoordination( JimEngine::Sprite &i_Sprite,float i_deltatime, bool o_IsDone, JimEngine::Sprite & i_Target)
{

	JimEngine::Coordination acceleration;
	acceleration = i_Sprite.Get_Acceleration();
	
	JimEngine::Coordination velocity;
	velocity = i_Sprite.Get_Acceleration();
	
	JimEngine::Coordination direction = i_Target.Get_Position() - i_Sprite.Get_Position();

	if( JimEngine::areAproxEuql( direction.Cor_Magnitude(),0.0f ) )
	{
	}

	else
	{
		direction = direction.Cor_Normalize();

		JimEngine::Coordination acceleration( direction.Cor_GetX() * 1.0f, direction.Cor_GetY() * 1.0f, direction.Cor_GetZ() * 1.0f );
		
		i_Sprite.Set_Acceleration(acceleration );

		velocity = ( i_Sprite.Get_Velocity() + JimEngine::Coordination( acceleration.Cor_GetX() * i_deltatime, acceleration.Cor_GetY() * i_deltatime, 0.0f ) );
	
		JimEngine::Coordination v = velocity;
		if(velocity.Cor_Magnitude() > i_Sprite.Get_MaxVelocity())
		{
			v *= 10.0f / velocity.Cor_Magnitude();
			velocity = v;
		}

		if( i_Sprite.Get_Position().Cor_GetX() > 35.0f  || i_Sprite.Get_Position().Cor_GetX() < -35.0f ) 
		{
			velocity = JimEngine::Coordination( -velocity.Cor_GetX(),-velocity.Cor_GetY(), 0.0f );
		}
		else if( i_Sprite.Get_Position().Cor_GetY() > 33.0f  || i_Sprite.Get_Position().Cor_GetY() < -17.0f )
		{
			velocity = JimEngine::Coordination( -velocity.Cor_GetX(),-velocity.Cor_GetY(), 0.0f );
		}

		i_Sprite.Set_Velocity( velocity );
		i_Sprite.Move( i_deltatime );
	}
}