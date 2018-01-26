#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CocoMessageBox :public LayerColor
{
public:
	static CocoMessageBox*create();
	//CREATE_FUNC(CocoMessageBox);
	void CMessageBox(const char *title, const char*msgs);
	virtual bool init();
private:
	//MenuItemImage * pBtn0;

	Sprite *m_pNodeBg;
	Menu *m_pNodeSureBtn;
	LabelTTF *m_pNodeTitleLabel;
	LabelTTF *m_pNodeMsgLabel;
	bool m_bSureBtnFlag;
	double m_dGap;
	void goseAction();
	void isOK(/*Ref *pSender*/);
};