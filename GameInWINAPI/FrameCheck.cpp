//FrameCheck.cpp

#include "stdafx.h"
#include "FrameCheck.h"


FrameCheck::FrameCheck(size_t iFps)
{
	_fps = iFps;
	_timePerFunction = 1000 / _fps;
}


FrameCheck::~FrameCheck()
{

}


bool FrameCheck::checkFrame()
{

	return true;
}