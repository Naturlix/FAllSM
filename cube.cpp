#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <math.h>

#define resolution_X 1366
#define resolution_Y 768
#define funcsum 2

std::string name_list[funcsum]={"dev.png","mov.png"};
float g=9.8;
float timedif=0.15;


class cube{
public:
sf::RectangleShape* name;
cube* next;
sf::Texture texture;
sf::Vector2f position;
sf::Vector2f speed;
};

void movement_calc(sf::Vector2f* pos, sf::Vector2f* sp){
pos->y=pos->y+sp->y*timedif+g*pow(timedif,2)/2;
sp->y+=g*timedif;
}


cube* create_cube(cube* last){
int ChaosGod=rand() % funcsum;
cube* new_cube=new cube;
new_cube->name=new sf::RectangleShape;
new_cube->texture.loadFromFile(name_list[ChaosGod]);
new_cube->name->setTexture(&(new_cube->texture));
sf::Vector2u size=new_cube->texture.getSize();
new_cube->name->setSize(sf::Vector2f(size.x,size.y));
last->next=new_cube;
new_cube->position.x=rand() % resolution_X;
new_cube->position.y=-90;
new_cube->speed.y=0;
new_cube->speed.x=0;
return new_cube;
};



int main()
{
	sf::RenderWindow window(sf::VideoMode(resolution_X, resolution_Y), "My window",sf::Style::None);
	cube* last=new cube;
	last=create_cube(last);	
	
	while (window.isOpen()){
	sf::Event event;
        
	while (window.pollEvent(event)){ if (event.key.code == sf::Keyboard::Escape) window.close();}
	
	movement_calc(&(last->position),&(last->speed));
	last->name->setPosition((last->position.x),(last->position.y));


        window.clear(sf::Color::Black);
        window.draw(*(last->name));
        window.display();
    	}

    return 0;
}
