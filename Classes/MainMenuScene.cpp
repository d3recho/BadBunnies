#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "GameManager.h" 
#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene* MainMenu::scene() {
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainMenu *layer = MainMenu::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
	return scene;
}

bool MainMenu::init() {
	// Init super first
	if ( !CCLayer::init() ) {
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* pScoreLabel = CCLabelTTF::create("Score: 0 / 10", "Arial", 24);
	pScoreLabel->setPosition(ccp(size.width / 2, size.height - 50));
	this->addChild(pScoreLabel, 1);


	// Create game buttons
	CCMenuItemFont* pStartButton1 = CCMenuItemFont::create(
		"Easy", this, menu_selector(MainMenu::mainMenuStartCallback));
	pStartButton1->setFontSizeObj(50);
	pStartButton1->setPosition(ccp(size.width / 2, size.height / 5 * 4));
	pStartButton1->setTag(1);

	CCMenuItemFont* pStartButton2 = CCMenuItemFont::create(
		"Medium", this, menu_selector(MainMenu::mainMenuStartCallback));
	pStartButton2->setFontSizeObj(50);
	pStartButton2->setPosition(ccp(size.width / 2, size.height / 5 * 3));
	pStartButton2->setTag(2);

	CCMenuItemFont* pStartButton3 = CCMenuItemFont::create(
		"Hard", this, menu_selector(MainMenu::mainMenuStartCallback));
	pStartButton3->setFontSizeObj(50);
	pStartButton3->setPosition(ccp(size.width / 2, size.height / 5 * 2));
	pStartButton3->setTag(3);

	CCMenuItemFont* pStartButton4 = CCMenuItemFont::create(
		"Krazyy", this, menu_selector(MainMenu::mainMenuStartCallback));
	pStartButton4->setFontSizeObj(50);
	pStartButton4->setPosition(ccp(size.width / 2, size.height / 5 * 1));
	pStartButton4->setTag(4);

	CCMenu* pMenu = CCMenu::create(pStartButton1, pStartButton2, pStartButton3, pStartButton4, NULL);
	pMenu->setPosition(CCPointZero);	
	this->addChild(pMenu, 1);
	
	return true;
}

void MainMenu::mainMenuStartCallback(CCObject* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/LargeThumpOrBump.wav", false);
	CCMenuItemFont* mi = (CCMenuItemFont *)pSender;
	GameManager* gm = GameManager::sharedGameManager();
	gm->setGameDifficulty(mi->getTag());
	
	CCScene *pScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

MainMenu::MainMenu(void)
{
}


MainMenu::~MainMenu(void)
{
}
