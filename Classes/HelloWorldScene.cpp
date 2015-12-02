#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace std;
using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto winSize = Director::getInstance()->getVisibleSize();
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	scheduleUpdate();
	
	//timer = 0;
	platformSpeed = 3.0;
	speedcount = 0;
	
	ball = (Sprite*)rootNode->getChildByName("ball");
	platform1 = (Sprite*)rootNode->getChildByName("platform1");
	platform2 = (Sprite*)rootNode->getChildByName("platform2");
	platform3 = (Sprite*)rootNode->getChildByName("platform3");
	
	background = (Sprite*)rootNode->getChildByName("background");
	
	timerText = (TextField*)rootNode->getChildByName("timerText");

	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	startButton = static_cast<ui::Button*>(rootNode->getChildByName("startButton"));
	startButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::startButtonPressed, this));
	startButton->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));

	isGameLive = false;

    return true;
}

void HelloWorld::update(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();

	if (isGameLive)
	{
		//------------------------------------------//
		//				BALL MOVEMENT				//
		//------------------------------------------//

		Vec2 v = touchLocation - ball->getPosition();
		float l = v.length();
		v.x = v.x / l;
		v.y = v.y / l;
		ball->setPosition(ball->getPosition() - v * 3);

		if (ball->getPosition().x > winSize.width
			|| ball->getPosition().x < 0
			|| ball->getPosition().y > winSize.height
			|| ball->getPosition().y < 0)
		{
			this->EndGame();
		}


		//------------------------------------------//
		//			   PLATFORM MOVEMENT			//
		//------------------------------------------//

		platform1->setPosition(platform1->getPosition().x, platform1->getPosition().y + platformSpeed);
		if (platform1->getPosition().y >= winSize.height + 10)
		{
			platform1->setPosition(rand_0_1() * winSize.width, -10);
			//platform1->setRotation(rand_0_1() * 90);
			while (platform1->getPosition().x > winSize.width - (platform1->getBoundingBox().size.width / 2)
				|| platform1->getPosition().x < platform1->getBoundingBox().size.width / 2)
			{
				platform1->setPosition(rand_0_1() * winSize.width, -10);
				//platform1->setRotation(rand_minus1_1() * 90);
			}
			
		}

		platform2->setPosition(platform2->getPosition().x, platform2->getPosition().y + platformSpeed);
		if (platform2->getPosition().y >= winSize.height + 10)
		{
			platform2->setPosition(rand_0_1() * winSize.width, -10);
			while (platform2->getPosition().x > winSize.width - (platform2->getBoundingBox().size.width / 2)
				|| platform2->getPosition().x < platform2->getBoundingBox().size.width / 2)
			{
				platform2->setPosition(rand_0_1() * winSize.width, -10);
				//platform2->setRotation(rand_minus1_1() * 90);
			}

		}

		platform3->setPosition(platform3->getPosition().x, platform3->getPosition().y + platformSpeed);
		if (platform3->getPosition().y >= winSize.height + 10)
		{
			platform3->setPosition(rand_0_1() * winSize.width, -10);
			while (platform3->getPosition().x > winSize.width - (platform3->getBoundingBox().size.width / 2) 
				|| platform3->getPosition().x < platform3->getBoundingBox().size.width / 2)
			{
				platform3->setPosition(rand_0_1() * winSize.width, -10);
				//platform3->setRotation(rand_minus1_1() * 90);
			}
		}

		//------------------------------------------//
		//			   PLATFORM COLLISION			//
		//------------------------------------------//

		if (platformCollision(ball, platform1) || platformCollision(ball, platform2) || platformCollision(ball, platform3))
		{
			this->EndGame();
		}

		timercount++;
		if (timercount >= 60)
		{
			timer++;
			speedcount++;
			timercount = 0;
			if (speedcount >= 10)
			{
				platformSpeed = platformSpeed + 0.5f;
				speedcount = 0;
			}
		}

		timerText->setString(to_string(timer));
	}
}

void HelloWorld::startButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->startGame();
	}
	this->startGame();
}

void HelloWorld::startGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	auto audio = SimpleAudioEngine::getInstance();
	
	isGameLive = true;

	GameManager::sharedGameManager()->isGameLive = true;

	ball->setPosition(winSize.width / 2, winSize.height*0.7f);

	audio->playBackgroundMusic("MechaMalfunction.wav", true);

	// Reset the score.
	GameManager::sharedGameManager()->ResetScore();

	// Reset the Platforms
	platform1->setPosition(
		(winSize.width * 0.33) - (platform1->getBoundingBox().size.width / 2), 
		 -winSize.height - 10);

	platform2->setPosition(
		(winSize.width * 0.66) - (platform2->getBoundingBox().size.width / 2),
		-winSize.height * 0.33);

	platform3->setPosition(
		(winSize.width * 0.99) - (platform3->getBoundingBox().size.width / 2),
		-winSize.height * 0.66);

	timer = 0;
	timercount = 0;
	platformSpeed = 3;
	speedcount = 0;


	//Retract start button.
	auto moveTo = MoveTo::create(0.5, Vec2(-winSize.width*0.5f, winSize.height*0.5f)); // Take half a second to move off screen.
	startButton->runAction(moveTo);
}

void HelloWorld::endGame()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->setEffectsVolume(0.25f);
	audio->playEffect("Explosion.wav", false, 0.25f, 0.25f, 0.25f);
	
	audio->stopBackgroundMusic(true);

	auto winSize = Director::getInstance()->getVisibleSize();

	isGameLive = false;

	//Bring start button back on screen.
	auto moveTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height*0.5f)); // Take half a second to move on screen.
	startButton->runAction(moveTo);
}

bool HelloWorld::onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchPos = touch->getLocation();
	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchPos = touch->getLocation();
}

bool HelloWorld::Collision(Sprite* ball, Sprite* platform)
{
	if (platform->getBoundingBox().intersectsCircle(ball->getPosition(), ball->getBoundingBox().size.width / 2))
	{
		return true;
	}
}