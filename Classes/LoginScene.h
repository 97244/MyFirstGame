#pragma once
#include "cocos2d.h"
#include "LoadingLayer.h"
USING_NS_CC;
using namespace std;
class SocketClient;
#include "RegisterScene.h"
class LoginScene :public Layer
{
public:
	LoginScene();
	~LoginScene();
	
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);
	
	void loadUI(Ref* pData);
	void socketError(Ref* pData);
	void loginMenuCallBack(Ref* pData);
	void receiveMainScene(Ref* pData);
	void personalBack(Ref* pData);
	void registermoveback(Ref *pData);

	void registerMenuCallBack(Ref *pSender);
	void addRegisterLayer();
	void addLoginLayer();
	/*
	void LayerEaseIn(Node *pSender);
	virtual bool TouchBegan(Touch* touch, Event* event);
	virtual void TouchMoved(Touch* touch, Event* event);
	virtual void TouchEnded(Touch* touch, Event* event);

	void mainScene();
	void MoveAndEase(Point pos, Node * sender);

	void onExit();
	*/
private:
	SocketClient *g_pSocket;
	Size g_cSize;
	LoadingLayer *m_pLoading;
	RegisterScene *m_pRegister;

	Menu *m_pLoginMenu;
//	Point m_beginPoint;
//	Point m_oldPoint;
	Menu *m_pRegisterMenu;
	Layer *m_pLoadLayer;

//	bool m_bRegisterBtn;
//	bool m_bLoginFlag;
//	float g_fGap;//点击btn跟锚点之间的差值
//	float g_fDis;

	vector<string> m_vResourceArray;
	
};