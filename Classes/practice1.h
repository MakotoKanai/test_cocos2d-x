#ifndef __PRACTICE_SCENE_1_H__
#define __PRACTICE_SCENE_1_H__

#include "cocos2d.h"

class Practice1 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Practice1);

public:
	//public:ÇÃç≈å„Ç…í«â¡ÅB
	//void update(float delta);
	void updateByTimer(float time);
private:
	int count;
	void _update(float delta);
	cocos2d::Label *nowCount = nullptr;
};

#endif // __PRACTICE_SCENE_1_H__
