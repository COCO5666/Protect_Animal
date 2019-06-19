#include "StartScene.h"
#include "ui/CocosGUI.h"
using namespace ui;
#include "SimpleAudioEngine.h"
#include "Level.h"
using namespace CocosDenshion;

//��������scene�Ͳ�layer
Scene* StartScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = StartScene::create();
	scene->addChild(layer); //������ص�������
	return scene; //����һ������ĳ���
}
bool StartScene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	
	//Director������������Ϸֻ��һ�������ڿ�����Ϸ
	size = Director::getInstance()->getWinSize();


	Sprite* bg = Sprite::create("bg2.png");
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	//��������ʼ��Ϸ����Ϸ���ú���Ϸ�����������˵�ѡ���ͼƬ����Item��
	auto startButton = MenuItemImage::create("play.png","play.png",CC_CALLBACK_0(StartScene::start,this));
	startButton->setPosition(Vec2(size.width/2,size.height/2+70));
	auto setButton = MenuItemImage::create("set.png","set.png",CC_CALLBACK_0(StartScene::setLayer,this));
	setButton->setPosition(Vec2(size.width/2,size.height/2-50));
	auto helpButton = MenuItemImage::create("help.png","help.png",CC_CALLBACK_0(StartScene::helpLayer,this));
	helpButton->setPosition(Vec2(size.width/2,size.height/2-150));

	//�����˵��������洴���������˵�����ӵ��˵���
	menu = Menu::create(startButton,setButton,helpButton,NULL);
	menu->setPosition(Vec2::ZERO);
	//�Ѳ˵���ӵ���ǰ����
	this->addChild(menu);

	//��Ӳ����ź�������Ķ���
	//startAnimate();

	//�ڵ�ǰ�������ѩ��Ʈ�������Ч��
	auto snow = ParticleSnow::create();
	snow->setPosition(Vec2(size.width/2,size.height));
	this->addChild(snow);

	//�������֣�ǰ�����ͷ�ļ��������ռ䣬�Ǹ�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.mp3");
	
	return true;
}
//����ʼ��Ϸ���˵��Ļص�������������ɽ���ѡ���ɫѡ��ؿ�����
void StartScene::start( )
{
	log("start");
	Scene *scene=SelectLevel::createScene();
	Director::getInstance()->replaceScene(scene);
}
//���ò˵��Ļص�������������ӱ������ֺ�������С�Ŀ��ƺ�ok��ť
void StartScene::setLayer( )
{
	//����ص�����Ҫ��ԭ���Ĳ˵�������
	menu->setEnabled(false);
	
	//����������
	setBg = Sprite::create("mianban.png");
	setBg->setPosition(Vec2(size.width/2,100));
	this->addChild(setBg);

	//���ֿ��ƵĿ��ز˵�
	auto onMusic = MenuItemImage::create("duihao1.png","duihao1.png");
	auto offMusic = MenuItemImage::create("duihao2.png","duihao2.png");
	//auto Music = MenuItemToggle::create(onMusic);
	//Music->addSubItem(offMusic);
	//Music->setCallback(CC_CALLBACK_1(StartScene::setMusic,this));
	
	auto Music=MenuItemToggle::createWithCallback(CC_CALLBACK_1(StartScene::setMusic,this),onMusic,offMusic,NULL);

	
	Music->setPosition(Vec2(setBg->getContentSize().width/2,setBg->getContentSize().height/2+100));
	auto menu = Menu::create(Music,NULL);
	menu->setPosition(Vec2::ZERO);

	setBg->addChild(menu);

	//okButton
	//Button*okButton = Button::create("ok.png","ok.png","ok.png");
	Button*okButton = Button::create("ok.png","ok.png");
	okButton->addClickEventListener(CC_CALLBACK_0(StartScene::setBack,this));
	okButton->setPosition(Vec2(setBg->getContentSize().width/2,100));
	setBg->addChild(okButton);

	//���Ժš��˵�ǰ���Music��ǩMusic
	Label* MusicLabel = Label::createWithSystemFont("Music","",30);
	MusicLabel->setColor(Color3B::BLUE);
	MusicLabel->setPosition(Vec2(setBg->getContentSize().width/2-100,setBg->getContentSize().height/2+100));
	setBg->addChild(MusicLabel);

	////��Ч���ƿ��ز˵�
	//auto onEffect = MenuItemImage::create("duihao1.png","duihao1.png");
	//auto offEffect = MenuItemImage::create("duihao2.png","duihao2.png");
	//auto Effect = MenuItemToggle::create(onEffect);
	//Effect->addSubItem(offEffect);
	////�����������������滻auto Effect = MenuItemToggle::create(onEffect��offEffect��NULL);
	//Effect->setCallback(CC_CALLBACK_1(StartScene::setEffect,this));
	//Effect->setPosition(Vec2(setBg->getContentSize().width/2+150,setBg->getContentSize().height/2+100));
	//auto menu2 = Menu::create(Effect,NULL);
	//menu2->setPosition(Vec2::ZERO);
	//setBg->addChild(menu2);

	////���Ժš��˵�ǰ��ı�ǩEffect
	//Label* EffectLable = Label::createWithSystemFont("Effect","",30);
	//EffectLable->setColor(Color3B::BLUE);
	//EffectLable->setPosition(Vec2(setBg->getContentSize().width/2+60,setBg->getContentSize().height/2+100));
	//setBg->addChild(EffectLable);

	//��ӻ�����
	auto slider=Slider::create();
	slider->loadBarTexture("SliderBar.png");
	slider->loadSlidBallTextures("aaa.png","aaa.png","aaa.png");
	slider->setPosition(Vec2(setBg->getContentSize().width/2,setBg->getContentSize().height/2));
	slider->setScale9Enabled(true);
	slider->setContentSize(Size(Vec2(300,40)));
	slider->setPercent(50);
	slider->addEventListener(CC_CALLBACK_1(StartScene::adjustVolumn,this)); //�������ļ����ص���ʱ�̼�⻬������ֵ�øı�
	setBg->addChild(slider);
	//��������ý������ݺ�������100��λ���ƶ������������
	MoveTo* moveTo = MoveTo::create(0.5,Vec2(size.width/2,size.height/2));
	setBg->runAction(moveTo);
}
//��������
void StartScene::adjustVolumn(Ref * sender)
{
	Slider *slider=(Slider *)sender;
	log("%d",slider->getPercent());
	//��������ֵΪ0-100֮������������������õ�ֵ��0-1֮�䡣����Ҫ����100.
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(slider->getPercent()/100);
}

