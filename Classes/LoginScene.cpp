#include "LoginScene.h"
#include "AnimationUtil.h"
#include "ResourceName.h"
#include "RegisterScene.h"
#include "MainView.h"

LoginScene::LoginScene()
{

}
LoginScene::~LoginScene()
{
	TextureCache::getInstance()->removeTextureForKey(M_LOGIN_BG);
	TextureCache::getInstance()->removeTextureForKey(M_LOGIN_BTN_DOWN);
	TextureCache::getInstance()->removeTextureForKey(M_LOGIN_BTN_UP);
	TextureCache::getInstance()->removeTextureForKey(M_CHUANGJIAN_UP);
	TextureCache::getInstance()->removeTextureForKey(M_CHUANGJIAN_DOWN);
	ccDrawFree();
	/* DrawPrimitives::free();*/
}

Scene* LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
 	auto mainLayer = MainView::create();
 	scene->addChild(mainLayer);
	mainLayer->setTag(10001);
	layer->setTag(10002);
	scene->addChild(layer,1);
	return scene;
}
bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto frameCache1 = SpriteFrameCache::getInstance();
	frameCache1->addSpriteFramesWithFile("rest.plist", "rest.png");

	auto action1 = Animate::create(AnimationUtil::createWithSingleFrameName("ZS1_0",0.1f,-1));
	auto sp1 = Sprite::create();
	sp1->setFlipX(true);
	sp1->runAction(RepeatForever::create(action1));
	sp1->setPosition(Point(200, 200));
	this->addChild(sp1, 99999);
	frameCache1->removeSpriteFrames();

	auto frameCache2 = SpriteFrameCache::getInstance();
	frameCache2->addSpriteFramesWithFile("rest.plist", "rest.png");
	auto action2 = Animate::create(AnimationUtil::createWithSingleFrameName("ZS1_0", 0.1f, -1));

	auto sp2 = Sprite::create();
	sp2->setPosition(Point(100, 100));
	sp2->runAction(RepeatForever::create(action2));
	this->addChild(sp2, 99999);
	frameCache2->removeSpriteFrames();

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoginScene::socketError), "socketError", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoginScene::loginMenuCallBack), "loginMessage", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoginScene::loadUI), "loadingremove", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoginScene::receiveMainScene), "petsInfo", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoginScene::personalBack), "personMessage", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoginScene::registermoveback), "registermove", NULL);
	
	m_pLoading = LoadingLayer::create();
	this->addChild(m_pLoading, 999);
	m_vResourceArray.push_back(M_LOGIN_BG);
	m_vResourceArray.push_back(M_LOGIN_BTN_UP);
	m_vResourceArray.push_back(M_LOGIN_BTN_DOWN);
	m_vResourceArray.push_back(M_CHUANGJIAN_UP);
	m_vResourceArray.push_back(M_CHUANGJIAN_DOWN);
	m_vResourceArray.push_back(M_REGISTER_BTN_UP);
	m_vResourceArray.push_back(M_REGISTER_BTN_DOWN);
	m_vResourceArray.push_back(M_REGISTER_BOUNDER);
	m_vResourceArray.push_back(M_MAINVIEW_BG);
	m_vResourceArray.push_back(M_MVDRAG_BG);
	m_vResourceArray.push_back(M_KZBTN_UP);
	m_vResourceArray.push_back(M_KZBTN_DOWN);
	m_vResourceArray.push_back(M_TDBTN_UP);
	m_vResourceArray.push_back(M_TDBTN_DOWN);
	m_vResourceArray.push_back(M_QHBTN_UP);
	m_vResourceArray.push_back(M_QHBTN_DOWN);
	m_vResourceArray.push_back(M_FLBTN_UP);
	m_vResourceArray.push_back(M_FLBTN_DOWN);
	m_pLoading->addImage(m_vResourceArray, this);
	setTouchEnabled(true);

	//²ãÍÌÊÉÊÂ¼þ,·ÀÖ¹µÇÂ¼½çÃæµã»÷·Ç×¢²á,µÇÂ¼°´Å¥,´¥·¢MainView²ãÊÂ¼þ
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void LoginScene::loadUI(Ref* pData)
{
	if (pData == this)
	{
		NotificationCenter::getInstance()->removeObserver(this, "loadingremove");
	}
	else
	{
		return;
	}

	g_cSize = Director::getInstance()->getWinSize();
	//setTouchEnabled(true);
	//m_bRegisterBtn = false;
	/*ÍøÂçÄ£¿éÔÝÊ±×¢ÊÍ
	g_pSocket = new SocketClient(ip, ports, 1, 1, NULL);//146
	g_pSocket->start();
	GameData::shareGameData()->socket = g_pSocket;
	CCLog("%s  %s", CCUserDefault::sharedUserDefault()->getStringForKey("password").c_str(), CCUserDefault::sharedUserDefault()->getStringForKey("user").c_str());
	CCLog("^^^^^^^^^^^%d  %d", !strcmp(CCUserDefault::sharedUserDefault()->getStringForKey("password").c_str(), ""), !strcmp(CCUserDefault::sharedUserDefault()->getStringForKey("user").c_str(), ""));
	*/
	//if (!strcmp(UserDefault::getInstance()->getStringForKey("password").c_str(), "") ||
	//	!strcmp(UserDefault::getInstance()->getStringForKey("user").c_str(), "")) 
	//{
		//addRegisterLayer();
	//}
	//else
	//{
		//MessageManager::shareMessageManager()->sendLoginMessage();
	//}

	auto pNodeBgSprite = Sprite::create(M_LOGIN_BG);
	pNodeBgSprite->setPosition(Point(g_cSize.width/2, g_cSize.height/2));
	auto pNodeLoginBtn = MenuItemImage::create(M_LOGIN_BTN_UP, M_LOGIN_BTN_DOWN, this, menu_selector(LoginScene::loginMenuCallBack));
	auto pNodeRegistBtn = MenuItemImage::create(M_CHUANGJIAN_UP, M_CHUANGJIAN_DOWN, this, menu_selector(LoginScene::registerMenuCallBack));
	pNodeLoginBtn->setAnchorPoint(Point(1, 0));
	pNodeRegistBtn->setAnchorPoint(Vec2::ZERO);

	m_pLoginMenu = Menu::create(pNodeLoginBtn, NULL);
	m_pLoginMenu->setAnchorPoint(Vec2::ZERO);
	m_pRegisterMenu = Menu::create(pNodeRegistBtn, NULL);
	m_pRegisterMenu->setAnchorPoint(Vec2::ZERO);

	m_pLoginMenu->setPosition(Point(g_cSize.width, g_cSize.height / 2 - 100));
	m_pRegisterMenu->setPosition(Point(0, g_cSize.height / 2 + 140));
	this->addChild(pNodeBgSprite);
	this->addChild(m_pLoginMenu);
	this->addChild(m_pRegisterMenu);
	setTouchEnabled(true);

	/*
	auto listener = EventListenerTouchOneByOne::create();
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	listener->onTouchBegan = CC_CALLBACK_2(LoginScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LoginScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LoginScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	*/

}
void LoginScene::addLoginLayer()
{

	m_pLoadLayer = (MainView*)Director::getInstance()->getRunningScene()->getChildByTag(10001);
	((MainView*)m_pLoadLayer)->setCoin();
	((MainView *)m_pLoadLayer)->setRole();
	((MainView *)m_pLoadLayer)->intensifLayer->setVisible(true);
	m_pLoadLayer->setTouchEnabled(false);
	this->removeFromParentAndCleanup(true);
}
void LoginScene::addRegisterLayer( )
{
	auto pNodeRegister = RegisterScene::create();
	pNodeRegister->setPosition(Vec2::ZERO);
	//pNodeRegister->addObject(this);
	this->addChild(pNodeRegister, 50);
}
void LoginScene::socketError(Ref* pData)
{

}
void LoginScene::loginMenuCallBack(Ref* pData)
{
	m_pLoginMenu->setScale(1);
	addLoginLayer();
}
void LoginScene::receiveMainScene(Ref* pData)
{

}
void LoginScene::personalBack(Ref* pData)
{

}


