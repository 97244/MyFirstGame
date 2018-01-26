#include "MainView.h"
#include "ResourceName.h"
#include "UTF_8Trans.h"
MainView::MainView()
{
	m_coins = 100;
	m_golds = 10;
	intensify_Flag = false;
	fire_menu_flag = false;
	team_flag = false;
	flmenuFlag = false;
// 	m_bintensify_menu_flag = false;
// 	m_bfire_menu_flag = false;
// 	m_bteam_menu_flag = false;
// 	m_bwelfare_menu_Flag = false;
}
MainView::~MainView()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
	TextureCache::getInstance()->removeTextureForKey(M_MAINVIEW_BG);
	TextureCache::getInstance()->removeTextureForKey(M_MVDRAG_BG);
	TextureCache::getInstance()->removeTextureForKey(M_KZBTN_UP);
	TextureCache::getInstance()->removeTextureForKey(M_KZBTN_DOWN);
	TextureCache::getInstance()->removeTextureForKey(M_TDBTN_UP);
	TextureCache::getInstance()->removeTextureForKey(M_TDBTN_DOWN);
	TextureCache::getInstance()->removeTextureForKey(M_QHBTN_UP);
	TextureCache::getInstance()->removeTextureForKey(M_QHBTN_DOWN);
	TextureCache::getInstance()->removeTextureForKey(M_FLBTN_UP);
	TextureCache::getInstance()->removeTextureForKey(M_FLBTN_DOWN);
}


 Scene*MainView::scene()
 {
 	auto scene = Scene::create();
 	auto layer = MainView::create();
 	layer->setTag(101);
 	scene->addChild(layer);
 	return scene;
}

bool MainView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainView::enterIntensifyLoading), "loadingremove", NULL);
	//NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainView::receiveWelfareMsg), "welfare", NULL);
	size = Director::getInstance()->getWinSize();
	color = LayerColor::create(Color4B(0, 0, 0, 150), size.width, size.height);
	this->addChild(color, 10);
	//NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainView::registermove), "registermove", NULL);
	intensifyLoading();
	SecondLayer();


}

// void MainView::registermove(Ref *pSender)
// {
// 	this->setVisible(true);
// }

void MainView::intensifyLoading()
{
	LoadingLayer *layer = LoadingLayer::create();
	intensifLayer = layer;
	intensifLayer->setVisible(false);
	intensifLayer->setPosition(Point(-size.width, 0));
	this->addChild(layer, 6);
}
#if 0

