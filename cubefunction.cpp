#include"cubefunction.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <string>
#include <math.h>

CvCapture *capture = cvCreateCameraCapture(0);
IplImage *src;//, *templ,*frame;
IplImage *templ=cvLoadImage("finger.jpg", 1);
IplImage *frame = cvCreateImage( cvSize(533,375),32,1);

class cube{
public:
	cube* next;
	sf::Texture texture;
	int width;
	int height;
	sf::Sprite Sprite;
	b2Body* Body;
	b2BodyDef* BodyDef;
};


cube* create_cube(b2World& World, cube* last){
	
	cube* new_cube=new cube;
	last->next=new_cube;
	b2BodyDef BodyDef;
	new_cube->BodyDef=&BodyDef;
	new_cube->next=NULL;


	BodyDef.position = b2Vec2(rand()%resx/SCALE, -100/SCALE);


	BodyDef.type = b2_dynamicBody;
	new_cube->Body = World.CreateBody(&BodyDef);
	
	int ChaosGod=rand() % funcsum;
	new_cube->texture.loadFromFile(name_list[ChaosGod]);

	new_cube->Sprite.setTexture(new_cube->texture);
	sf::Vector2u size=new_cube->texture.getSize();

	b2PolygonShape Shape;
	Shape.SetAsBox((size.x/2)/SCALE, (size.y/2)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = density;
	FixtureDef.friction = friction;
	FixtureDef.shape = &Shape;
	new_cube->Body->CreateFixture(&FixtureDef);

	new_cube->width=size.x;
	new_cube->height=size.y;
	new_cube->Sprite.setOrigin(size.x/2, size.y/2);
	return new_cube;
}

void movement_calc(cube* current){
	current->Sprite.setPosition(SCALE * current->Body->GetPosition().x, SCALE * current->Body->GetPosition().y);
	current->Sprite.setRotation(current->Body->GetAngle() * 180/b2_pi);
}

void movement_platform(cube* platform){
	sf::Vector2f location;
        double    minval, maxval;
        CvPoint    minloc, maxloc;
	src = cvQueryFrame(capture);
	cvMatchTemplate( src, templ, frame, 0);
	cvMinMaxLoc(frame, &minval, &maxval, &minloc, &maxloc, 0);

	location.x=minloc.x;
	location.y=700;
	if(location.x>200){
	platform->Body->SetLinearVelocity( b2Vec2( -20, 0 ) );
	}else{
	platform->Body->SetLinearVelocity( b2Vec2( 20, 0 ) );}	
	platform->Sprite.setPosition(SCALE * platform->Body->GetPosition().x, SCALE * platform->Body->GetPosition().y);
}



cube* create_platform(b2World& World){
	cube* platform=new cube;
	
	b2BodyDef BodyDef;
	platform->BodyDef=&BodyDef;
	BodyDef.position = b2Vec2(rand()%resx/SCALE, 700/SCALE);
	BodyDef.type = b2_kinematicBody;
	platform->Body = World.CreateBody(&BodyDef);
	platform->texture.loadFromFile("platform.png");

	platform->Sprite.setTexture(platform->texture);
	sf::Vector2u size=platform->texture.getSize();

	b2PolygonShape Shape;
	Shape.SetAsBox((size.x/2)/SCALE, (size.y/2)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = density;
	FixtureDef.friction = friction;
	FixtureDef.shape = &Shape;
	platform->Body->CreateFixture(&FixtureDef);

	platform->width=size.x;
	platform->height=size.y;
	platform->Sprite.setOrigin(size.x/2, size.y/2);
	return platform;
}
