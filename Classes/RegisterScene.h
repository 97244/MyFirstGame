#pragma once
#include "cocostudio/CocoStudio.h" 
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "cocos2d.h"
USING_NS_CC;
class RegisterScene :public Layer {
public:

	Point oldPos;
	Menu *m_pBtnMenu;
	bool btn_menuflag;
	bool btnIsRuning;
	bool noticeFlag;
	int n_btnDistance;
	bool m_registerInfoOk;
	Size m_winSize;
	EditBox *m_pEditBox0;
	EditBox *m_pEditBox1;
	EditBox *m_pEditBox2;
	bool edit0;
	bool edit1;
	bool edit2;
	virtual bool init();
	~RegisterScene();
	bool judgePassWord();
	void reciveRegisterMsg(Ref *pSender);
	//Object *m_obj;
	/*Lambd表达式替代*/
	/*
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	*/
	//void addObject(Object *obj);
	CREATE_FUNC(RegisterScene);
};