void MainView::SecondLayer()
{

	slayer = Layer::create();
	auto pBgSprite = Sprite::create(M_MAINVIEW_BG);
	pBgSprite->setPosition(Point(size.width / 2, size.height / 2));
	slayer->addChild(pBgSprite);

	//拖拽按钮
	drag_sp = Sprite::create(M_MVDRAG_BG);
	drag_sp->setAnchorPoint(Point(0, 0));
	drag_sp->setPosition(Point(0, 0));
	slayer->addChild(drag_sp, 0);

	//用户名
	m_namelabel = CCLabelTTF::create(G2U("这里是名字"), SELF_TTF_ONE, 60);
	m_namelabel->setPosition(Point(size.width / 4, size.height - size.height / 6));
	m_namelabel->setColor(fontColor);
	this->addChild(m_namelabel, 2);

	//银币个数
	m_coinLabel = CCLabelTTF::create("0", SELF_TTF_ONE, 60, CCSizeMake(500, 70), TextHAlignment::LEFT);
	m_coinLabel->setPosition(Point(size.width - 2 * size.width / 5, size.height - size.height / 6));
	m_coinLabel->setColor(fontColor);
	this->addChild(m_coinLabel, 2);

	//金币个数
	m_goldLabel = CCLabelTTF::create("0", SELF_TTF_ONE, 60, CCSizeMake(500, 70), TextHAlignment::LEFT);
	m_goldLabel->setColor(fontColor);
	m_goldLabel->setPosition(Point(size.width - size.width / 9, size.height - size.height / 6));
	this->addChild(m_goldLabel, 2);

	/*战力 团队 强化 福利菜单*/
	MenuItemImage * fire_Btn = MenuItemImage::create(M_KZBTN_UP, M_KZBTN_DOWN, this, menu_selector(MainView::menuFireBtnCallback));
	MenuItemImage * team_Btn = MenuItemImage::create(M_TDBTN_UP, M_TDBTN_DOWN, this, menu_selector(MainView::menuTeamBtnCallback));
	MenuItemImage * intensify_Btn = MenuItemImage::create(M_QHBTN_UP, M_QHBTN_DOWN, this, menu_selector(MainView::menuintensifyBtnCallback));
	MenuItemImage * welfareBtn = MenuItemImage::create(M_FLBTN_UP, M_FLBTN_DOWN, this, menu_selector(MainView::menuWelfareBtncallback));
	welfareBtn->setAnchorPoint(Point(0, 0));
	welfareBtn->setPosition(Point(0, 0));
	intensify_Btn->setPosition(Point(0, 0));
	intensify_Btn->setAnchorPoint(Point(0, 0));
	team_Btn->setPosition(Point(0, 0));
	team_Btn->setAnchorPoint(Point(0, 0));
	fire_Btn->setAnchorPoint(Point(0, 0));
	fire_Btn->setPosition(Point(0, 0));

	m_pWelfareMenu = Menu::create(welfareBtn, NULL);
	m_pWelfareMenu->setPosition(Point(0, 70));
	m_pWelfareMenu->setAnchorPoint(Point(0, 0));
	slayer->addChild(m_pWelfareMenu, 1);

	m_pintensify_Menu = Menu::create(intensify_Btn, NULL);
	m_pintensify_Menu->setPosition(Point(0, 250));
	m_pintensify_Menu->setAnchorPoint(Point(0, 0));
	slayer->addChild(m_pintensify_Menu, 1);

	m_pTeamMenu = Menu::create(team_Btn, NULL);
	m_pTeamMenu->setPosition(Point(0, 430));
	m_pTeamMenu->setAnchorPoint(Point(0, 0));
	slayer->addChild(m_pTeamMenu, 1);

	m_pFireMenu = Menu::create(fire_Btn, NULL);
	m_pFireMenu->setPosition(Point(0, 610));
	m_pFireMenu->setAnchorPoint(Point(0, 0));

	slayer->addChild(m_pFireMenu, 1);
	slayer->setPosition(Point(0, 0));
	this->addChild(slayer, 1);
}

void MainView::onEnter() {
	Layer::onEnter();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	// CCTextureCache::sharedTextureCache()->removeAllTextures();
}

void MainView::onExit() {
	Layer::onExit();
}