//Ref���������һ������
void StartScene::setBack( )
{
	//������ ȷ�� ��ť
	menu->setEnabled(true);
	setBg->removeFromParent();
}
//�������ֵĿ���״̬���������ֵĲ��ź���ͣ
void StartScene::setMusic(Ref* sender)
{
	MenuItemToggle *toggle=(MenuItemToggle *)sender;
	//��ȡ�˵�����±꣨0--off�� 1--on��
	if(toggle->getSelectedIndex( )==1)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}
//������Ч�Ŀ���״̬���������״̬��ŵ�����UserDefault.xml�ļ��У��Ա���Ҫʱ������Ч��
//void StartScene::setEffect(Ref* sender)
//{
//	MenuItemToggle *toggle=(MenuItemToggle *)sender;
//	if(toggle->getSelectedIndex( )==1 )
//	{
//		/*���ڱ�������ݣ���Ҫ�浽json��xml�ļ�����ʱ����Ŀɴ浽����userdefault.xml�ļ��У�
//		���ﱣ����ʱ����Ч״̬���´�������Ϸʱ����������޹�
//		*/
//		UserDefault::getInstance()->setBoolForKey("onEffect",true);
//	}
//	else
//	{
//		UserDefault::getInstance()->setBoolForKey("onEffect",false);
//	}
//}
//��Ϸ������ť�Ļص�
void StartScene::helpLayer()
{
	//�ص�menu�ĵ���¼���false���ɵ����
	menu->setEnabled(false);

	//�������棬�Ѱ������ľ���ӵ���Ϸ���ò��ϣ�
	helpSp = Sprite::create("help_mianban.png");
	helpSp->setPosition(Vec2(size.width/2,size.height/2-200));
	this->addChild(helpSp);

	//�ڰ����㣬����Button����Ҫ����ͼƬ��
	Button* okButton = Button::create("ok.png","ok.png");

	//Button�ļ������������button��ť�ͷ��ص���Ϸ���ý���
	okButton->addClickEventListener(CC_CALLBACK_0(StartScene::helpBack,this));
	okButton->setPosition(Vec2(helpSp->getContentSize().width/2,100));
	
	//��button��ť��ӵ�������徫���ϡ�
	helpSp->addChild(okButton);

	//���������0.8���ڴ�������100��λ���ƶ���������м�λ�á�
	auto moveTo = MoveTo::create(0.5,Vec2(size.width/2,size.height/2));
	helpSp->runAction(moveTo);
}
//���������е�ok��ť�Ļص�����������򷵻ص���Ϸ���ý���
void StartScene::helpBack()
{
	//menu����¼�������true��������¼���
	menu->setEnabled(true);

	//�Ѱ�������Ӹ���ͼ���Ƴ����򷵻ص���Ϸ���ý���
	helpSp->removeFromParent();
}
