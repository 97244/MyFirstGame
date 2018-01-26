#include "LoadingLayer.h"
#include "ResourceName.h"
bool LoadingLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
	{
		return false;
	}
	this->threadStart();
	m_nCurCount = 0;
	Size size = Director::getInstance()->getWinSize();
	m_pNodeLoadingBg = Sprite::create(M_LOADING_BG);
	m_pNodeLoadingBg->setAnchorPoint(Vec2::ZERO);
	m_pNodeLoadingBg->setPosition(Vec2::ZERO);
	this->addChild(m_pNodeLoadingBg);


	m_pNodeProgressBg = Sprite::create(M_PROGRESS_BG);
	m_pNodeProgressBg->setAnchorPoint(Vec2::ZERO);
	m_pNodeProgressBg->setPosition(Point(size.width / 2 - 400, size.height / 2 - 50));


	m_pProgress = ProgressTimer::create(Sprite::create(M_PROGRESS));
	m_pProgress->setType(ProgressTimer::Type::BAR);
	m_pProgress->setMidpoint(Point(0, 0));
	m_pProgress->setBarChangeRate(Point(1, 0));
	m_pProgress->setAnchorPoint(Vec2::ZERO);
	m_pProgress->setPosition(Point(size.width / 2 - 400, size.height / 2 - 50));


	m_pNodeLoadingBg->addChild(m_pProgress, 2);
	m_pNodeLoadingBg->addChild(m_pNodeProgressBg, 1);
	
	setTouchEnabled(false);

	return true;
}

void LoadingLayer::addImage(vector<string> arr, Object *obj)
{
	m_nCurCount = 1;
	m_vResourceArray = arr;
	nowcount = m_vResourceArray.begin();
	m_pObj = obj;
	setProgress(NULL);
}
void LoadingLayer::setProgress(cocos2d::Texture2D *texture)
{
	if (m_nCurCount == m_vResourceArray.size() || m_vResourceArray.size() == 0)
	{
		return;
	}
	else
	{
		nowcount++;
		m_nCurCount++;
	}
	Director::getInstance()->getTextureCache()->addImageAsync((string(*nowcount)).c_str(), CC_CALLBACK_1(LoadingLayer::setProgress, this));
	m_pProgress->stopAllActions();
	auto to2 = ProgressTo::create(1, m_nCurCount / m_vResourceArray.size() * 100);
	to2->setTag(20);
	CallFunc *func = CallFunc::create(this, callfunc_selector(LoadingLayer::loadFinished));
	Sequence *seq = Sequence::create(to2, func, NULL);
	m_pProgress->runAction(seq);
}

void LoadingLayer::loadFinished()
{
	if (m_nCurCount == m_vResourceArray.size())
	{
		NotificationCenter::getInstance()->postNotification("loadingremove", m_pObj);
		this->removeFromParentAndCleanup(true);
	}
}

int LoadingLayer::threadStart()
{
	return 1;
}