void MainView::setCoin() {

	m_coinLabel->setString(StringUtils::toString(m_coins));
	m_goldLabel->setString(StringUtils::toString(m_golds));
}
void MainView::setRole()//初始化人物信息
{

}
void MainView::loadFBTexture() {
	if (number == 1) {
		fbtexture.push_back("FBLayer/guanqia_bg.png");
		fbtexture.push_back("FBLayer/huodong_down.png");
		fbtexture.push_back("FBLayer/huodong_up.png");
		fbtexture.push_back("FBLayer/icons.png");
		fbtexture.push_back("FBLayer/jingji_dwon.png");
		fbtexture.push_back("FBLayer/jingji_up.png");
		fbtexture.push_back("FBLayer/tiaozhan_down.png");
		fbtexture.push_back("FBLayer/tiaozhan_up.png");
		fbtexture.push_back("FBLayer/wujin_down.png");
		fbtexture.push_back("FBLayer/wujin_up.png");
		fbtexture.push_back("FBLayer/xiaodui_down.png");
		fbtexture.push_back("FBLayer/xiaodui_up.png");
		fbtexture.push_back("FBLayer/zhuxian_down.png");
		fbtexture.push_back("FBLayer/zhuxian_up.png");
	}
	else if (number == 2) {
		fbtexture.push_back("qianghua_1/attack_down.png");
		fbtexture.push_back("qianghua_1/attack_up.png");
		fbtexture.push_back("qianghua_1/dujie_down.png");
		fbtexture.push_back("qianghua_1/dujie_up.png");
		fbtexture.push_back("qianghua_1/qh_bg.png");
		fbtexture.push_back("qianghua_1/shengming_down.png");
		fbtexture.push_back("qianghua_1/shengming_up.png");

	}
	else if (number == 3) {
		fbtexture.push_back("team_layer_1/persons01.png");
		fbtexture.push_back("team_layer_1/team_bg.png");
		fbtexture.push_back("team_layer_1/team_locked.png");
		fbtexture.push_back("team_layer_1/team_zhegai.png");
		fbtexture.push_back("team_layer_1/team_unlocked.png");
		fbtexture.push_back("frontPerson.png");
	}
	else if (number == 4) {
		fbtexture.push_back("welfareBg.png");
		fbtexture.push_back("welfarecell_Bg.png");
		fbtexture.push_back("receive_down.png");
		fbtexture.push_back("receive_up.png");
		fbtexture.push_back("receive_dis.png");
	}

	intensifLayer->addImage(fbtexture, this);

}
void MainView::callBackSelect(CALLBACKTYPE type)
{
	switch (type)
	{
	case MainView::FIRECALLBACK:

		if (m_bintensify_menu_flag)
		{
			m_pintensify_Menu->setScale(1.0f);
			m_bintensify_menu_flag = false;
		}
		if (m_bteam_menu_flag)
		{
			m_pTeamMenu->setScale(1.0f);
			m_bteam_menu_flag = false;
		}
		if (m_bwelfare_menu_Flag)
		{
			m_pWelfareMenu->setScale(1.0f);
			m_bwelfare_menu_Flag = false;
		}
		if (m_bfire_menu_flag)
		{
			return;
		}
		m_pFireMenu->setScale(1.1);
		m_bfire_menu_flag = true;
		break;
	case MainView::INTENSIFYCALLBACK:
		break;
	case MainView::TEAMCALLBACK:
		break;
	case MainView::WELFCALLBACK:
		break;
	default:
		break;
	}
}
void MainView::menuFireBtnCallback(Ref *pSender)
{

	if (m_bintensify_menu_flag)
	{
		m_pintensify_Menu->setScale(1.0f);
		m_bintensify_menu_flag = false;
	}
	if (m_bteam_menu_flag)
	{
		m_pTeamMenu->setScale(1.0f);
		m_bteam_menu_flag = false;
	}
	if (m_bwelfare_menu_Flag)
	{
		m_pWelfareMenu->setScale(1.0f);
		m_bwelfare_menu_Flag = false;
	}
	if (m_bfire_menu_flag)
	{
		return;
	}
	m_pFireMenu->setScale(1.1);
	m_bfire_menu_flag = true;

}
void MainView::menuTeamBtnCallback(Ref *pSender)
{
	if (m_bfire_menu_flag)
	{
		m_pFireMenu->setScale(1.0f);
		m_bfire_menu_flag = false;
	}
	if (m_bintensify_menu_flag)
	{
		m_pintensify_Menu->setScale(1.0f);
		m_bintensify_menu_flag = false;
	}
	if (m_bwelfare_menu_Flag)
	{
		m_pWelfareMenu->setScale(1.0f);
		m_bwelfare_menu_Flag = false;
	}

	if (m_bteam_menu_flag)
	{
		return;
	}


	m_bteam_menu_flag = true;
	m_pTeamMenu->setScale(1.1f);
}
void MainView::menuintensifyBtnCallback(Ref *pSender)
{
	if (m_bfire_menu_flag)
	{
		m_pFireMenu->setScale(1.0f);
		m_bfire_menu_flag = false;
	}

	if (m_bteam_menu_flag)
	{
		m_pTeamMenu->setScale(1.0f);
		m_bteam_menu_flag = false;
	}
	if (m_bwelfare_menu_Flag)
	{
		m_pWelfareMenu->setScale(1.0f);
		m_bwelfare_menu_Flag = false;
	}
	if (m_bintensify_menu_flag)
	{
		return;
	}
	m_pintensify_Menu->setScale(1.1f);
	m_bintensify_menu_flag = true;
}
void MainView::menuWelfareBtncallback(Ref *pSender)
{
	if (m_bfire_menu_flag)
	{
		m_pFireMenu->setScale(1.0f);
		m_bfire_menu_flag = false;
	}
	if (m_bintensify_menu_flag)
	{
		m_pintensify_Menu->setScale(1.0f);
		m_bintensify_menu_flag = false;
	}
	if (m_bteam_menu_flag)
	{
		m_pTeamMenu->setScale(1.0f);
		m_bteam_menu_flag = false;
	}
	if (m_bwelfare_menu_Flag)
	{
		return;
	}

	m_pWelfareMenu->setScale(1.1f);
	m_bwelfare_menu_Flag = true;
}
#endif
void MainView::SecondLayer() {
	slayer = CCLayer::create();


	Sprite *m_pBgSprite = Sprite::create(M_MAINVIEW_BG);
	m_pBgSprite->setPosition(Point(size.width / 2, size.height / 2));
	slayer->addChild(m_pBgSprite);



	drag_sp = Sprite::create(M_MVDRAG_BG);
	drag_sp->setAnchorPoint(Point(0, 0));
	drag_sp->setPosition(Point(0, 0));
	slayer->addChild(drag_sp, 0);

	namelabel = LabelTTF::create(G2U("这里是名字"), SELF_TTF_ONE, 60);
	namelabel->setPosition(Point(size.width / 4, size.height - size.height / 6));
	namelabel->setColor(fontColor);
	this->addChild(namelabel, 2);

	coinLabel = LabelTTF::create("0", SELF_TTF_ONE, 60, CCSizeMake(500, 70), kCCTextAlignmentLeft);
	coinLabel->setPosition(Point(size.width - 2 * size.width / 5, size.height - size.height / 6));
	coinLabel->setColor(fontColor);
	this->addChild(coinLabel, 2);

	goldLabel = LabelTTF::create("0", SELF_TTF_ONE, 60, CCSizeMake(500, 70), kCCTextAlignmentLeft);
	goldLabel->setColor(fontColor);
	goldLabel->setPosition(Point(size.width - size.width / 9, size.height - size.height / 6));
	this->addChild(goldLabel, 2);

	MenuItemImage * fire_Btn = MenuItemImage::create(M_KZBTN_UP, M_KZBTN_DOWN);
	MenuItemImage * team_Btn = MenuItemImage::create(M_TDBTN_UP, M_TDBTN_DOWN);
	MenuItemImage * strengthening_Btn = MenuItemImage::create(M_QHBTN_UP, M_QHBTN_DOWN);
	MenuItemImage * welfareBtn = MenuItemImage::create(M_FLBTN_UP, M_FLBTN_DOWN);
	welfareBtn->setAnchorPoint(Point(0, 0));
	welfareBtn->setPosition(Point(0, 0));
	strengthening_Btn->setPosition(Point(0, 0));
	strengthening_Btn->setAnchorPoint(Point(0, 0));
	team_Btn->setPosition(Point(0, 0));
	team_Btn->setAnchorPoint(Point(0, 0));
	fire_Btn->setAnchorPoint(Point(0, 0));
	fire_Btn->setPosition(Point(0, 0));
	m_pWelfareMenu = Menu::create(welfareBtn, NULL);
	m_pWelfareMenu->setPosition(Point(0, 70));
	m_pWelfareMenu->setAnchorPoint(Point(0, 0));
	slayer->addChild(m_pWelfareMenu, 1);
	m_pWelfareMenu->setTouchEnabled(true);
	m_pWelfareMenu->setContentSize(welfareBtn->getContentSize());


	intensify_Menu = Menu::create(strengthening_Btn, NULL);
	intensify_Menu->setPosition(Point(0, 250));
	intensify_Menu->setAnchorPoint(Point(0, 0));
	slayer->addChild(intensify_Menu, 1);
	intensify_Menu->setTouchEnabled(true);
	intensify_Menu->setContentSize(strengthening_Btn->getContentSize());

	m_pTeamMenu = Menu::create(team_Btn, NULL);
	m_pTeamMenu->setPosition(Point(0, 430));
	m_pTeamMenu->setAnchorPoint(Point(0, 0));
	slayer->addChild(m_pTeamMenu, 1);
	m_pTeamMenu->setTouchEnabled(true);
	m_pTeamMenu->setContentSize(team_Btn->getContentSize());

	m_pFireMenu = Menu::create(fire_Btn, NULL);
	m_pFireMenu->setPosition(Point(0, 610));
	m_pFireMenu->setAnchorPoint(Point(0, 0));
	m_pFireMenu->setTouchEnabled(true);
	slayer->addChild(m_pFireMenu, 1);
	slayer->setPosition(Point(0, 0));
	this->addChild(slayer, 1);
	m_pFireMenu->setContentSize(fire_Btn->getContentSize());

	//setTouchEnabled(true);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(MainView::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainView::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, -1);


}

