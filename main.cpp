#include<iostream>
#include<Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/String.hpp>
#include <iostream>
#include <string>

#include"cubefunction.cpp"


int main(){
	sf::SoundBuffer buffer;
	buffer.loadFromFile("sound.ogg");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	
	bool ch=0;
//	
	sf::Clock clock; // starts the clock
    sf::Time elapsed1; // set time object
    int intSecondsCounted;
    std::stringstream ss;
//	
	sf::RenderWindow Window(sf::VideoMode(resx, resy, 32), "Test");
    	Window.setFramerateLimit(24);
    //	
    	sf::Font font;
	font.loadFromFile("LiberationSans-Regular.ttf");
	sf::Text text;
	text.setFont (font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Blue);
	text.setPosition(20,20);
//		
	b2Vec2 Gravity(0.f, g);
    	b2World World(Gravity);

	cube* last=new cube;
	cube* current;
	last=create_cube(World, last);	
	cube* first=last;
	int timer=0;
	cube* platform=create_platform(World);

	sf::Event event;
 	while (Window.isOpen()){
	while (Window.pollEvent(event)){ if (event.key.code == sf::Keyboard::Escape) Window.close();}

	timer++;
	if(timer%COMPLEXITY==0) last=create_cube(World, last); //ever 1000 create a cube


        World.Step(1/24.f, 8, 3);


	current=first;//start to calculating a movement of all cubes
       	do{
	movement_calc(current);
	if(current->next!=NULL)current=current->next;
	} while(current->next!=NULL);
	Window.clear(sf::Color::Black);

        current=first;//display all cubes
	do{		
		Window.draw(current->Sprite);
       		if(current->next!=NULL)current=current->next;
	}while(current->next!=NULL);
	movement_platform(platform, sf::Mouse::getPosition(Window).x);
	Window.draw(platform->Sprite);
	
	//	
		elapsed1 = clock.getElapsedTime();
        ss.str(std::string()); //clear the string
        ss << std::endl << "Time"<<std::endl;
        ss << elapsed1.asSeconds();
        //ss << std::endl << "Time";
        text.setString( ss.str().c_str());
//		
	Window.draw(text);
	
        Window.display();
	}
return 0;
}
