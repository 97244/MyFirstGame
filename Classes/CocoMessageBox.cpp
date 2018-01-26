#include "CocoMessageBox.h"
#include "ResourceName.h"
#include "UTF_8Trans.h"
bool CocoMessageBox::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0), winSize.width, winSize.height))
	{
		return false;
	}
	Director::getInstance()->getRunningScene()->addChild(this, 2);
	setTouchEnabled(true);
	m_pNodeBg = Sprite::create(MESSAGEBOXBG);
	m_pNodeBg->setScale(0);
	m_pNodeBg->setPosition(Point(winSize.width / 2, winSize.height / 2));

	m_pNodeTitleLabel = LabelTTF::create("", SELF_TTF_ONE, 40);
	m_pNodeTitleLabel->setFontFillColor(Color3B(0, 0, 0));
	m_pNodeTitleLabel->setPosition(Point(m_pNodeBg->getContentSize().width / 2, m_pNodeBg->getContentSize().height - 50));
	m_pNodeBg->addChild(m_pNodeTitleLabel);

	m_pNodeMsgLabel = CCLabelTTF::create("", SELF_TTF_ONE, 40, CCSizeMake(500, 400), kCCTextAlignmentLeft);
	m_pNodeMsgLabel->setFontFillColor(ccc3(0, 0, 0));
	m_pNodeMsgLabel->setAnchorPoint(Point(0, 1));
	m_pNodeMsgLabel->setPosition(Point(40, m_pNodeBg->getContentSize().height - 80));
	m_pNodeBg->addChild(m_pNodeMsgLabel);



	auto pBtn0 = MenuItemImage::create(SURE_UP, SURE_DOWN);
	m_pNodeSureBtn = Menu::create(pBtn0, NULL);
	m_pNodeSureBtn->setAnchorPoint(Point(0, 0));
	m_pNodeSureBtn->setPosition(Point(140, 100));
	m_pNodeSureBtn->setContentSize(pBtn0->getContentSize());
	m_pNodeBg->addChild(m_pNodeSureBtn);
	m_pNodeSureBtn->setTouchEnabled(true);
	addChild(m_pNodeBg);
	Director::getInstance()->getRunningScene()->addChild(this, 2);
	setTouchEnabled(true);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event *event) {
		
		m_bSureBtnFlag = m_pNodeSureBtn->getBoundingBox().containsPoint(touch->getLocation());
 		//m_bSureBtnFlag = m_pNodeSureBtn->onTouchBegan(touch, event);
 		m_dGap = touch->getLocation().x - m_pNodeSureBtn->boundingBox().origin.x;
		return true;
	};
	listener->onTouchMoved = [&](Touch* touch, Event *event) {
		
 		if (m_bSureBtnFlag)
 		{
 			m_pNodeSureBtn->onTouchMoved(touch, event);
 			if (touch->getLocation().x - m_dGap < 140) {
 				return;
 			}
 			else if (touch->getLocation().x - m_dGap > 500) {
 				ScaleTo *aScaleTo = ScaleTo::create(0.1, 0);
 				CallFunc *func = CallFunc::create(this, callfunc_selector(CocoMessageBox::isOK));
 				Sequence *seq = Sequence::create(aScaleTo, func, NULL);
 				m_pNodeBg->runAction(seq);
 				return;
 			}
 			m_pNodeSureBtn->setPosition(ccp(touch->getLocation().x - m_dGap, m_pNodeSureBtn->getPosition().y));
 		}
	};

	listener->onTouchEnded = [&](Touch* touch, Event *event) {
 		if (m_bSureBtnFlag) {
 			m_pNodeSureBtn->onTouchEnded(touch, event);
 			MoveTo *moveold = MoveTo::create((m_pNodeSureBtn->getPosition().x - 140) / 1500, ccp(140, 100));
 			EaseOut *easeOut = EaseOut::create(moveold, 1);
 			m_pNodeSureBtn->runAction(easeOut);
 		}
	};
	//_eventDispatcher->addEventListenerWithFixedPriority(listener, -130);
	//_eventDispatcher->addEventListenerWithFixedPriority(listener, -1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}


CocoMessageBox* CocoMessageBox::create()
{
	CocoMessageBox *pRet = new CocoMessageBox();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

void CocoMessageBox::CMessageBox(const char *title, const char *msgs)
{
	char *utitle = G2U(title);
	char *umsgs = G2U(msgs);
	m_pNodeTitleLabel->setString(utitle);
	m_pNodeMsgLabel->setString(umsgs);
	goseAction();
}

void CocoMessageBox::goseAction()
{
	auto actScale = ScaleTo::create(0.1, 1);
	m_pNodeBg->runAction(actScale);
}

void CocoMessageBox::isOK(/*Ref *pSender*/) {
// 	MoveTo *moveold = MoveTo::create((m_pNodeSureBtn->getPosition().x - 140) / 1500, ccp(140, 100));
// 	EaseOut *easeOut = EaseOut::create(moveold, 1);
// 	m_pNodeSureBtn->runAction(easeOut	
	this->removeFromParentAndCleanup(true);
	NotificationCenter::getInstance()->postNotification("registerMessage", this);
}
