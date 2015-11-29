#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <ui/UIButton.h>

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
	void startButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void startGame();
	void endGame();

	virtual bool onTouchBegin(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);

	bool Collision(Sprite* ball, Sprite* platform);

private:
	Sprite* ball;
	/*Sprite platform1;
	Sprite platform2;
	Sprite platform3;*/
	Label* scoreLabel;
	Sprite* background;
	ui::Button* startButton;
	Vec2 touchPos;

	bool isGameLive;

};

#endif // __HELLOWORLD_SCENE_H__
