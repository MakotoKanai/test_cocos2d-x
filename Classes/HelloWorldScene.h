#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
	void ShotCube(cocos2d::Vec2 veloc);

public:
	// reference: http://is4cafe.hatenablog.com/entry/20140322/1395418017
	// Touch�C�x���g�p
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// Node��Rect���擾����
	cocos2d::Rect getRect(cocos2d::Node* node);
private:
	// Touch�C�x���g�̊J�n�n�_
	cocos2d::Point touchPoint;
};

#endif // __HELLOWORLD_SCENE_H__
