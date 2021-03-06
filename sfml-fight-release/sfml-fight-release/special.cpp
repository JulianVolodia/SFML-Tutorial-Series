#include "player.h"

//SPECIFIC FIGHTER IMPLEMENTATION
FIGHTBETH::FIGHTBETH(){
	Sprite.Resize(100, 200);
	name.SetText("BETH");
	Sprite.SetColor(sf::Color::Red);
	Sprite.SetPosition(100.f, 600.f);
	name.SetPosition(50, 50);
	health.set_pos(50.f);
	state="NULL";
}

FIGHTBETH::FIGHTBETH(std::string pos){
	name.SetText("BETH");
	//store all of Beth's visual states
	sf::Image img;
	img.LoadFromFile("imgs/BETH/beth-idle.png");
	states.push_back(img);
	img.LoadFromFile("imgs/BETH/beth-block.png");
	states.push_back(img);
	img.LoadFromFile("imgs/BETH/beth-punch.png");
	states.push_back(img);
	img.LoadFromFile("imgs/BETH/beth-kick.png");
	states.push_back(img);
	img.LoadFromFile("imgs/BETH/beth-prespec.png");
	states.push_back(img);
	img.LoadFromFile("imgs/BETH/beth-spec.png");
	states.push_back(img);

	Sprite.SetImage(states[0]);

	if(pos=="player1"){
		Sprite.SetPosition(100.f, 800.f-Sprite.GetSize().y);
		name.SetPosition(50, 50);
		health.set_pos(50.f);
	}
	else{
		Sprite.FlipX(true);
		Sprite.SetPosition(1180.f-Sprite.GetSize().x, 800.f-Sprite.GetSize().y);
		name.SetPosition(800, 50);
		health.set_pos(800.f);
	}	
	state="NULL";

	kick_offset = (float)states[3].GetWidth()-states[0].GetWidth();
	punch_offset = (float)states[2].GetWidth()-states[0].GetWidth();

}

blast* FIGHTBETH::special(sf::Vector2f enemy_pos){
	//Sprite.SetColor(sf::Color::White);
	Sprite.SetImage(states[5]);
	if(Sprite.GetPosition().x<enemy_pos.x)
		return new blast(sf::Vector2f(Sprite.GetPosition().x+Sprite.GetSize().x, 
			Sprite.GetPosition().y+(Sprite.GetSize().y/2)), true);
	else
		return new blast(sf::Vector2f(Sprite.GetPosition().x, 
			Sprite.GetPosition().y+Sprite.GetSize().y/2), false);
}

FIGHTDAN::FIGHTDAN(){}

FIGHTDAN::FIGHTDAN(std::string pos){
	name.SetText("DAN");
	//store all of Beth's visual states
	sf::Image img;
	img.LoadFromFile("imgs/DAN/dan-idle.png");
	states.push_back(img);
	img.LoadFromFile("imgs/DAN/dan-block.png");
	states.push_back(img);
	img.LoadFromFile("imgs/DAN/dan-punch.png");
	states.push_back(img);
	img.LoadFromFile("imgs/DAN/dan-kick.png");
	states.push_back(img);
	img.LoadFromFile("imgs/DAN/dan-prespec.png");
	states.push_back(img);
	img.LoadFromFile("imgs/DAN/dan-spec.png");
	states.push_back(img);

	Sprite.SetImage(states[0]);

	if(pos=="player1"){
		Sprite.SetPosition(100.f, 800.f-Sprite.GetSize().y);
		name.SetPosition(50, 50);
		health.set_pos(50.f);
	}
	else{
		Sprite.FlipX(true);
		Sprite.SetPosition(1180.f-Sprite.GetSize().x, 800.f-Sprite.GetSize().y);
		name.SetPosition(800, 50);
		health.set_pos(800.f);
	}	
	state="NULL";

	kick_offset = (float)states[3].GetWidth()-states[0].GetWidth();
	punch_offset = (float)states[2].GetWidth()-states[0].GetWidth();
}

hawk *FIGHTDAN::special(sf::Vector2f enemy_pos){
	state="SPECIAL";
	Sprite = sf::Sprite(states[5], Sprite.GetPosition());
	if(enemy_pos.x<Sprite.GetPosition().x)
		Sprite.FlipX(true);
	return new hawk(Sprite.GetPosition(), enemy_pos);
}