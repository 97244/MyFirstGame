#include "AnimationUtil.h"

Animation*AnimationUtil::createWithSingleFrameName(const char*name, float delay, int iLoops)
{
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame *frame = NULL;
	int index = 1;
	do 
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, index++));
		if (frame == NULL)
		{
			break;
		}
		frameVec.pushBack(frame);
	} while (true);

	Animation *animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);
	return animation;
}


Animation*AnimationUtil::createWithFrameNameAndNum(const char*name, int num,float delay, int iLoops)
{
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame *frame = NULL;
	int index = 1;
	for (index; index<=num; index++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, index));
		if (frame == NULL)
		{
			break;
		}
		frameVec.pushBack(frame);
	}
	
	Animation *animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);
	return animation;
}