void MainView::onEnter() {
	Layer::onEnter();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	// CCTextureCache::sharedTextureCache()->removeAllTextures();
}

void MainView::onExit() {
	Layer::onExit();
}

void MainView::setCoin() {

	coinLabel->setString(StringUtils::toString(m_coins));
	goldLabel->setString(StringUtils::toString(m_golds));
}
void MainView::setRole()//初始化人物信息
{

}
void MainView::loadFBTexture() {
	if (number == 1) {
		fbtexture.push_back("FBLayer/guanqia_bg.png");
		fbtexture.push_back("FBLayer/huodong_down.png");
		fbtexture.push_back("FBLayer/huodong_up.png");
		fbtexture.push_back("FBLayer/icons.png");
		fbtexture.push_back("FBLayer/jingji_dwon.png");
		fbtexture.push_back("FBLayer/jingji_up.png");
		fbtexture.push_back("FBLayer/tiaozhan_down.png");
		fbtexture.push_back("FBLayer/tiaozhan_up.png");
		fbtexture.push_back("FBLayer/wujin_down.png");
		fbtexture.push_back("FBLayer/wujin_up.png");
		fbtexture.push_back("FBLayer/xiaodui_down.png");
		fbtexture.push_back("FBLayer/xiaodui_up.png");
		fbtexture.push_back("FBLayer/zhuxian_down.png");
		fbtexture.push_back("FBLayer/zhuxian_up.png");
	}
	else if (number == 2) {
		fbtexture.push_back("qianghua_1/attack_down.png");
		fbtexture.push_back("qianghua_1/attack_up.png");
		fbtexture.push_back("qianghua_1/dujie_down.png");
		fbtexture.push_back("qianghua_1/dujie_up.png");
		fbtexture.push_back("qianghua_1/qh_bg.png");
		fbtexture.push_back("qianghua_1/shengming_down.png");
		fbtexture.push_back("qianghua_1/shengming_up.png");

	}
	else if (number == 3) {
		fbtexture.push_back("team_layer_1/persons01.png");
		fbtexture.push_back("team_layer_1/team_bg.png");
		fbtexture.push_back("team_layer_1/team_locked.png");
		fbtexture.push_back("team_layer_1/team_zhegai.png");
		fbtexture.push_back("team_layer_1/team_unlocked.png");
		fbtexture.push_back("frontPerson.png");
	}
	else if (number == 4) {
		fbtexture.push_back("welfareBg.png");
		fbtexture.push_back("welfarecell_Bg.png");
		fbtexture.push_back("receive_down.png");
		fbtexture.push_back("receive_up.png");
		fbtexture.push_back("receive_dis.png");
	}

	intensifLayer->addImage(fbtexture, this);

}

