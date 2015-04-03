#include "HelloWorldScene.h"
#include "VisibleRect.h"

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

USING_NS_CC;

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
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}
void HelloWorld::onEnter()
{

	Layer::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto label = Label::createWithTTF(title().c_str(), "arial.ttf", 32.0f);
	addChild(label, 1);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
            origin.y + visibleSize.height - label->getContentSize().height));


	_ball = Sprite::create("ball.png");
	_ball->setScale(2.f);
	_ball->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	addChild(_ball);

	    _ball->retain();
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event)
{
//     double fNow = pAccelerationValue->timestamp;
//
//     if (_lastTime > 0.0)
//     {
//         auto ptNow = convertToUI
//     }
//
//     _lastTime = fNow;

    auto pDir = Director::getInstance();

    /*FIXME: Testing on the Nexus S sometimes _ball is NULL */
    if ( _ball == NULL ) {
        return;
    }

    auto ballSize  = _ball->getContentSize();

    auto ptNow  = _ball->getPosition();
    auto ptTemp = pDir->convertToUI(ptNow);

    ptTemp.x += acc->x * 9.81f;
    ptTemp.y -= acc->y * 9.81f;

    auto ptNext = pDir->convertToGL(ptTemp);
    FIX_POS(ptNext.x, (VisibleRect::left().x+ballSize.width *2 / 2.0), (VisibleRect::right().x - ballSize.width * 2 / 2.0));
    FIX_POS(ptNext.y, (VisibleRect::bottom().y+ballSize.height *2 / 2.0), (VisibleRect::top().y - ballSize.height * 2/ 2.0));
    _ball->setPosition(ptNext);
}
std::string HelloWorld::title() const
{
    return "AccelerometerTest";
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
