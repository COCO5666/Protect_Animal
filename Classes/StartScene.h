#pragma once
//#include "e:\cocosproject\hero\hero\cocos2d\cocos\2d\cclayer.h"
#include "cocos2d.h"
using namespace cocos2d;

class StartScene : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
	void start();
	void setLayer();
	void helpLayer();
	//void startAnimate();
	void helpBack();
	void setMusic(Ref* sender);//Ref����������ĸ���
	void setBack();
	void setEffect(Ref* sender);
	void adjustVolumn(Ref * sender); //��������

private:
	Size size;
	Sprite* helpSp;
	Menu* menu;
	Sprite* setBg;
};