bool MainView::onTouchBegan(Touch* touch, Event* event) {
	if (intensify_Flag || fire_menu_flag || team_flag) {
		return false;
	}



// 	intensify_Flag = intensify_Menu->onTouchBegan(touch, event);
// 	team_flag = m_pTeamMenu->onTouchBegan(touch, event);
// 	fire_menu_flag = m_pFireMenu->onTouchBegan(touch, event);
// 	flmenuFlag = m_pWelfareMenu->onTouchBegan(touch, event);
	fpoint = touch->getLocation();

	intensify_Flag = intensify_Menu->getBoundingBox().containsPoint(touch->getLocation());
	if (intensify_Flag)
	{
		log("");
	}
	team_flag = m_pTeamMenu->getBoundingBox().containsPoint(touch->getLocation());
	if (team_flag)
	{
		log("");
	}
	fire_menu_flag = m_pFireMenu->getBoundingBox().containsPoint(touch->getLocation());
	if (fire_menu_flag)
	{
		log("");
	}
	flmenuFlag = m_pWelfareMenu->getBoundingBox().containsPoint(touch->getLocation());
	if (flmenuFlag)
	{
		log("");
	}

	if (fire_menu_flag) {
		dis = touch->getLocation().x - m_pFireMenu->boundingBox().origin.x;
		m_pFireMenu->setScale(1.1);

	}
	else if (intensify_Flag) {
		dis = touch->getLocation().x - intensify_Menu->boundingBox().origin.x;
		intensify_Menu->setScale(1.1);
	}
	else if (team_flag) {
		dis = touch->getLocation().x - m_pTeamMenu->boundingBox().origin.x;
		m_pTeamMenu->setScale(1.1);
	}
	else if (flmenuFlag) {
		dis = touch->getLocation().x - m_pWelfareMenu->boundingBox().origin.x;
		m_pWelfareMenu->setScale(1.1);
	}
	return true;
}

