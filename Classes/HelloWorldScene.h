#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ClipNode.h"
#include "Bunny.h"


const int TAG_action = 13;
const int TAG_score = 20;

struct BunnyHoles {
	BunnyHoles();
	bool isUnused[3][3];
	cocos2d::CCPoint position[3][3];
	cocos2d::CCSprite* pBackHole[3][3];
	cocos2d::CCSprite* pFrontHole[3][3];
};



class HelloWorld : public cocos2d::CCLayer
{
private:
	BunnyHoles* bunnyHoles;
	cocos2d::CCArray* pBunnyArray;
	void clearBunny(CCNode*);
	void clearParticle(CCNode*);
	int randHeightPos;

	float fSpawnSpeed, fUpSpeed, fDownSpeed, fDelay, fFloatPeriod, fMultiplier;
	float t_fSpawnSpeed, t_fUpSpeed, t_fDownSpeed, t_fDelay, t_fFloatPeriod;

protected:
	cocos2d::CCSprite*				tmpSprite;
    cocos2d::CCParticleSystem		m_emitter;
    cocos2d::CCSprite*				m_background;
	cocos2d::CCTouch*				pLastTouch ;
	cocos2d::CCLabelTTF*			pScoreLabel;

public:	
	void actionBunnyMove(Bunny* b);
	int pTotalScore;
	void updateScore(int);
	cocos2d::ClipNode* cNodeRow1;
	cocos2d::ClipNode* cNodeRow2;
	cocos2d::ClipNode* cNodeRow3;
	cocos2d::CCNode aqq;
	void registerStandardDelegate();
	//void selectSpriteForTouch(cocos2d::CCPoint* touchLocation);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void spawnBunnyMaybe(float dt);

	void DemoParticleFromFile(int x, int y);
	
};

#endif  // __HELLOWORLD_SCENE_H__