#include "practice1.h"

#pragma execution_character_set("utf-8")

USING_NS_CC;

Scene* Practice1::createScene()
{
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = Practice1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	PhysicsWorld* world = scene->getPhysicsWorld();
	world->setGravity(Vec2(0, -100));
	world->setSpeed(1.0f);
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Practice1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Practice1::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	auto label = Label::createWithTTF("練習シーン１", "fonts/07やさしさゴシック.ttf", 24);
	label->setAnchorPoint(Vec2(0.0f, 0.0f));
	label->setPosition(origin.x, origin.y + visibleSize.height);
	this->addChild(label);

	nowCount = Label::createWithTTF("現在のカウント:    0", "fonts/07やさしさゴシック.ttf", 24);
	nowCount->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(nowCount);
	count = 0;

	// add this scene to update schedule
	//this->scheduleUpdate();
	//this->schedule(schedule_selector(Practice1::updateByTimer), 1.0f);

	// create field
	// 空のスプライトを用意
	float fieldWidth = visibleSize.width / 2;
	float fieldHeight = visibleSize.height + 100.0f;
	float fieldBlockWidth = fieldWidth / 8;
	const int fieldObjectNumber = 3;
	Rect fieldSizes[fieldObjectNumber] = {
		{ 0, 0, fieldBlockWidth, fieldHeight },
		{ 0, 0, fieldWidth, fieldBlockWidth },
		{ 0, 0, fieldBlockWidth, fieldHeight },
	};
	Point fieldPoints[fieldObjectNumber] = {
		{ origin.x + visibleSize.width / 2 - fieldWidth/2 - fieldBlockWidth, origin.x + visibleSize.height },
		{ origin.x + visibleSize.width / 2 - fieldWidth / 2, origin.x + visibleSize.height },
		{ origin.x + visibleSize.width / 2 + fieldWidth / 2, origin.x + visibleSize.height },
	};
	//for (int i = 0; i < fieldObjectNumber; ++i)
	for (int i = 0; i < 1; ++i)
	{
		Sprite* field = Sprite::create("HelloWorld.png");
		//Sprite* field = Sprite::create();
		//field->setColor(Color3B::WHITE);
		field->setAnchorPoint(Vec2(0, 1.0));

		field->setTextureRect(fieldSizes[i]);
		field->setPosition(fieldPoints[i]);
		
		//auto fieldPhysics = PhysicsBody::createBox(fieldSizes[i].size);
		auto fieldPhysics = PhysicsBody::createBox(Size(field->getContentSize().width, field->getContentSize().height));
		fieldPhysics->setDynamic(false);
		fieldPhysics->setRotationEnable(false);
		field->setPhysicsBody(fieldPhysics);

		this->addChild(field);
	}

	auto sprite2 = Sprite::create("EDGE(after).png");
	sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
	auto sprite2Physics = PhysicsBody::createBox(Size(sprite2->getContentSize().width, sprite2->getContentSize().height));
	sprite2Physics->setDynamic(true);
	sprite2Physics->setRotationEnable(false);
	sprite2->setPhysicsBody(sprite2Physics);
	this->addChild(sprite2);

	return true;						
}

/*void Practice1::update(float delta)
{
	_update(delta);
}*/
void Practice1::updateByTimer(float time)
{
	_update(time);
}

void Practice1::_update(float delta)
{
	// reference: http://mettoboshi.com/cocos2d-x/scheduler
	count++;
	// reference: http://mettoboshi.com/cocos2d-x/cocos2d-x-label
	//std::unique_ptr<String> labelString(String::createWithFormat("現在のカウント: %4d", count));
	auto labelString(String::createWithFormat("現在のカウント: %4d", count));
	nowCount->setString(labelString->getCString());
}

void Practice1::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
