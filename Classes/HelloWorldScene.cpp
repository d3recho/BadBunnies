#include "HelloWorldScene.h"
#include "EndGameScene.h"
#include "ClipNode.h"
#include "GameManager.h" 
#include "ctime"
#include "SimpleAudioEngine.h"

#define CCCA(x)   (x->copy()->autorelease())

using namespace cocos2d;


BunnyHoles::BunnyHoles() {
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	for (int col = 0; col < 3; col++) {
		for (int row = 0; row < 3; row++) {
			isUnused[col][row] = true;
			position[col][row] = ccp(size.width/3 * (col) + (size.width/3)/2, size.height/4 * (row + 0.75));

			pBackHole[col][row] = CCSprite::create("hole_backsoil2.png");
			pBackHole[col][row]->setAnchorPoint(ccp(0.5f, 0.0f));
			pBackHole[col][row]->setPosition(position[col][row]);

			pFrontHole[col][row] = CCSprite::create("hole_frontsoil2.png");
			pFrontHole[col][row]->setAnchorPoint(ccp(0.5f, 0.0f));
			pFrontHole[col][row]->setPosition(position[col][row]);
		}
	}
}

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCLayer::init());

		// Salt the rand function
		srand((unsigned)time(0));

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		pBunnyArray = new CCArray;

        // 1. Add a menu item with "X" image, which is clicked to quit the program.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        pCloseItem->setPosition(ccp(size.width - 20, 20));
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);	// Create a menu with the "close" menu item, it's an auto release object.
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 20);


		// 2. Add a label 
		pScoreLabel = CCLabelTTF::create("Score: 0 / 10", "Arial", 24);
        CC_BREAK_IF(! pScoreLabel );
		pScoreLabel->setPosition(ccp(size.width / 2, size.height - 50));
        this->addChild(pScoreLabel, 20);

        // 3. Add background 
        CCSprite* pSprite = CCSprite::create("grass2.png");
        CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(size.width/2, size.height/2 + 26));
        this->addChild(pSprite, 10);

		// 4. Add bunny hole sprites
		bunnyHoles = new BunnyHoles();
		for (int col = 0; col < 3; col++) {
			for (int row = 0; row < 3; row++) {
				addChild(bunnyHoles->pBackHole[col][row], 20);
				addChild(bunnyHoles->pFrontHole[col][row], 40);
			}
		}

		// 5. Add ClipNodes, one needed for each Row 
		cNodeRow1 = new ClipNode();
		cNodeRow1->autorelease();
		cNodeRow1->setClipsToBounds(true);
		cNodeRow1->setPosition(ccp(0, 0));
		cNodeRow1->setClippingRegion(CCRect(0, bunnyHoles->position[0][0].y + 12, size.width, 220));
		addChild(cNodeRow1, 30);

		cNodeRow2 = new ClipNode();
		cNodeRow2->autorelease();
		cNodeRow2->setClipsToBounds(true);
		cNodeRow2->setPosition(ccp(0, 0));
		cNodeRow2->setClippingRegion(CCRect(0, bunnyHoles->position[0][1].y + 12, size.width, 220));
		addChild(cNodeRow2, 30);
		
		cNodeRow3 = new ClipNode();
		cNodeRow3->autorelease();
		cNodeRow3->setClipsToBounds(true);
		cNodeRow3->setPosition(ccp(0, 0));
		cNodeRow3->setClippingRegion(CCRect(0, bunnyHoles->position[0][2].y + 12, size.width, 220));
		addChild(cNodeRow3, 30);

//		tmpSprite = CCSprite::create("evaluate.png");
//		tmpSprite->setPosition(ccp(size.width/2, size.height/2+26));
//		cNodeRow1->addChild(tmpSprite);
		
		// 6. set variables based on difficulty level
		GameManager* gm = GameManager::sharedGameManager();

		fMultiplier	= 0.4f;
		switch(gm->getGameDifficulty()) {
		case 2 :
			fSpawnSpeed		=	0.7f;
			fUpSpeed		=	1.0f;
			fDownSpeed		=	fUpSpeed / 2;
			fDelay			=	0.2f;
			fFloatPeriod	=	0.25f;
			break;
		case 3 :
			fSpawnSpeed		=	0.5f;
			fUpSpeed		=	0.5f;
			fDownSpeed		=	fUpSpeed / 2;
			fDelay			=	0.1f;
			fFloatPeriod	=	0.3f;
			break;
		case 4 :
			fSpawnSpeed		=	0.3f;
			fUpSpeed		=	0.2f;
			fDownSpeed		=	fUpSpeed / 2;
			fDelay			=	0.01f;
			fFloatPeriod	=	0.2f;
			break;
		default :
			fSpawnSpeed		=	1.0f;
			fUpSpeed		=	1.5f;
			fDownSpeed		=	fUpSpeed / 2;
			fDelay			=	0.25f;
			fFloatPeriod	=	0.25f;
		}



		// Repetetive scheduler to spawn bunnies
		this->schedule(schedule_selector(HelloWorld::spawnBunnyMaybe), fSpawnSpeed);

		// Make touchable
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

		
		pTotalScore = 0;



        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

