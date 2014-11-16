#include "HumanController.h"
#include "Spirte.h"


void HumanController::UpdateCoordination( JimEngine::Sprite & i_Sprite,float i_deltatime, bool  o_IsDone, JimEngine::Sprite & i_Target)
{
	
	JimEngine::Coordination acceleration;
	acceleration = i_Sprite.Get_Acceleration();
	JimEngine::Coordination velocity;
	
	switch( i_Sprite.Get_Direction() )
	{
	// Up W
	case 1:
		{
			acceleration.Cor_Set(i_Sprite.Get_Acceleration().Cor_GetX(),i_Sprite.Get_Acceleration().Cor_GetY() + 0.7f,i_Sprite.Get_Acceleration().Cor_GetZ());
			break;
		}
	// Down S
	case 2:
		{
			acceleration.Cor_Set(i_Sprite.Get_Acceleration().Cor_GetX(),i_Sprite.Get_Acceleration().Cor_GetY() - 0.7f,i_Sprite.Get_Acceleration().Cor_GetZ());
			break;
		}
	// right D
	case 4:
		{
			acceleration.Cor_Set(i_Sprite.Get_Acceleration().Cor_GetX() + 0.7f,i_Sprite.Get_Acceleration().Cor_GetY(),i_Sprite.Get_Acceleration().Cor_GetZ());
			break;
		}
	// left A
	case 3:
		{
			acceleration.Cor_Set(i_Sprite.Get_Acceleration().Cor_GetX() - 0.7f,i_Sprite.Get_Acceleration().Cor_GetY(),i_Sprite.Get_Acceleration().Cor_GetZ());
			break;
		}
	default:
		{
			acceleration.Cor_Set(0.0f, 0.0f, 0.0f);
			break;
		}
}
	i_Sprite.Set_Acceleration(acceleration);
	acceleration.Cor_Set( acceleration.Cor_GetX() * i_deltatime, acceleration.Cor_GetY() * i_deltatime, acceleration.Cor_GetZ() * i_deltatime );
	velocity = ( i_Sprite.Get_Velocity() + acceleration );
	
	JimEngine::Coordination v = velocity;
	if(velocity.Cor_Magnitude() > i_Sprite.Get_MaxVelocity())
	{
		v *= 10.0f / velocity.Cor_Magnitude();
		velocity = v;
	}

	velocity.Cor_Set(velocity.Cor_GetX() * 0.85f,velocity.Cor_GetY() * 0.85f, velocity.Cor_GetZ() * 0.85f);

	i_Sprite.Set_Velocity(velocity);
	i_Sprite.Move(i_deltatime);

	i_Sprite.Set_Direction(7);
}