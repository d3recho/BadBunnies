#include "EndGameScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene* EndGame::scene() {
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        EndGame *layer = EndGame::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
	return scene;
}

bool EndGame::init() {
	// Init super first
	if ( !CCLayer::init() ) {
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* pSprite = CCSprite::create("sketch-granny.png");
	pSprite->setPosition(ccp(size.width/2, size.height/2+26));
	this->addChild(pSprite, 1);

	CCLabelTTF* pScoreLabel = CCLabelTTF::create("You have finished the game!!", "Arial", 24);
	pScoreLabel->setPosition(ccp(size.width / 2, size.height - 50));


	// Create Restart game button
	CCMenuItemFont* pStartButton = CCMenuItemFont::create(
		"Restart game", 
		this, 
		menu_selector(EndGame::endGameStartCallback));

	pStartButton->setFontSizeObj(50);
	pStartButton->setColor(ccc3(0,255,0));
	pStartButton->setPosition(ccp(size.width / 2, size.height / 2));
	CCMenu* pMenu = CCMenu::create(pStartButton, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	
	return true;
}

void EndGame::endGameStartCallback(CCObject* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/LargeThumpOrBump.wav", false);
	CCScene *pScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

EndGame::EndGame(void)
{
}


EndGame::~EndGame(void)
{
}
