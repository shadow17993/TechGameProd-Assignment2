#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float delta);

	virtual bool onTouchBegin(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	void startButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void StartGame();
	void EndGame();

	bool platformCollision(Sprite* ball, Sprite* platform);

	int timer = 0;
	int timercount = 0;

private:
	Sprite* ball;
	Sprite* platform1;
	Sprite* platform2;
	Sprite* platform3;
	TextField* timerText;
	Label* timerLabel;
	Button* startButton;
	Sprite* background1;
	Sprite* background2;
	Platform* platforms;
	//int timer;
	float platformSpeed;
	int speedcount;
	Vec2 touchLocation;

	bool isGameLive;
};

#endif // __HELLOWORLD_SCENE_H__