void LoginScene::registerMenuCallBack(Ref *pSender)
{
	m_pRegisterMenu->setScale(1);
	addRegisterLayer();
}
void LoginScene::registermoveback(Ref *pData)
{
	NotificationCenter::getInstance()->removeObserver(this, "registermove");
}
/*
bool LoginScene::TouchBegan(Touch* touch, Event* event)
{
	log("11111");
	
	if (m_bLoginFlag || m_bRegisterBtn)
	{
		return false;
	}

	g_fGap = touch->getLocation().x - m_pLoginMenu->boundingBox().origin.x;
	m_bLoginFlag = m_pLoginMenu->onTouchBegan(touch, event);
	if (m_pLoginMenu)
	{
		m_pLoginMenu->setScale(1.1);
		m_pLoadLayer = (MainView*)Director::getInstance()->getRunningScene()->getChildByTag(10001);
		((MainView*)m_pLoadLayer)->setCoin();
		m_pLoadLayer->setTouchEnabled(false);
	}

	m_beginPoint = touch->getLocation();
	g_fDis = m_oldPoint.x - m_beginPoint.x;
	m_bRegisterBtn = m_pRegisterMenu->onTouchBegan(touch, event);
	if (m_bRegisterBtn) {
		m_pRegisterMenu->setScale(1.1);
	}
	return true;
}
void LoginScene::TouchMoved(Touch* touch, Event* event)
{
	if (m_bLoginFlag) {
		m_pLoginMenu->onTouchMoved(touch, event);
		this->setPosition(Point(touch->getLocation().x - g_fGap - g_cSize.width, 0));
		((MainView *)m_pLoadLayer)->color->setOpacity(GLubyte(150 - ((abs(touch->getLocation().x - g_cSize.width) / g_cSize.width) * 150)));
		m_pLoadLayer->setScaleY(0.95 + (abs(touch->getLocation().x - g_cSize.width) / g_cSize.width)*0.05);
	}
	if (m_bRegisterBtn) {
		m_pRegisterMenu->onTouchMoved(touch, event);
	}
}
void LoginScene::TouchEnded(Touch* touch, Event* event)
{
	if (m_bLoginFlag) {
		m_pLoginMenu->onTouchEnded(touch, event);
		m_bLoginFlag = false;
		LayerEaseIn(this);
		m_oldPoint = touch->getLocation();
		m_pLoginMenu->setScale(1);
	}
	if (m_bRegisterBtn) {
		m_bRegisterBtn = false;
		m_pRegisterMenu->setScale(1);
		m_pRegisterMenu->onTouchEnded(touch, event);
	}
}

void LoginScene::LayerEaseIn(Node * Layersender)
{
	if (Layersender->getPosition().x < (-g_cSize.width / 2)) {
		MoveTo *move = MoveTo::create(0.3, ccp(-g_cSize.width, 0));
		EaseIn *easein = EaseIn::create(move, 1);
		CallFunc *func = CallFunc::create(this, callfunc_selector(LoginScene::mainScene));
		Sequence *actions = Sequence::create(easein, NULL);
		Layersender->runAction(actions);
		MoveTo *menu_Move = MoveTo::create(0.3, ccp(-g_cSize.width, g_cSize.height / 2 - 100));
		EaseIn *menu_EaseIn = EaseIn::create(menu_Move, 1);
		DelayTime *delay = DelayTime::create(0.5);
		Sequence *menu_Seq = Sequence::create(menu_EaseIn, delay, func, NULL);
		ScaleTo *scale = ScaleTo::create(0.3, 1, 1);
		FadeTo *fade = FadeTo::create(0.3, GLubyte(0));
		((MainView *)m_pLoadLayer)->color->runAction(fade);
		m_pLoadLayer->runAction(scale);
		m_pLoginMenu->runAction(menu_Seq);
		m_pLoadLayer->setTouchEnabled(true);
	}
	else if (Layersender->getPosition().x > (-g_cSize.width / 2)) {
		MoveTo *move = MoveTo::create(0.3, Vec2::ZERO);
		EaseIn *easein = EaseIn::create(move, 1);
		Layersender->runAction(easein);
		ScaleTo *scale = ScaleTo::create(0.3, 1, 0.95);
		FadeTo *fade = FadeTo::create(0.3, GLubyte(150));
		((MainView *)m_pLoadLayer)->color->runAction(fade);
		m_pLoadLayer->runAction(scale);
		MoveAndEase(ccp(g_cSize.width, g_cSize.height / 2 - 100), m_pLoginMenu);
	}
}

void LoginScene::mainScene()
{
	((MainView *)m_pLoadLayer)->setRole();
	((MainView *)m_pLoadLayer)->intensifLayer->setVisible(true);
	m_pLoadLayer->setTouchEnabled(true);
	this->removeFromParentAndCleanup(true);
}
void LoginScene::MoveAndEase(Point pos, Node * sender)
{
	MoveTo *menu_Move = MoveTo::create(0.3, pos);
	EaseIn *menu_EaseIn = EaseIn::create(menu_Move, 1);

	Sequence *menu_Seq = Sequence::create(menu_EaseIn, NULL);
	sender->runAction(menu_Seq);

}

void LoginScene::onExit()
{
	Layer::onExit();
}*/