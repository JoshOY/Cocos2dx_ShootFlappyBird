#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
	this->schedule(schedule_selector(HelloWorld::update));

	_targets = new CCArray;
	_birds = new CCArray;

	//ע����������CCArray�޷��Զ��ͷţ�������������Ҫ�ͷ�

	//Music part
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Little_Apple.mp3");

	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

	return true;
}

HelloWorld::~HelloWorld()
{
	if (_targets != NULL)
		_targets->release();
	if (_birds != NULL)
		_birds->release();
}

void HelloWorld::gameLogic(float dt)
{
	this->createPipe();
}

void HelloWorld::createPipe()
{
	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	//���һֻ����
	CCSprite* newpipe = CCSprite::create("pipeLandscape.png");
	int y = rand() % (int)(screenSize.height);
	newpipe->setPosition(ccp(screenSize.width - 20, y));
	this->addChild(newpipe);

	newpipe->setTag(1);
	_targets->addObject(newpipe);

	CCMoveTo* movement = CCMoveTo::create(2, ccp(0, newpipe->getPositionY()) );
	CCCallFunc* SelfDefinedAction = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::pipeDisappear));
	CCSequence* actions = CCSequence::create(movement, SelfDefinedAction, NULL);

	newpipe->runAction(actions);
}

void HelloWorld::menuResponseFunc(CCObject* obj)
{
	
	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	CCMoveTo* movement = CCMoveTo::create(2, ccp(screenSize.width / 2 + 20, screenSize.height / 2));
	//redbird->runAction(movement);
	
	
	CCCallFunc* SelfDefinedAction = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::pipeDisappear));
	CCSequence* actions = CCSequence::create(movement, SelfDefinedAction, NULL);
	
	redbird->runAction(actions);
	
}

void HelloWorld::pipeDisappear(CCNode* who)
{
	//who->setPosition(ccp(redbird->getPositionX(), redbird->getPositionY()));
	int tag = who->getTag();
	if (tag == 2) {
		_birds->removeObject(who);
	} else if (tag == 1) {
		_targets->removeObject(who);
	}

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
	//��ô������е�һ����
	CCTouch* touch = (CCTouch*)(pTouches->anyObject() );
	
	//�õ��������λ��
	CCPoint locationInView = touch->getLocationInView();

	//��UI������ת��ΪOpenGL������
	CCPoint locationFixed = CCDirector::sharedDirector()->convertToGL(locationInView);

	//��ȡ��Ļ�ߴ�
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	if (locationFixed.x <= 20) {

		return;
	}

	CCSprite* enemy = CCSprite::create("bird1.png");
	enemy->setPosition(ccp(20, visibleSize.height / 2.0) );
	this->addChild(enemy);

	enemy->setTag(2);
	_birds->addObject(enemy);

	//��ѧ��ʽorz���������������Ƴ�~
	//
	double dx = locationFixed.x - 20;
	double dy = locationFixed.y - visibleSize.height / 2.0;
	double d = sqrt(dx * dx + dy * dy);

	double D = sqrt(visibleSize.width * visibleSize.width + visibleSize.height * visibleSize.height);

	double ratio = D / d;
	double endx = ratio * dx + 20;
	double endy = ratio * dy + visibleSize.height / 2.0;

	//Ȼ���ȷ�����˶�Ӧ���ƶ�Ŀ��㶯��
	CCMoveTo* move = CCMoveTo::create(D/320, ccp(endx, endy) );
	CCCallFuncN* moveFinish = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::pipeDisappear));
	CCSequence* actions = CCSequence::create(move, moveFinish, NULL);

	enemy->runAction(actions);
}

void HelloWorld::update(float delta) // delta = 1.0 / fps
{
	CCArray* targetsToDelete = new CCArray;
	CCArray* birdsToDelete = new CCArray;
	CCObject* iTarget;
	CCObject* iBird;
	

	CCARRAY_FOREACH(_targets, iTarget) {
		CCSprite* target = (CCSprite*)iTarget;
		CCRect targetZone = CCRectMake(target->getPositionX()
			, target->getPositionY()
			, target->getContentSize().width
			, target->getContentSize().height);

		CCARRAY_FOREACH(_birds, iBird) {
			CCSprite* bird = (CCSprite*)iBird;
			CCRect birdZone = CCRectMake(bird->getPositionX()
				, bird->getPositionY()
				, bird->getContentSize().width
				, bird->getContentSize().height);

			
			if (targetZone.intersectsRect(birdZone)) {
				birdsToDelete->addObject(iBird);
				targetsToDelete->addObject(iTarget);
			} //��ɶ�bird�ı���
		} //��ɶ�pipe�ı���
	}

	CCARRAY_FOREACH(birdsToDelete, iBird) {
		_birds->removeObject(iBird);
		CCSprite* bird = (CCSprite*)iBird;
		bird->removeFromParentAndCleanup(true);
	}

	CCARRAY_FOREACH(targetsToDelete, iTarget) {
		_targets->removeObject(iTarget);
		CCSprite* target = (CCSprite*)iTarget;
		target->removeFromParentAndCleanup(true);
	}

	targetsToDelete->release();
	birdsToDelete->release();
}

	

	
