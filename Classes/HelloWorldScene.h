#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
	void menuCloseCallback(cocos2d::CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);


	/* 其他函数 */

	//菜单响应函数
	void menuResponseFunc(cocos2d::CCObject* obj);

	//
	void gameLogic(float dt);

	//随机创建红鸟函数
	void createRedBird();

	//红鸟
	cocos2d::CCSprite* redbird;

	//红鸟消失函数
	void redbirdDisappear(cocos2d::CCNode* who);

	//
	void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
};

#endif // __HELLOWORLD_SCENE_H__
