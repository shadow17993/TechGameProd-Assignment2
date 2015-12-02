//Platform.cpp



//includes ---------
#include "Platform.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h" //main/gama manager file name

using namespace cocos2d;

//----------------End------------------

//--------------------------------------------------Methods Start-----------------------------------------------------------

//create/delete object method ----------------
Platform* Platform::create()
{
	Platform* myNode = new Platform();
	if (myNode->init())
	{
		myNode->autorelease();
		return myNode;
	}
	else
	{
		CC_SAFE_DELETE(myNode);
		return nullptr;
	}
	return myNode;
}
//----------------End------------------

//init ---------------
bool Platform::init()
{
	if (!Node::init())
	{
		return false;
	}

	//load platform object
	auto rootNode = CSLoader::createNode("Node.csd");//add other platform sprite files if needed
	addChild(rootNode);
	//Add other sprite nodes here!!!!!!!!!!!!!

	//Position this container at left,centre. Anchor point should also be (0.0f, 0.5f).
	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, winSize.height*0.3f));//add size of platform sprite
	this->setAnchorPoint(Vec2(0.0f, 0.3f));
	this->scheduleUpdate();

	//sprites 
	platform1 = (Sprite*)rootNode->getChildByName("Platform1");
	platform2 = (Sprite*)rootNode->getChildByName("Platform2");
	platform3 = (Sprite*)rootNode->getChildByName("Platform3");

	//starting position
	//X Positions for sprites
	startPosition_left = Vec2(0.0f + (platform1->getBoundingBox().size.width / 2), -winSize.height * 0.33); //set to 0 or left side
	startPosition_middle = Vec2(platform2->getBoundingBox().size.width / 2, -winSize.height * 0.99);
	startPosition_right = Vec2(winSize.width - (platform3->getBoundingBox().size.width / 2), -winSize.height * 0.66);//set position to right side
	
	//Set platform speed
	platformSpeed = 3.0f;

	return true;
}
//----------------End------------------

//Update -----------------
void Platform::update(float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)//need file name think
	{
		//Get the window size
		auto  winSize = Director::getInstance()->getVisibleSize();

		platform1->setPosition(platform1->getPosition().x, platform1->getPosition().y + platformSpeed);
		if (platform1->getPosition().y >= winSize.height + 10)
		{
			platform1->setPosition(rand_0_1() * winSize.width, -10);
			while (platform1->getPosition().x > winSize.width - (platform1->getBoundingBox().size.width / 2)
				|| platform1->getPosition().x < platform1->getBoundingBox().size.width / 2)
			{
				reset(platform1);
			}

		}

		platform2->setPosition(platform2->getPosition().x, platform2->getPosition().y + platformSpeed);
		if (platform2->getPosition().y >= winSize.height + 10)
		{
			platform2->setPosition(rand_0_1() * winSize.width, -10);
			while (platform2->getPosition().x > winSize.width - (platform2->getBoundingBox().size.width / 2)
				|| platform2->getPosition().x < platform2->getBoundingBox().size.width / 2)
			{
				reset(platform2);
			}

		}

		platform3->setPosition(platform3->getPosition().x, platform3->getPosition().y + platformSpeed);
		if (platform3->getPosition().y >= winSize.height + 10)
		{
			platform3->setPosition(rand_0_1() * winSize.width, -10);
			while (platform3->getPosition().x > winSize.width - (platform3->getBoundingBox().size.width / 2)
				|| platform3->getPosition().x < platform3->getBoundingBox().size.width / 2)
			{
				reset(platform3);
			}
		}
	}
}
//----------------End------------------


Platform::Platform()
{
	
}

Platform::~Platform()
{
	
}


//loop/reset method ------------------
void Platform::reset(Sprite* platform)
{
	auto  winSize = Director::getInstance()->getVisibleSize();

	platform->setPosition(rand_0_1() * winSize.width, -10);
}
//----------------End------------------

//------------------------------------------------------END--------------------------------------------------------------------