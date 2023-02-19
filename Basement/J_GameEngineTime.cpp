#include "J_GameEngineTime.h"

J_GameEngineTime* J_GameEngineTime::instance_ = new J_GameEngineTime();

J_GameEngineTime::J_GameEngineTime() : frequency_(), beginningCheck_(), finishingCheck_(), deltaTime_(0.0)
{
	ResetTimer();
}

J_GameEngineTime::~J_GameEngineTime()
{
}

void J_GameEngineTime::ResetTimer()
{
	QueryPerformanceFrequency(&frequency_);
	QueryPerformanceCounter(&beginningCheck_);
	QueryPerformanceCounter(&finishingCheck_);
}

void J_GameEngineTime::UpdateDeltaTime()
{
	QueryPerformanceCounter(&finishingCheck_);
	deltaTime_ = static_cast<double>(finishingCheck_.QuadPart - beginningCheck_.QuadPart) / static_cast<double>(frequency_.QuadPart);
	beginningCheck_.QuadPart = finishingCheck_.QuadPart;
}