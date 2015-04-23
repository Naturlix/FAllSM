#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <math.h>
#define resolution_X 1366
#define resolution_Y 768
#define funcsum 2 //number of cube examples
#define COMPLEXITY 50 //cube creating time

//cubes list----------------------------------------
std::string name_list[funcsum]={"dev.png","mov.png"};
//--------------------------------------------------


//gravitation constatns-------------------------
float g=9.8;
float timedif=0.01; //dt
float e=0.1; //that's fucking why i can't jump
float planes[4][3]={
   1,  0, 0,
   0, -1, resolution_Y-70,
   -1, 0, resolution_X,
   0,  1, 0
};
//----------------------------------------------




//cube itself-----------------------------------
class cube{
public:
sf::RectangleShape* name;
cube* next;
sf::Texture texture;
sf::Vector2f position;
sf::Vector2f speed;
sf::Vector2f mspeed;
float angle;
float friction;
};
//-----------------------------------------------

float scalar(sf::Vector2f* first, sf::Vector2f* second){
	return first->x*second->x+first->y*second->y;
}

//movement calculating function-------------------
void movement_calc(cube* body,cube* curent){
sf::Vector2f* pos=&(body->position);
sf::Vector2f* sp=&(body->speed);
float distance;
float collis;
int i;
bool check=1;
sf::Vector2f collision;

sf::FloatRect bodybox = body->name->getGlobalBounds();
sf::FloatRect curentbox;

while(curent->next!=NULL){
	curentbox = curent->name->getGlobalBounds();
	if((bodybox.intersects(curentbox))&&(body!=curent)){
		check=0;
		/*if((body->position.x+body->texture.getSize().x/2 < curent->position.x+body->texture.getSize().x)&&
		   (body->position.x+body->texture.getSize().x/2 > curent->position.x)&&(body->position.y>curent->position.y)){	*/
		curent->speed.y-=(1+e)*curent->speed.y;
		
		sp->y-=(1+e)*curent->speed.y;
		//}
	}
       	curent=curent->next;
	}
if(check)sp->y+=g*timedif;

for (i=0;i<4;i++){
	distance=planes[i][0]*(pos->x)+planes[i][1]*(pos->y)+planes[i][2];
	collis=planes[i][0]*(sp->x)+planes[i][1]*(sp->y);
	collision.x=planes[i][0];
   	collision.y=planes[i][1];
	if(distance<0 && collis<0){
		sp->x-=(1+e)*collision.x*collis;
		sp->y-=(1+e)*collision.y*collis;}
	}

*pos=*pos+*sp;
}
//--------------------------------------------


//Cube creation function----------------------
cube* create_cube(cube* last){
int ChaosGod=rand() % funcsum;
cube* new_cube=new cube;
last->next=new_cube;
new_cube->name=new sf::RectangleShape;
new_cube->texture.loadFromFile(name_list[ChaosGod]);
new_cube->name->setTexture(&(new_cube->texture));
sf::Vector2u size=new_cube->texture.getSize();
new_cube->name->setSize(sf::Vector2f(size.x,size.y));
last->next=new_cube;
new_cube->position.x=rand() % resolution_X;
new_cube->position.y=-60;
new_cube->speed.y=0;
new_cube->speed.x=0;
new_cube->next=NULL;
return new_cube;
};
//----------------------------------------------



int main()
{
	int timer=0;
	sf::RenderWindow window(sf::VideoMode(resolution_X, resolution_Y), "My window",sf::Style::None);
	cube* last=new cube;
	cube* curent;
	last=create_cube(last);	
	cube* first=last;
	
		while (window.isOpen()){
		sf::Event event;
        	timer++;
		
		while (window.pollEvent(event)){ if (event.key.code == sf::Keyboard::Escape) window.close();}
	
		if(timer%COMPLEXITY==0) last=create_cube(last); //ever 1000 create a cube


		curent=first;//start to calculating a movement of all cubes

		do{
		movement_calc(curent,first);
		curent->name->setPosition((curent->position.x),(curent->position.y));
		if(curent->next!=NULL)curent=curent->next;
		} while(curent->next!=NULL);

		
        	window.clear(sf::Color::Black);//clear screen

	
        	curent=first;//display all cubes
		do{			
			window.draw(*(curent->name));
       			if(curent->next!=NULL)curent=curent->next;
		}while(curent->next!=NULL);
	
		window.display();
    		}

    return 0;
}