void MainView::onTouchMoved(Touch* touch, Event* event) {
	if (intensify_Flag) {
		intensify_Menu->onTouchMoved(touch, event);
		m_pWelfareMenu->setZOrder(0);
		m_pFireMenu->setZOrder(0);
		m_pTeamMenu->setZOrder(0);
		drag_sp->setZOrder(1);
		intensify_Menu->setPosition(Point(touch->getLocation().x - dis, intensify_Menu->getPosition().y));
		drag_sp->setPosition(Point(touch->getLocation().x - dis, drag_sp->getPosition().y));
		intensifLayer->setPosition(Point(touch->getLocation().x - size.width - dis, 0));
	}
	else  if (fire_menu_flag) {

		m_pFireMenu->onTouchMoved(touch, event);
		m_pWelfareMenu->setZOrder(0);
		intensify_Menu->setZOrder(0);
		m_pTeamMenu->setZOrder(0);
		drag_sp->setZOrder(1);
		drag_sp->setPosition(Point(touch->getLocation().x - dis, drag_sp->getPosition().y));
		m_pFireMenu->setPosition(Point(touch->getLocation().x - dis, m_pFireMenu->getPosition().y));
		intensifLayer->setPosition(Point(touch->getLocation().x - size.width - dis, 0));
	}
	if (team_flag) {
		m_pTeamMenu->onTouchMoved(touch, event);
		m_pWelfareMenu->setZOrder(0);
		m_pFireMenu->setZOrder(0);
		intensify_Menu->setZOrder(0);
		drag_sp->setZOrder(1);
		drag_sp->setPosition(Point(touch->getLocation().x - dis, drag_sp->getPosition().y));
		m_pTeamMenu->setPosition(Point(touch->getLocation().x - dis, m_pTeamMenu->getPosition().y));
		intensifLayer->setPosition(Point(touch->getLocation().x - size.width - dis, 0));
	}
	if (flmenuFlag) {
		m_pWelfareMenu->onTouchMoved(touch, event);
		m_pFireMenu->setZOrder(0);
		intensify_Menu->setZOrder(0);
		m_pTeamMenu->setZOrder(0);
		drag_sp->setZOrder(1);
		drag_sp->setPosition(Point(touch->getLocation().x - dis, drag_sp->getPosition().y));
		m_pWelfareMenu->setPosition(Point(touch->getLocation().x - dis, m_pWelfareMenu->getPosition().y));
		intensifLayer->setPosition(Point(touch->getLocation().x - size.width - dis, 0));
	}
}

void MainView::onTouchEnded(Touch* touch, Event* event) {
	if (intensify_Flag) {
		number = 2;
		intensify_Menu->onTouchEnded(touch, event);
		intensify_Menu->setScale(1);
		m_pWelfareMenu->setZOrder(2);
		m_pFireMenu->setZOrder(2);
		m_pTeamMenu->setZOrder(2);
		drag_sp->setZOrder(0);
		LayerEaseIn(intensifLayer, intensify_Menu);
		intensify_Flag = false;
	}
	if (fire_menu_flag) {
		number = 1;
		m_pFireMenu->setScale(1);
		intensify_Menu->setZOrder(2);
		m_pWelfareMenu->setZOrder(2);
		m_pTeamMenu->setZOrder(2);
		drag_sp->setZOrder(0);
		m_pFireMenu->onTouchEnded(touch, event);
		LayerEaseIn(intensifLayer, m_pFireMenu);
		fire_menu_flag = false;

	}
	if (team_flag) {
		number = 3;
		m_pTeamMenu->setScale(1);
		m_pWelfareMenu->setZOrder(2);
		intensify_Menu->setZOrder(2);
		drag_sp->setZOrder(0);
		m_pFireMenu->setZOrder(0);
		m_pTeamMenu->onTouchEnded(touch, event);
		LayerEaseIn(intensifLayer, m_pTeamMenu);
		team_flag = false;
	}
	if (flmenuFlag) {
		number = 4;
		m_pWelfareMenu->onTouchEnded(touch, event);
		m_pWelfareMenu->setScale(1);
		intensify_Menu->setZOrder(2);
		m_pTeamMenu->setZOrder(2);
		drag_sp->setZOrder(0);
		m_pFireMenu->setZOrder(2);
		LayerEaseIn(intensifLayer, m_pWelfareMenu);
		flmenuFlag = false;
	}
}

void MainView::enterIntensifyLoading(Object *obj)
{

}
void MainView::MoveAndEase(Point pos, Node * sender)
{

}
void MainView::LayerEaseIn(Node * Layersender, Menu * menu)
{

}
void MainView::setLayerVisible()
{

}