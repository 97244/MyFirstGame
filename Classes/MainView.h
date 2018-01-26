#pragma once
#include "LoadingLayer.h"
#include "cocos2d.h"
USING_NS_CC;

class MainView : public Layer
{
public:

	MainView();
	~MainView();
#if 0
	enum CALLBACKTYPE
	{
		FIRECALLBACK,
		INTENSIFYCALLBACK,
		TEAMCALLBACK,
		WELFCALLBACK,
	};
	vector<string> fbtexture;
	int dis;
	bool m_bintensify_menu_flag;
	bool m_bteam_menu_flag;
	bool m_bfire_menu_flag;
	bool m_bwelfare_menu_Flag;
	Menu * m_pintensify_Menu;
	Menu *m_pWelfareMenu;//������ť
	Menu *m_pFireMenu;//ս����ť
	Menu *m_pTeamMenu;//�ŶӰ�ť
	LayerColor *color;
	CCLabelTTF *m_namelabel;
	CCLabelTTF *m_coinLabel;
	CCLabelTTF *m_goldLabel;
	Sprite *drag_sp;

	Point fpoint;
	LoadingLayer *intensifLayer;
	Layer *slayer;
	Size size;//���ڴ�С
	Menu *fmenu;

	static Scene * scene();
	virtual bool init();
	//void receiveWelfareMsg(CCObject *pObj);//������Ϣ�¼�
	//void getWelfareMsg();//��ȡ��Ϣ�¼�
	void SecondLayer();
	void setCoin();//��ʼ����Ǯ��Ϣ
	void setRole();//��ʼ��������Ϣ
	void loadFBTexture();

	//void registermove(Ref *pSender);
	CREATE_FUNC(MainView);

private:
	int number;
	void intensifyLoading();
	void enterIntensifyLoading(Ref *pSender);

	int m_coins;
	int m_golds;

	void menuFireBtnCallback(Ref *pSender);

	void menuTeamBtnCallback(Ref *pSender);

	void menuintensifyBtnCallback(Ref *pSender);

	void menuWelfareBtncallback(Ref *pSender);
	void callBackSelect(CALLBACKTYPE type);

	//void MoveAndEase(Point pos, Node * sender);
	//void LayerEaseIn(Node * Layersender, Menu * menu);
	//void setLayerVisible();
	/*
	virtual void  registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	*/
	void onExit();
	void onEnter();
#endif
	vector<string> fbtexture;
	int dis;
	bool fflag;
	bool team_flag;
	bool fire_menu_flag;
	bool flmenuFlag;

	Menu *m_pWelfareMenu;//������ť
	Menu *m_pFireMenu;//ս����ť
	Menu *m_pTeamMenu;//�ŶӰ�ť
	LayerColor *color;
	CCLabelTTF *namelabel;
	CCLabelTTF *coinLabel;
	CCLabelTTF *goldLabel;
	Sprite *drag_sp;

	Point fpoint;
	LoadingLayer *intensifLayer;
	Layer *slayer;
	Size size;//���ڴ�С
	Menu *fmenu;

	static Scene * scene();
	virtual bool init();
	//void receiveWelfareMsg(CCObject *pObj);//������Ϣ�¼�
	//void getWelfareMsg();//��ȡ��Ϣ�¼�
	void SecondLayer();
	void setCoin();//��ʼ����Ǯ��Ϣ
	void setRole();//��ʼ��������Ϣ
	void loadFBTexture();
	CREATE_FUNC(MainView);
	//~MainView();
private:
	int m_coins;
	int m_golds;

	int number;
	Menu * intensify_Menu;
	bool intensify_Flag;
	void intensifyLoading();
	void enterIntensifyLoading(Object *obj);
	void MoveAndEase(Point pos, Node * sender);
	void LayerEaseIn(Node * Layersender, Menu * menu);
	void setLayerVisible();
	//virtual void  registerWithTouchDispatcher();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	void onExit();
	void onEnter();
};