#pragma once
//#include "e:\cocosproject\hero\hero\cocos2d\cocos\2d\cclayer.h"
#include "cocos2d.h"
using namespace cocos2d;

class Loading : public Layer
{
public:
	static Scene * createScene();//������������̬���෽����
    virtual bool init();//���캯�����̳��Ը��࣬virtual�麯����

	//����layer���궨�塣���洫�Ĳ����ǵ�ǰ��������
	CREATE_FUNC(Loading);

	void startScene();
};
