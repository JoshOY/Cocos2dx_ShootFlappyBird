#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
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

	if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	
	// step 1 end
	//////////////////////////////

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(HelloWorld::gameLogic), 1);
	

	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

	return true;

}

void HelloWorld::gameLogic(float dt)
{
	this->createRedBird();
}

void HelloWorld::createRedBird()
{
	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	//添加一只红鸟
	CCSprite* newbird = CCSprite::create("angrybird2.png");
	int y = rand() % (int)(screenSize.height);
	newbird->setPosition(ccp(0, y));
	this->addChild(newbird);

	CCMoveTo* movement = CCMoveTo::create(2, ccp(screenSize.width / 2 + 20, screenSize.height / 2));
	CCCallFunc* SelfDefinedAction = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::redbirdDisappear));
	CCSequence* actions = CCSequence::create(movement, SelfDefinedAction, NULL);

	newbird->runAction(actions);
}

void HelloWorld::menuResponseFunc(CCObject* obj)
{
	
	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	CCMoveTo* movement = CCMoveTo::create(2, ccp(screenSize.width / 2 + 20, screenSize.height / 2));
	//redbird->runAction(movement);
	
	
	CCCallFunc* SelfDefinedAction = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::redbirdDisappear));
	CCSequence* actions = CCSequence::create(movement, SelfDefinedAction, NULL);
	
	redbird->runAction(actions);
	
}

void HelloWorld::redbirdDisappear(CCNode* who)
{
	//who->setPosition(ccp(redbird->getPositionX(), redbird->getPositionY()));
	who->removeFromParentAndCleanup(true);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	//获得触摸点中的一个点
	CCTouch* touch = (CCTouch*)(pTouches->anyObject() );
	
	//得到触摸点的位置
	CCPoint locationInView = touch->getLocationInView();

	//将UI点坐标转换为OpenGL点坐标
	CCPoint locationFixed = CCDirector::sharedDirector()->convertToGL(locationInView);

	//获取屏幕尺寸
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	if (locationFixed.x <= 20) {

		return;
	}

	CCSprite* enemy = CCSprite::create("bird1.png");
	enemy->setPosition(ccp(20, visibleSize.height / 2.0) );
	this->addChild(enemy);

	//数学公式orz，由相似三角形推出~
	//
	double dx = locationFixed.x - 20;
	double dy = locationFixed.y - visibleSize.height / 2.0;
	double d = sqrt(dx * dx + dy * dy);

	double D = sqrt(visibleSize.width * visibleSize.width + visibleSize.height * visibleSize.height);

	double ratio = D / d;
	double endx = ratio * dx + 20;
	double endy = ratio * dy + visibleSize.height / 2.0;

	//然后就确定好了对应的移动目标点动作
	CCMoveTo* move = CCMoveTo::create(D/320, ccp(endx, endy) );
	CCCallFuncN* moveFinish = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::redbirdDisappear));
	CCSequence* actions = CCSequence::create(move, moveFinish, NULL);

	enemy->runAction(actions);
}

