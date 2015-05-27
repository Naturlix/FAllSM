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

int eventcheck(b2Body* boat){
int i;
for(i=0; i<vortexnum; i++){
	if(abs(SCALE * boat->GetPosition().x-vortex[i][0]*32)<20 && abs(SCALE * boat->GetPosition().y-vortex[i][1]*32)<20) return 1;}
for(i=0; i<finishnum; i++){	
	if(abs(SCALE * boat->GetPosition().x-finish[i][0]*32)<5 && abs(SCALE * boat->GetPosition().y-finish[i][1]*32)<5) return 2;}
}




void BoatMovementCalculation(sf::RenderWindow* Window, b2Body* boat){

	float ForceY, ForceX;
        double    minval, maxval;
        CvPoint    minloc, maxloc;
	src = cvQueryFrame(capture);
	cvMatchTemplate( src, templ, frame, 0);
	cvMinMaxLoc(frame, &minval, &maxval, &minloc, &maxloc, 0);

ForceY=(-375/2+minloc.y)*0.01;
ForceX=-(-533/2+minloc.x)*0.01;
b2Vec2 force = b2Vec2(ForceX,ForceY);
boat->SetLinearVelocity(b2Vec2(ForceX,ForceY));
}





 
b2Body* CreateBoat(b2World& World, float X, float Y){
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((18.f/2)/SCALE, (18.f/2)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	return Body;
}
 
void CreateWall(b2World& World, float X, float Y){
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}
