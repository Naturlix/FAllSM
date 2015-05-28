#include<iostream>
#include<Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include"map.h"
#include"cubefunction.cpp"
int main(){
	int i;
	int eventfind;
//Prepare the window
	sf::RenderWindow Window(sf::VideoMode(resx, resy), "BallSM", sf::Style::Fullscreen);
	Window.setFramerateLimit(60);
	sf::Event LogOut;
	
//Prepare the world
	b2Vec2 Gravity(0.f, 0.f);
	b2World World(Gravity);
    
//Create map
	for(i=0; i<mapnum; i++) {CreateWall(World, map[i][0]*32, map[i][1]*32);}
	sf::Texture mapTexture;
	sf::Texture boatTexture;
	sf::Texture vortexTexture;
	sf::Texture finishTexture;
	sf::Texture overTexture;
	sf::Texture winTexture;
	mapTexture.loadFromFile("map1.png");
	boatTexture.loadFromFile("boat.png");
	vortexTexture.loadFromFile("vortex.png");
	finishTexture.loadFromFile("finish.png");
	overTexture.loadFromFile("over.png");
	winTexture.loadFromFile("win.png");
	sf::Sprite mapSprite;
	sf::Sprite vortexSprite;
	sf::Sprite finishSprite;
	sf::Sprite overSprite;
	sf::Sprite winSprite;
	mapSprite.setTexture(mapTexture);
	vortexSprite.setTexture(vortexTexture);
	finishSprite.setTexture(finishTexture);	
	overSprite.setTexture(overTexture);
	mapSprite.setPosition(400, 80);
	finishSprite.setOrigin(32.f,32.f);
	finishSprite.setPosition(25.5*32,17.5*32);
	vortexSprite.setOrigin(16.f,16.f);	

//Create boat
	b2Body* boat=CreateBoat(World, 480, 128);
	sf::Sprite boatSprite;
	boatSprite.setTexture(boatTexture);
	boatSprite.setOrigin(9.f, 9.f);



	while (Window.isOpen()){
	while (Window.pollEvent(LogOut)){if(LogOut.key.code==sf::Keyboard::Escape) Window.close();}
	World.Step(1/60.f, 8, 3);
        Window.clear(sf::Color::White);
	Window.draw(mapSprite);
	Window.draw(finishSprite);	
	for(i=0; i<vortexnum; i++){
		vortexSprite.setPosition(vortex[i][0]*32, vortex[i][1]*32);
		Window.draw(vortexSprite);
	}
	
	BoatMovementCalculation(&Window, boat);
	boatSprite.setPosition(SCALE * boat->GetPosition().x, SCALE * boat->GetPosition().y);
	Window.draw(boatSprite);
	eventfind=eventcheck(boat);
	if(eventfind==1) 
	{
		
		sf::Time elapsed; // set time object
		sf::Time delay = sf::seconds(20.0f);
		overSprite.setPosition(522, 202);
		elapsed = sf::seconds(0.0f);
		sf::Time count = sf::seconds (0.1f);
		
		while (elapsed<=delay) 
		{
			Window.draw(overSprite);
			Window.display(); 
			elapsed += count;
		}
		return 0;
	}
	else if(eventfind==2) 
	{
		sf::Time elapsed; // set time object
		sf::Time delay = sf::seconds(20.0f);
		winSprite.setPosition(522, 202);
		elapsed = sf::seconds(0.0f);
		sf::Time count = sf::seconds (0.1f);
		
		while (elapsed<=delay) 
		{
			Window.draw(winSprite);
			Window.display(); 
			elapsed += count;
		}
		return 0;
	}
        Window.display();
	}
 
        return 0;
}
