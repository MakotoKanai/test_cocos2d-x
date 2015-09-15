#include "HelloWorldScene.h"
#include "practice1.h"

#pragma execution_character_set("utf-8")

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	
	// 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

	PhysicsWorld* world = scene->getPhysicsWorld();
	world->setGravity(Vec2(0, 100));
	world->setSpeed(1.0f);
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// Touchイベント用
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, layer);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, layer);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, layer);

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	auto label = Label::createWithTTF("はろぅ　わーるど", "fonts/07やさしさゴシック.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));

	//auto spritePhysics = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height));
	//spritePhysics->setDynamic(false);
	//spritePhysics->setRotationEnable(false);
	//sprite->setPhysicsBody(spritePhysics);


	auto sprite2 = Sprite::create("EDGE(after).png");
	sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
	auto sprite2Physics = PhysicsBody::createBox(Size(sprite2->getContentSize().width, sprite2->getContentSize().height));
	sprite2Physics->setDynamic(true);
	sprite2Physics->setRotationEnable(false);
	sprite2->setPhysicsBody(sprite2Physics);

	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);
	this->addChild(sprite2, 0);

	// Ver3.x
	// http://study-cocos2d-x.info/scenelayer/61/
	auto labelItem1 = MenuItemLabel::create(LabelTTF::create("ラベルボタン１", "Arial", 48), CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto labelItem2 = MenuItemLabel::create(LabelTTF::create("ラベルボタン２", "Arial", 48), CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	// メニューを縦向きに並べます
	auto menu2 = Menu::create(labelItem1, labelItem2, NULL);
	menu2->alignItemsVertically();
	this->addChild(menu2);

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
		{ origin.x + visibleSize.width / 2 - fieldWidth / 2 - fieldBlockWidth, origin.x + visibleSize.height },
		{ origin.x + visibleSize.width / 2 - fieldWidth / 2, origin.x + visibleSize.height },
		{ origin.x + visibleSize.width / 2 + fieldWidth / 2, origin.x + visibleSize.height },
	};
	for (int i = 0; i < fieldObjectNumber; ++i)
	{
		//Sprite* field = Sprite::create("HelloWorld.png");
		Sprite* field = Sprite::create();
		field->setColor(Color3B::WHITE);
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

    return true;
}

void HelloWorld::ShotCube(Vec2 veloc)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* cube = Sprite::create();
	cube->setColor(Color3B::WHITE);
	cube->setAnchorPoint(Vec2(0, 1.0));

	cube->setTextureRect(Rect(0, 0, 20.0f, 20.0f));
	cube->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + 20.0f));

	auto cubePhysics = PhysicsBody::createBox(Size(cube->getContentSize().width, cube->getContentSize().height));
	cubePhysics->setDynamic(true);
	cubePhysics->setRotationEnable(true);
	cube->setPhysicsBody(cubePhysics);

	cube->getPhysicsBody()->applyImpulse(veloc);

	this->addChild(cube);
}

Rect HelloWorld::getRect(Node* node)
{
	Point point = node->getPosition();
	int width = node->getContentSize().width;
	int height = node->getContentSize().height;
	return Rect(point.x - (width / 2), point.y - (height / 2), width, height);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	touchPoint = touch->getLocation();
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	Point endPoint = touch->getLocation();
	Vect force = Vect(touchPoint.x - endPoint.x, touchPoint.y - endPoint.y) * 4;
	ShotCube(force);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	/*
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif
	*/

	// 練習シーンに遷移
	//次のシーンとして、HelloWorld2シーンをセット
	CCScene* nextScene = Practice1::createScene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if (pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}
