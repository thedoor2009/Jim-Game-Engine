#include "Game.h"

namespace JimEngine
{

	//void Game::Init(int i_num)
	//{
		

	//}

	bool Game::Input(int i_num)
	{
		return m_gameWorld.Input(i_num);
	}

	void Game::Update(float i_deltatime)
	{
		m_gameWorld.Update(i_deltatime);
		m_gameCollision.Update();
	}

	void Game::Draw(void)
	{
		m_gameRender.Draw();
	}

	JimEngine::World Game::Get_World(void)
	{
		return m_gameWorld;
	}

	JimEngine::Render Game::Get_Render(void)
	{
		return m_gameRender;
	}

	JimEngine::Collision Game::Get_Collision( void )
	{
		return m_gameCollision;
	}
	
}