#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include <assert.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#include <Cheesy.h>

#include <Text.h>

#include <time.h>
#include "Spirte.h"
#include "JimGame.h"

#include "LinkList.h"
#include "Human.h"
#include "Profiling.h"
#include "Messaging.h"

#include "Matrix.h"

void OnKeyPressed( unsigned int i_CharID );
Cheesy::Texture * CreateTextureFromFile( const char * i_pTextureFilename );
void SpriteUpdate(int num, bool Quit, JimEngine::MyList &list,JimEngine::Sprite *i_man);
bool BeginInterface(Cheesy::Point2D TextUL,Cheesy::Point2D TextLR,Cheesy::ColorRGBA i_White,Cheesy::ColorRGBA i_ClearColor,int i_num);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool bKeyPressed = false;
int num = 0;
float current_time = 0.0f;
float last_time = 0.0f;
float delta_time = 0.00001f;
JimEngine::Timer timer;

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	{
		//_CrtSetBreakAlloc( 835 );
		JimEngine::Matrix4x4 a;
		a.Unit_Test();

		JimGame MyGame;
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

		Cheesy::Create( "Cheesy Test App", 2024, 1024, false, false );

		srand((unsigned int)time(NULL));
	
		Cheesy::SetKeyPressCallback(OnKeyPressed);

		bool bQuit = false;

		//Game:Create();
		struct Cheesy::Point2D SSTextUL( 320, 40 );
		struct Cheesy::Point2D SSTextLR( 1520, 380 );
		struct Cheesy::ColorRGBA White( 255, 255, 255, 255 );

		struct Cheesy::ColorRGBA ClearColor( 100, 50, 60, 0 );

		do
		{
			Cheesy::Service( bQuit );

			if( !bQuit )
			{
				bQuit = BeginInterface(SSTextUL,SSTextLR,White,ClearColor, num);
			}
		} while ( (bQuit == false)  &&  (bKeyPressed == false) );
	

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( bQuit == false )
		{
			bKeyPressed = false;
			bool bUpdate = false;
			ClearColor.r = ClearColor.g = ClearColor.b = 80;

			MyGame.Init(num);
			timer.startTimer();

			D3DXVECTOR3	Eye( 0.0f, -30.0f, -40.0f );
			D3DXVECTOR3 LookAt( 0.0f, 0.0f, 0.0f );
			D3DXVECTOR3 Up( 0.0f, 1.0f, 0.0f );

			Cheesy::CreateProjection( D3DX_PI / 4, 0.1f, 100.0f );

			do
			{
				Cheesy::Service( bQuit );

				//************************************* Actors update themselves****************************************************//

				//1. Update Monster and Human
				bQuit = MyGame.Input(num);
				MyGame.Update(delta_time);

				//2. Get the deltatime
				delta_time = (float)timer.stopTimer();

				//3. Change the last time to prepare to the next update.
				timer.startTimer();

				//************************************* Actors draw themselves *****************************************************//
				if( !bQuit )
				{
					if( Cheesy::BeginFrame( ClearColor ) )
					{
						if( Cheesy::Begin3D( ) )
						{
							Cheesy::CreateCamera( Eye, LookAt, Up );
							
							MyGame.Draw();
							
							struct Cheesy::Point2D SSTextUL( 320, 40 );
							struct Cheesy::Point2D SSTextLR( 1520, 380 );
							struct Cheesy::ColorRGBA White( 255, 255, 255, 255 );
							Cheesy::Text::BeginText();
							Cheesy::Text::DrawText( "Protect your girl!", SSTextUL, SSTextLR, White );
							Cheesy::Text::EndText();
						}
						Cheesy::EndFrame();
					}
				}
			bKeyPressed = false;
			} while ( bQuit == false );
		}
	}
	// Number of the monsters:
	// 1:	Count: 15504 Sum: 4 Min: 0 Max: 1 Ave: 0.000001
	// 10:  Count: 2535 Sum: 3 Min: 2 Max: 3 Ave: 0.001183
	// 50:  Count: 169 Sum: 1169 Min: 6 Max: 8 Ave: 6.917160

#ifndef _PROFILE
	JimEngine::Profiling::g_Profiler.PrintAccumulators();
#endif
	//JimEngine::Profiling::g_Profiler.PrintAccumulators();
	
	JimEngine::Sprite::destory();
	Cheesy::Shutdown();

    //_CrtDumpMemoryLeaks();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnKeyPressed( unsigned int i_CharID )
{
	if((i_CharID > 48)&&(i_CharID < 59))
	{
		num = i_CharID - 48;
	}
	else if(i_CharID == 48)
	{
		num = -1;
	}
	else if((i_CharID == 112)||(i_CharID == 80))
	{
		//p
		num = 50;
	}
	else if((i_CharID == 113)||(i_CharID == 81))
	{
		//Quit
		num = -2;
	}
	else if((i_CharID == 87)||(i_CharID == 119))
	{
		//W
		num = 12;
	}
	else if((i_CharID == 83)||(i_CharID == 115))
	{
		//S
		num = 13;
	}
	else if((i_CharID == 65)||(i_CharID == 97))
	{
		//A
		num = 14;
	}
	else if((i_CharID == 68)||(i_CharID == 100))
	{
		//D
		num = 15;
	}
	else if((i_CharID == 77)||(i_CharID == 109))
	{
		//M
		num = 16;
	}
	else
	{
		num = 10;
	}
	//bKeyPressed = true;
}

bool BeginInterface(Cheesy::Point2D TextUL,Cheesy::Point2D TextLR,Cheesy::ColorRGBA i_White,Cheesy::ColorRGBA i_ClearColor,int i_num)
{
	bool Quit = false;
	do
	{
		Cheesy::Service( Quit );

		if( !Quit )
		{
			if( Cheesy::BeginFrame( i_ClearColor ) )
			{
				struct Cheesy::Point2D	origin( 320.0f, 240.0f );
				struct Cheesy::ColorRGB color;

				switch (num)
				{
					case -2:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "Quit the Game", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = true;
						return true;
						break;
					}
					case -1:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "The number should not be zero. Please input again.", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 0:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "Weclome to the my game PROTECT YOUR LOVER, how many cats(monsters) you want in this Game( 1 - 9 ). Key q is for quit", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 12:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "The input should be a number.", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 13:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "The input should be a number.", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 14:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "The input should be a number.", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 15:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "The input should be a number.", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 10:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "The input should be a number.", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						Quit = false;
						return false;
						break;
					}
					case 50:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "Now Game begins!", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						bKeyPressed = true;
						Quit = false;
						return false;
						break;
					}
					default:
					{
						Cheesy::Text::BeginText();
						Cheesy::Text::DrawText( "Now Game begins!", TextUL, TextLR, i_White );
						Cheesy::Text::EndText();

						Cheesy::EndFrame();
						bKeyPressed = true;
						Quit = false;
						return false;
						break;
					}
				}
				
			}
		}
	} while ( (Quit == false)  &&  (bKeyPressed == false) );
	return true;
}