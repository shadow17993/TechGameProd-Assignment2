//platform.h



//definitions/includes --------

//#ifndef _TechGameProd-Assignment2_platform_
//#define _TechGameProd-Assignment2_platform_ //need proper name

#include "cocos2d.h"  

using namespace cocos2d;

//-------------End--------------

//class ------------------------

class Platform : public cocos2d::Node
{
	public:
		Platform();
		~Platform();

		virtual bool init() override;
		static Platform create();
		void update(float);
		void reset(Sprite* platform);

private:
	
	//Right Sprites
	Sprite* platform1;
	Sprite* platform2;
	Sprite* platform3;

	Vec2 startPosition_right;
	Vec2 startPosition_middle;
	Vec2 startPosition_left;

	float	platformSpeed;
};
//--------------End--------------

