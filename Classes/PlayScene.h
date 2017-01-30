#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "OverLayer.h"

USING_NS_CC;

class PlayScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void update(float dt);
    
    // implement the "static create()" method manually
	CREATE_FUNC(PlayScene);
private:
	std::string _mathStr;
	int _score;
	bool _result;
	float _timer;

	Label* _mathLabel;
	Label* _timeLabel;
	Label* _scoreLabel;
	Menu* _menu;

	void randomMath();
	void trueButtonClick();
	void wrongBtnClick();
	void showOverLayer();
};

#endif // __INTRO_SCENE_H__
