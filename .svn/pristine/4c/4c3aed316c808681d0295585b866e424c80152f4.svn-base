#include "JimGame.h"
#include "DebugPrint.h"
#include "CollisionSystem.h"
#include "Messaging.h"


#define COLLIDE_PLAYER      0x01 
#define COLLIDE_MONSTER     0x02 
#define COLLIDE_TRIGGER     0x04
#define COLLIDE_LOVE        0x08 

extern struct Cheesy::_MeshData CubeData;

void JimGame::Init(int i_num)
{
	struct Cheesy::Point2D		center( 0.0f, 0.0f );
	struct Cheesy::Point2D		size( 50.0f, 50.0f );
	struct Cheesy::Point2D		offsetGG( 50.0f, 100.0f );
	struct Cheesy::Point2D		offsetBG( 101.9f, 122.0f );

	struct Cheesy::ColorRGBA	white( 255, 255, 255, 255 );
	Cheesy::UVSet				UVs = { Cheesy::UV( 0.0f, 0.0f ), Cheesy::UV( 1.0f, 0.0f ), Cheesy::UV( 0.0f, 1.0f ), Cheesy::UV( 1.0f, 1.0f ) };
	
	const char * pTextures_Bad[] = { "image/game_enemy.bmp" };
	const char * pTextures_Good[] = { "image/game_guy.bmp" };
	const char * pTextures_Love[] = { "image/game_love.bmp" };

	using namespace LuaPlus;

	LuaState * pState = LuaPlus::LuaState::Create();

	JimEngine::Messaging a;
	
	if(pState)
	{
		if(pState->DoFile("Data/ClassTypes.lua") == 0 )
		{
			//////////////////////////////////////////////////////////////////////////////////////////////////
			// Collideable Objects
			//////////////////////////////////////////////////////////////////////////////////////////////////
			
			LuaObject Actors = pState->GetGlobal( "Actors" );

			for( LuaPlus::LuaTableIterator it( Actors ); it; it.Next() )
			{
				
				LuaObject ThisActor = it.GetValue();
				assert( ThisActor.IsString() );


				LuaObject Class = ThisActor[ "class" ];
				assert( Class.IsString() );


				LuaObject Name = ThisActor[ "name" ];
				assert( Name.IsString() );

				LuaObject MaxVelocity = ThisActor[ "max_velocity" ];
				assert( MaxVelocity.IsNumber() );

				LuaObject PicPath = ThisActor[ "pic_path" ];
				assert( PicPath.IsString() );

				LuaObject Colliders =  ThisActor["collides_with"];

				assert( Colliders.IsTable() );
				
				if(strcmp(Class.GetString(),"Monster") == 0)
				{
					// Get the picture of the object
					Cheesy::Texture * pSampleTexture = CreateTextureFromFile( PicPath.GetString() );
					assert( pSampleTexture );
					
					for(int i = 0; i< i_num; i++)
					{
						//Create the relative object
						JimEngine::Ptr::SharePtr<JimEngine::Sprite> mon = JimEngine::World::Create( Name.GetString(),(float)MaxVelocity.GetNumber() );

						//Set the controller
						mon->SetController(new MonsterController());

						// Set the length of the bounding box
						mon->Set_Bounce_Width( 2 );
						mon->Set_Bounce_Height( 2 );
						mon->Set_Bounce_Thick( 2 );

						mon->Create( center, 0.1f, size, white, *pSampleTexture, UVs );

						Cheesy::Material *pMaterial = Cheesy::Material::Create( "image/Simple.fx", pTextures_Bad, 1 );
						assert( pMaterial );
						mon->Set_Material( pMaterial );

						Cheesy::Mesh * pMesh = Cheesy::Mesh::Create( CubeData );
						assert( pMesh );
						mon->Set_Mesh( pMesh );

						float x = JimEngine::GetRangeRandom(-20,30);
						float y = JimEngine::GetRangeRandom(-20,30);
						float z = JimEngine::GetRangeRandom(0,0);
						mon->Set_Position(JimEngine::Coordination(x,y,z));

						mon->SetCollisionHandler( new JimEngine::CollisionInfo() );
						mon->SetMessageHandler( new CollisionSystem() );
						
						int Set = 0;
						for( LuaPlus::LuaTableIterator it( Colliders ); it; it.Next() )
						{
							LuaObject Value = it.GetValue();
							assert( Value.IsString() ) ;

							// Get the collidable information for the game actors, including the collidable set and collidabel ID
							if(strcmp( Value.GetString(),"Monster" ) == 0 )
							{
								Set = Set | COLLIDE_MONSTER;
							}
							else if(strcmp( Value.GetString(),"Player" ) == 0 )
							{
								Set = Set | COLLIDE_PLAYER;
							}
							else if( strcmp( Value.GetString(),"Trigger" ) == 0 )
							{
								Set = Set | COLLIDE_TRIGGER;
							}
							else if( strcmp( Value.GetString(),"Love" ) == 0 )
							{
								Set = Set | COLLIDE_LOVE;
							}
						}

						mon->Get_CollisionInfo().m_CollisionID = COLLIDE_MONSTER;
						mon->Get_CollisionInfo().m_CollisionSet = Set;

						m_gameWorld.Add(mon);
						m_gameRender.Add(mon);
						m_gameCollision.Add( mon );
					}
					pSampleTexture->Release();
				}
				else if(strcmp(Class.GetString(),"Love") == 0)
				{
					// Get the picture of the object
					Cheesy::Texture * pSampleTexture = CreateTextureFromFile( PicPath.GetString() );
					assert( pSampleTexture );
					
					//Create the relative object
					JimEngine::Ptr::SharePtr<JimEngine::Sprite> love = JimEngine::World::Create( Name.GetString(), ( float )MaxVelocity.GetNumber() );
					
					//Set the controller 
					love->SetController( new MonsterController() );

					// Set the length of the bounding box
					love->Set_Bounce_Width( 2 );
					love->Set_Bounce_Height( 2 );
					love->Set_Bounce_Thick( 2 );

					//Set the picture of the object
					love->Create( center, 0.1f, size, white, *pSampleTexture, UVs );

					Cheesy::Material *pMaterial_good = Cheesy::Material::Create( "image/Simple.fx", pTextures_Love, 1 );
					assert( pMaterial_good );
					love->Set_Material( pMaterial_good );

					Cheesy::Mesh * pMesh = Cheesy::Mesh::Create( CubeData );
					assert( pMesh );
					love->Set_Mesh( pMesh );

					love->SetCollisionHandler( new JimEngine::CollisionInfo() );
					love->SetMessageHandler( new CollisionSystem() );
					love->Set_Position(JimEngine::Coordination( 10.0f, 0.0f, 0.0f));

					int Set = 0;
					for( LuaPlus::LuaTableIterator it( Colliders ); it; it.Next() )
					{
						LuaObject Value = it.GetValue();
						assert( Value.IsString() );

						if(strcmp(Value.GetString(),"Monster") == 0)
						{
							Set = Set | COLLIDE_MONSTER;
						}
						else if(strcmp(Value.GetString(),"Player") == 0)
						{
								Set = Set | COLLIDE_PLAYER;
						}
						else if( strcmp(Value.GetString(),"Trigger") == 0)
						{
							Set = Set | COLLIDE_TRIGGER;
						}
						else if( strcmp(Value.GetString(),"Love") == 0)
						{
							Set = Set | COLLIDE_LOVE;
						}
					}

					love->Get_CollisionInfo().m_CollisionID = COLLIDE_LOVE;
					love->Get_CollisionInfo().m_CollisionSet = Set;
					
					m_gameWorld.Add(love);
					m_gameRender.Add(love);
					m_gameCollision.Add( love );
					
					pSampleTexture->Release();
				}
				else
				{
					// Get the picture of the object
					Cheesy::Texture * pSampleTexture = CreateTextureFromFile( PicPath.GetString() );
					assert( pSampleTexture );
					
					//Create the relative object
					JimEngine::Ptr::SharePtr<JimEngine::Sprite> man = JimEngine::World::Create( Name.GetString(), ( float )MaxVelocity.GetNumber() );
					
					//Set the controller 
					man->SetController( new HumanController() );

					// Set the length of the bounding box
					man->Set_Bounce_Width( 2 );
					man->Set_Bounce_Height( 2 );
					man->Set_Bounce_Thick( 2 );

					//Set the picture of the object
					man->Create( center, 0.1f, size, white, *pSampleTexture, UVs );

					Cheesy::Material *pMaterial_good = Cheesy::Material::Create( "image/Simple.fx", pTextures_Good, 1 );
					assert( pMaterial_good );
					man->Set_Material( pMaterial_good );

					Cheesy::Mesh * pMesh = Cheesy::Mesh::Create( CubeData );
					assert( pMesh );
					man->Set_Mesh( pMesh );

					man->SetCollisionHandler( new JimEngine::CollisionInfo() );
					man->SetMessageHandler( new CollisionSystem() );

					int Set = 0;
					for( LuaPlus::LuaTableIterator it( Colliders ); it; it.Next() )
					{
						LuaObject Value = it.GetValue();
						assert( Value.IsString() );

						if(strcmp(Value.GetString(),"Monster") == 0)
						{
							Set = Set | COLLIDE_MONSTER;
						}
						else if(strcmp(Value.GetString(),"Player") == 0)
						{
							Set = Set | COLLIDE_PLAYER;
						}
						else if( strcmp(Value.GetString(),"Trigger") == 0)
						{
							Set = Set | COLLIDE_TRIGGER;
						}
						else if( strcmp(Value.GetString(),"Love") == 0)
						{
							Set = Set | COLLIDE_LOVE;
						}
					}

					man->Get_CollisionInfo().m_CollisionID = COLLIDE_PLAYER;
					man->Get_CollisionInfo().m_CollisionSet = Set;
					
					m_gameWorld.Add(man);
					m_gameRender.Add(man);
					m_gameCollision.Add( man );
					
					pSampleTexture->Release();
				}
			}
		}
	}
	
	LuaState::Destroy(pState);
}

Cheesy::Texture * JimGame::CreateTextureFromFile( const char * i_pTextureFilename )
{
		assert( i_pTextureFilename != NULL );

		FILE * pFile = NULL; 

		errno_t fopenError = fopen_s( &pFile, i_pTextureFilename, "rb" );
		if( fopenError != 0 )
			return NULL;

		assert( pFile != NULL );

		int FileIOError = fseek( pFile, 0, SEEK_END );
		assert( FileIOError == 0 );

		long FileSize = ftell( pFile );
		assert( FileSize >= 0 );

		FileIOError = fseek( pFile, 0, SEEK_SET );
		assert( FileIOError == 0 );

		char * pBuffer = new char[FileSize];
		assert( pBuffer );

		long FileRead = fread( pBuffer, 1, FileSize, pFile );
		assert( FileRead == FileSize );

		fclose( pFile );

		Cheesy::Texture * pTexture = Cheesy::Texture::Create( pBuffer, FileSize );

		delete [] pBuffer;

		return pTexture;
}