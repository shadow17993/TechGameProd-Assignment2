#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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
	auto winSize = Director::getInstance()->getVisibleSize();
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	ball = (Sprite*)rootNode->getChildByName("ball");
	// Place Platforms here //
	background = (Sprite*)rootNode->getChildByName("background");
	scoreLabel = (Label*)rootNode->getChildByName("scoreLabel");

	isGameLive = false;

	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	startButton = static_cast<ui::Button*>(rootNode->getChildByName("startButton"));
	startButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::startButtonPressed, this));
	startButton->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));

    return true;
}

void HelloWorld::Update(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();

	if (isGameLive = true)
	{
		// Update stuff goes here
		
	}
}

void HelloWorld::startButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->startGame();
	}
}

void HelloWorld::startGame()
{
	isGameLive = true;

	auto moveTo = MoveTo::create(0.5, Vec2(-winSize.width*0.5f, winSize.height*0.5f)); // Take half a second to move off screen.
	startButton->runAction(moveTo);
}

void HelloWorld::endGame()
{
	isGameLive = false;

	//Bring start button back on screen.
	auto moveTo = MoveTo::create(0.5, Vec2(winSize.width*0.5f, winSize.height*0.5f)); // Take half a second to move on screen.
	startButton->runAction(moveTo);
}

virtual bool HelloWorld::onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchPos = touch->GetPosition();
}

virtual void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchPos = touch->GetPosition();
}

bool HelloWorld::Collision(Sprite* ball, Platform* platform)
{
	if (platform->getBoundingBox().intersectCircle(ball->getPosition(), ball->getBoundingBox().size.width / 2))
	{
		return true;
	}
}