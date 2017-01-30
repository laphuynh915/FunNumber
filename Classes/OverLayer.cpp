#include "OverLayer.h"

// on "init" you need to initialize your instance
bool OverLayer::init()
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
	//Background gameover
	auto overPanel = Sprite::create("Popup.png");
	overPanel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 3) * 2));
	
	this->addChild(overPanel);

	//Score
	//Tạo LabelTTF
	_scoreLabel = Label::createWithTTF("0", "fonts/Square.ttf", 80);
	_scoreLabel->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() + overPanel->getContentSize().height / 4);

	this->addChild(_scoreLabel);

	_highScoreLabel = Label::createWithTTF("0", "fonts/Square.ttf", 20);
	_highScoreLabel->setPosition(origin.x + visibleSize.width / 2, _scoreLabel->getPositionY() - _highScoreLabel->getContentSize().height - 30);

	this->addChild(_highScoreLabel);

	//Button
	auto menuBtn = MenuItemImage::create("MenuBtn.png", "MenuBtnSelected.png", CC_CALLBACK_0(OverLayer::gotoMenuScene, this));
	auto replayBtn = MenuItemImage::create("AgainBtn.png", "AgainBtnSelected.png", CC_CALLBACK_0(OverLayer::gotoPlayScene, this));

	auto menu = Menu::create(menuBtn, replayBtn, nullptr);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() - overPanel->getContentSize().height / 2 + menuBtn->getContentSize().height);

	this->addChild(menu);
    
    return true;
}

void OverLayer::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, menuscene));
}

void OverLayer::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}
void OverLayer::setScore(int score)
{
	_score = score;

	auto userdefault = UserDefault::getInstance();
	auto highscore = userdefault->getIntegerForKey("HIGHSCORE", 0);

	if (_score > highscore)
	{
		highscore = _score;
		userdefault->setIntegerForKey("HIGHSCORE", highscore);
	}

	userdefault->flush();

	_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	_highScoreLabel->setString(String::createWithFormat("HIGH SCORE: %d", highscore)->getCString());
}