void HelloWorld::spawnBunnyMaybe(float dt) {
	int pRndCol = (rand() % 3);
	int pRndRow = (rand() % 3);
	if (bunnyHoles->isUnused[pRndCol][pRndRow]) {
		bunnyHoles->isUnused[pRndCol][pRndRow] = false;
		Bunny* bunny = new Bunny(pRndCol, pRndRow, bunnyHoles->position[pRndCol][pRndRow]);
		HelloWorld::pBunnyArray->addObject(bunny);

		switch(pRndRow) {
		case 0 : 
			cNodeRow1->addChild(bunny); break;
		case 1 : 
			cNodeRow2->addChild(bunny); break;
		case 2 : 
			cNodeRow3->addChild(bunny); break;
		}
		
		HelloWorld::actionBunnyMove(bunny);
	}
}

void HelloWorld::actionBunnyMove(Bunny* bunny) {
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	t_fUpSpeed		=	fUpSpeed + fMultiplier * (rand() % 2 );
	t_fDownSpeed	=	t_fUpSpeed / 2;
	t_fDelay		=	fDelay + fMultiplier * (rand() % 2 );
	t_fFloatPeriod	=	fFloatPeriod + fMultiplier * (rand() % 2 );
	
	CCActionInterval* move = CCMoveBy::create(t_fUpSpeed, ccp(0, bunny->boundingBox().size.height));
	CCActionInterval* move2 = CCMoveBy::create(t_fDownSpeed, ccp(0, -bunny->boundingBox().size.height));

	CCActionInterval* move_elastic_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()), t_fFloatPeriod);
	CCActionInterval* move_ease_in = CCEaseBackIn::create((CCActionInterval*)(move2->copy()->autorelease()));

	CCFiniteTimeAction* action_clear_bunny = CCCallFuncN::create( this, SEL_CallFuncN(&HelloWorld::clearBunny));

	CCDelayTime *delay = CCDelayTime::create(t_fDelay);
	CCFiniteTimeAction* sequence = CCSequence::create(move_elastic_out, CCCA(delay), move_ease_in, action_clear_bunny, NULL);
	sequence->setTag(TAG_action);

	bunny->runAction(sequence);
}

void HelloWorld::clearBunny(CCNode* sender) {
	Bunny* b = (Bunny *)sender;
	HelloWorld::pBunnyArray->removeObject(b, false);
	bunnyHoles->isUnused[b->col][b->row] = true;
	switch(b->row) {
		case 0 : 
			cNodeRow1->removeChild(b, true); break;
		case 1 : 
			cNodeRow2->removeChild(b, true); break;
		case 2 : 
			cNodeRow3->removeChild(b, true); break;
		}
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	CCObject* ib = NULL;
	CCARRAY_FOREACH(HelloWorld::pBunnyArray, ib) {
		Bunny* bb = dynamic_cast<Bunny*>(ib);	// Casting CCObject to Bunny obj
		if (bb->boundingBox().containsPoint(pTouch->getLocation())) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/SharpPunch.wav", false);
			DemoParticleFromFile(pTouch->getLocation().x, pTouch->getLocation().y);
			if (!bb->isBunnyHit) {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/FryingPanHit.wav", false);
				bb->isBunnyHit = true;
				updateScore(1);
				bb->setTexture(CCTextureCache::sharedTextureCache()->addImage("bunny_hit2.png"));
				break;
			}
		} else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/WoodWhack.wav");
		}
	}
	return true;
}

void HelloWorld::updateScore(int score) {
	pTotalScore += score;
	
	char scoreLabelText[30];
	snprintf(scoreLabelText, 30, "Score: %d / 10", pTotalScore);
	pScoreLabel->setString(scoreLabelText);
	if (pTotalScore >= 10)  {
		CCScene *pScene = EndGame::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}

}

void HelloWorld::DemoParticleFromFile(int x, int y) {
	CCParticleSystem* m_emitter = new CCParticleSystemQuad();
	std::string filename = "Particles/ExplodingRing.plist";
	m_emitter->initWithFile(filename.c_str());
    addChild(m_emitter, 100);
	m_emitter->setPosition( ccp(x, y) );

	CCDelayTime * delayAction = CCDelayTime::create( 0.5f );
	CCCallFuncN * callFunc = CCCallFuncN::create( this, callfuncN_selector( HelloWorld::clearParticle ));
	m_emitter -> runAction( CCSequence::createWithTwoActions( delayAction, callFunc ) );}

void HelloWorld::clearParticle(CCNode* sender) {
	CCParticleSystemQuad *particle = (CCParticleSystemQuad *)sender;
	this->removeChild(particle, true);
}
