
ClassTypes = {
	"Monster",
	"Player",
	"Zombie",
	"Droid"
}

Actors = 
{
	{
		name = "Jim",
		class = "Player",
		max_velocity = 700.0,
		collides_with = {"Monster","Love","Trigger"},
		pic_path = "./image/game_guy.bmp",
			

	} ,
	{
		name = "Yuskix",
		class = "Love",
		max_velocity = 700.0,
		collides_with = {"Monster","Player"},
		pic_path = "./image/game_guy.bmp",
			

	} ,

	{
		name = "Sakura",
		class = "Monster",
		max_velocity = 410.0,
		collides_with = {"Monster","Player","Love"},
		pic_path = "./image/game_enemy.bmp",
		
	}
	
}

Trigger = 
{
	{
		name = "Bounce",
		class = "TriggerBox",
		collides_with = {"Monster","Player"},
		Size = 10.0,
		pic_path = "./image/game_enemy.bmp",
	},

	{
		name = "Bounce",
		class = "TriggerBox",
		collides_with = {"Monster","Player"},
		Size = 10.0,
		pic_path = "./image/game_enemy.bmp",
	},

	{
		name = "Bounce",
		class = "TriggerBox",
		collides_with = {"Monster","Player"},
		Size = 10.0,
		pic_path = "./image/game_enemy.bmp",
	},

	{
		name = "Bounce",
		class = "TriggerBox",
		collides_with = {"Monster","Player"},
		Size = 10.0,
		pic_path = "./image/game_enemy.bmp",
	}  
	
}