#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class LoadingLayer : public LayerColor
{
public:
	
	virtual bool init();
	Object *m_pObj;
	Sprite *m_pNodeProgressBg;
	Sprite *m_pNodeLoadingBg;
	ProgressTimer *m_pProgress;
	int m_nCurCount;
	void loadFinished();
	void setProgress(cocos2d::Texture2D *texture);
	vector<string> m_vResourceArray;
	void addImage(vector<string> arr, Object *obj);
	vector<string>::const_iterator nowcount;
	int threadStart();
	CREATE_FUNC(LoadingLayer);
private:

};
