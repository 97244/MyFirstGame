#include "RegisterScene.h"
#include "ResourceName.h"
#include "CocoMessageBox.h"
bool RegisterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	NotificationCenter::getInstance()->addObserver(this,callfuncO_selector(RegisterScene::reciveRegisterMsg), "registerMessage", NULL);
	m_winSize = Director::getInstance()->getWinSize();
	Scale9Sprite * sp0 = Scale9Sprite::create();

	m_pEditBox0 = EditBox::create(CCSizeMake(500, 80), sp0);
	m_pEditBox0->setFontSize(30);
	m_pEditBox0->setReturnType(EditBox::KeyboardReturnType::DONE);
	m_pEditBox0->setInputFlag(EditBox::InputFlag::PASSWORD);
	m_pEditBox0->setPosition(Point(m_winSize.width / 2 - 130, m_winSize.height / 3 - 60));
	m_pEditBox0->setFontColor(Color3B::BLACK);
	m_pEditBox0->setText("");
	this->addChild(m_pEditBox0, 1);

	Scale9Sprite *sp1 = Scale9Sprite::create();
	m_pEditBox1 = EditBox::create(CCSizeMake(500, 80), sp1);
	m_pEditBox1->setFontSize(30);
	m_pEditBox1->setReturnType(EditBox::KeyboardReturnType::DONE);
	m_pEditBox1->setInputFlag(EditBox::InputFlag::PASSWORD);
	m_pEditBox1->setPosition(ccp(m_winSize.width / 2 - 130, m_winSize.height / 2 - 130));
	m_pEditBox1->setFontColor(Color3B::BLACK);
	m_pEditBox1->setText("");
	this->addChild(m_pEditBox1, 1);

	Scale9Sprite *sp2 = Scale9Sprite::create();
	m_pEditBox2 = EditBox::create(CCSizeMake(500, 80), sp2);
	m_pEditBox2->setFontSize(30);
	m_pEditBox2->setReturnType(EditBox::KeyboardReturnType::DONE);
	m_pEditBox2->setPosition(ccp(m_winSize.width / 2 - 130, m_winSize.height / 2));
	m_pEditBox2->setFontColor(Color3B::BLACK);
	m_pEditBox2->setText("");
	this->addChild(m_pEditBox2, 1);

	btnIsRuning = false;
	auto m_bg = Sprite::create(M_REGISTER_BG);
	m_bg->setAnchorPoint(Vec2::ZERO);
	m_bg->setPosition(Vec2::ZERO);
	this->addChild(m_bg);

	auto m_bg_bound = Sprite::create(M_REGISTER_BOUNDER);
	m_bg_bound->setAnchorPoint(Vec2::ZERO);
	m_bg_bound->setPosition(Point(80, 50));
	m_bg->addChild(m_bg_bound);

	//setTouchEnabled(true);

	auto m_btn_register = MenuItemImage::create(M_REGISTER_BTN_UP, M_REGISTER_BTN_DOWN);
	m_pBtnMenu = Menu::create(m_btn_register, NULL);

	oldPos = Point(320, 170);
	m_pBtnMenu->setAnchorPoint(Vec2::ZERO);
	m_pBtnMenu->setPosition(oldPos);
	this->addChild(m_pBtnMenu);
	m_pBtnMenu->setTouchEnabled(true);
	setTouchEnabled(true);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event *event) {
	//	m_bSureBtnFlag = m_pNodeSureBtn->getBoundingBox().containsPoint(touch->getLocation());
		m_registerInfoOk = false;
		edit0 = m_pEditBox0->getBoundingBox().containsPoint(touch->getLocation());
		edit1 = m_pEditBox1->getBoundingBox().containsPoint(touch->getLocation());
		edit2 = m_pEditBox2->getBoundingBox().containsPoint(touch->getLocation());
		noticeFlag = true;
		if (!btnIsRuning)
		{
			btn_menuflag = m_pBtnMenu->getBoundingBox().containsPoint(touch->getLocation());
			m_pBtnMenu->stopAllActions();
			n_btnDistance = touch->getLocation().x - m_pBtnMenu->boundingBox().origin.x;
		}
		return true;
	};
	listener->onTouchMoved = [&](Touch* touch, Event *event) {
		if (btn_menuflag)
		{
			if (touch->getLocation().x - n_btnDistance < 320)
			{
				return;
			}
			else if (touch->getLocation().x - n_btnDistance > 900)
			{
				if (noticeFlag)
				{
					m_registerInfoOk = judgePassWord();
					noticeFlag = false;
				}
				return;
			}
			m_pBtnMenu->onTouchMoved(touch, event);
			m_pBtnMenu->setPosition(Point(touch->getLocation().x - n_btnDistance, m_pBtnMenu->getPosition().y));
		}

		if (edit0) {
			m_pEditBox0->onTouchMoved(touch, event);
		}
		if (edit2) {
			m_pEditBox2->onTouchMoved(touch, event);
		}
		if (edit1) {
			m_pEditBox1->onTouchMoved(touch, event);
		}
	};

	listener->onTouchEnded = [&](Touch* touch, Event *event) {
		if (btn_menuflag)
		{
			m_pBtnMenu->onTouchEnded(touch, event);
			btn_menuflag = false;
			CCActionInterval *moveold = CCMoveTo::create((m_pBtnMenu->getPosition().x - oldPos.x) / 1500, ccp(320, 170));
			CCEaseOut *easeOut = CCEaseOut::create(moveold, 1);
			m_pBtnMenu->runAction(easeOut);
			if (m_registerInfoOk)
			{
// 				NotificationCenter::getInstance()->postNotification("registermove", this);
// 				this->removeFromParentAndCleanup(true);

				CocoMessageBox *msgbox = CocoMessageBox::create();
				msgbox->CMessageBox("提  示", "注册成功,可以开始游戏了！");
			}
		}
		if (edit1) {
			edit1 = false;
			m_pEditBox1->onTouchEnded(touch, event);
		}
		if (edit0) {
			edit0 = false;
			m_pEditBox0->onTouchEnded(touch, event);
		}
		if (edit2) {
			edit2 = false;
			m_pEditBox2->onTouchEnded(touch, event);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

bool RegisterScene::judgePassWord() {
	if (!strcmp(m_pEditBox2->getText(), "")) {

		CocoMessageBox *msgbox = CocoMessageBox::create();
		msgbox->CMessageBox("提  示", "账户名不能为空");
		// CCDirector::sharedDirector()->getRunningScene()->addChild(msgbox,2);
		return false;
	}
	else if (!strcmp(m_pEditBox1->getText(), "") || !strcmp(m_pEditBox0->getText(), "")) {

		CocoMessageBox *msgbox = CocoMessageBox::create();
		msgbox->CMessageBox("提  示", "密码不能为空");
		// CCDirector::sharedDirector()->getRunningScene()->addChild(msgbox,2);
		return false;
	}
	else if (strcmp(m_pEditBox0->getText(), m_pEditBox1->getText())) {

		CocoMessageBox *msgbox = CocoMessageBox::create();
		msgbox->CMessageBox("提  示", "两次输入的密码不同");
		return false;
		// CCDirector::sharedDirector()->getRunningScene()->addChild(msgbox,2);
	}
	else {
		//sendRegisterMsg();
		return true;
	}
}

void RegisterScene::reciveRegisterMsg(Ref *pSender)
{
	if (m_registerInfoOk)
	{
		NotificationCenter::getInstance()->postNotification("registermove", this);
		this->removeFromParentAndCleanup(true);
	}
}

RegisterScene::~RegisterScene()
{
	this->removeAllChildren();
	TextureCache::getInstance()->removeTextureForKey("register_bg.png");
	TextureCache::getInstance()->removeTextureForKey("reg_cj_up.png");
	TextureCache::getInstance()->removeTextureForKey("reg_cj_down.png");
	TextureCache::getInstance()->removeTextureForKey("register_bounder.png");
}

// void RegisterScene::addObject(Object *obj)
// {
// 	m_obj = obj;
/*}*/