#include "PlayScene.h"
#include "MenuScene.h"




Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B(random(1, 255), random(1, 255), random(1, 255), 255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	//
	_timer = 5.0f;
	_score = 0.0f;

	//Button
	auto trueBtn = MenuItemImage::create("TrueButton_Normal.png", "TrueButton_Selected.png", CC_CALLBACK_0(PlayScene::trueButtonClick, this));
	auto wrongBtn = MenuItemImage::create("WrongButton_Normal.png", "WrongButton_Selected.png", CC_CALLBACK_0(PlayScene::wrongBtnClick, this));

	_menu = Menu::create(wrongBtn, trueBtn, nullptr);
	_menu->alignItemsHorizontallyWithPadding(20.0f);
	_menu->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + trueBtn->getContentSize().height / 2 + 10));
	
	this->addChild(_menu);
    
	//MATH LABEL
	_mathStr = "";
	_mathLabel = Label::createWithTTF(_mathStr, "fonts/Square.ttf", 100);
	_mathLabel->setAlignment(TextHAlignment::CENTER);
	_mathLabel->setLineHeight(80);
	_mathLabel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 3) * 2));
	this->addChild(_mathLabel);

	//TIME LABEL
	_timeLabel = Label::createWithTTF(_mathStr, "fonts/Square.ttf", 40);
	_timeLabel->setAnchorPoint(Point(0.0f, 0.5f));
	_timeLabel->setPosition(Point(origin.x + 20, origin.y + visibleSize.height - 40));
	this->addChild(_timeLabel);

	//SCORE LABEL
	_scoreLabel = Label::createWithTTF("0", "fonts/Square.ttf", 40);
	_scoreLabel->setAnchorPoint(Point(1.0f, 0.5f));
	_scoreLabel->setPosition(Point(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 40));

	this->addChild(_scoreLabel);

	//Random Math
	randomMath();

	//Update
	this->scheduleUpdate();

    return true;
}

void PlayScene::update(float dt)
{
	_timer -= dt;
	_timeLabel->setString(String::createWithFormat("%.2f", _timer)->getCString());

	if (_timer < 0.0f)
	{
		_timer = 0.0f;
		_timeLabel->setString(String::createWithFormat("%.2f", _timer)->getCString());

		showOverLayer();
	}
}

void PlayScene::randomMath()
{
	int _firstNum = random(1, _score + 10);
	int _secondNum = random(1, _score + 10);			//Độ lệch/khó theo số điểm
	int _operator = random(0, 1);						//0 là trừ, 1 là cộng
	_result = random(0, 1);								//Kết quả random đúng hoặc sai

	switch (_operator)
	{
	case 1:
	{
		
		if (_result)
		{
			_mathStr = String::createWithFormat("%d + %d\n=%d", _firstNum, _secondNum, _firstNum + _secondNum)->getCString();
		}
		else
		{
			_mathStr = String::createWithFormat("%d + %d\n=%d", _firstNum, _secondNum, random(_firstNum, _firstNum + _secondNum - 1))->getCString();
		}
		break;
	}
	case 0:
	{
		if (_result)
		{
			_mathStr = String::createWithFormat("%d - %d\n= %d", _firstNum, _secondNum, _firstNum - _secondNum)->getCString();
		}
		else
		{
			_mathStr = String::createWithFormat("%d - %d\n=%d", _firstNum, _secondNum, random(_firstNum - _secondNum + 1, _firstNum + _secondNum))->getCString();
		}
		break;
	}
	default:
		break;
	}

	_mathLabel->setString(_mathStr);
}

void PlayScene::trueButtonClick()
{
	if (_result == true)
	{
		_timer = 5.0f;

		randomMath();

		_score++;
		_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	}
	else
	{
		showOverLayer();
	}
}

void PlayScene::wrongBtnClick()
{
	if (_result == false)
	{
		_timer = 5.0f;

		randomMath();

		_score++;
		_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	}
	else
	{
		showOverLayer();
	}
}

void PlayScene::showOverLayer()
{
	this->pause();
	_menu->setEnabled(false);

	auto overlayer = OverLayer::create();
	overlayer->setPosition(Point(0, 0));
	overlayer->setScore(_score);

	this->addChild(overlayer);
}
