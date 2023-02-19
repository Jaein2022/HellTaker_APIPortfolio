#include "J_Timer.h"

J_Timer* J_Timer::instance_ = new J_Timer();

J_Timer::J_Timer() : frequency_(), beginningCheck_(), finishingCheck_(), deltaTime_(0.0)
{
	ResetTimer();
}

J_Timer::~J_Timer()
{
}

void J_Timer::ResetTimer()
{
	QueryPerformanceFrequency(&frequency_);
	QueryPerformanceCounter(&beginningCheck_);
	QueryPerformanceCounter(&finishingCheck_);
}

void J_Timer::MeasureDeltaTime()
{
	QueryPerformanceCounter(&finishingCheck_);
	deltaTime_ = static_cast<double>(finishingCheck_.QuadPart - beginningCheck_.QuadPart) / static_cast<double>(frequency_.QuadPart);
	beginningCheck_.QuadPart = finishingCheck_.QuadPart;
}