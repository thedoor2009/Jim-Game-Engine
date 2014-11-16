#ifndef SPRITECONTROLLER_H
#define SPRITECONTROLLER_H


namespace JimEngine
{
	class Sprite;
	class SpriteController
	{
	public:
		virtual void UpdateCoordination(  Sprite & i_Sprite,float i_deltatime, bool o_IsDone, Sprite & i_Target) = 0;
		virtual ~SpriteController()
		{

		}
	};

}
#endif