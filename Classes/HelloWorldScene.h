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

	//destructor
	~HelloWorld();


	/* �������� */

	//�˵���Ӧ����
	void menuResponseFunc(cocos2d::CCObject* obj);

	//
	void gameLogic(float dt);

	//�������������
	void createPipe();

	//����
	cocos2d::CCSprite* redbird;

	//������ʧ����
	void pipeDisappear(cocos2d::CCNode* who);

	//����
	void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
	void update(float delta); // delta = 1.0 / fps

	//array ���� ɾ��Ч�ʵ��� ����Ч�ʸ�
	//list  ���� ɾ�� Ч�ʸ� ����Ч�ʵ�
	cocos2d::CCArray* _targets;
	cocos2d::CCArray* _birds;

};

#endif // __HELLOWORLD_SCENE_H__
