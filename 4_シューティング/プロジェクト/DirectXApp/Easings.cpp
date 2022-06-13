#include "Easings.h"
#include <cmath>

float Easings::EaseOutQuad(float timeRate)
{
	return -1.0f * timeRate * (timeRate - 2.0f);
}

float Easings::EaseInQuad(float timeRate)
{
	return timeRate * timeRate;
}

float Easings::EaseInOutQuad(float timeRate)
{
	timeRate *= 2.0f;
	if (timeRate < 1) return timeRate * timeRate * 0.5f;
	timeRate -= 1.0f;
	return (timeRate * (timeRate - 2) - 1) * -0.5f;
}

float Easings::EaseOutCubic(float timeRate)
{
	timeRate -= 1.0f;
	return timeRate * timeRate * timeRate + 1.0f;
}

float Easings::EaseInCubic(float timeRate)
{
	return timeRate * timeRate * timeRate;
}

float Easings::EaseInOutCubic(float timeRate)
{
	timeRate *= 2.0f;
	if (timeRate < 1.0f) return 0.5f * timeRate * timeRate * timeRate;
	timeRate -= 2.0f;
	return (timeRate * timeRate * timeRate + 2.0f) * 0.5f;
}

float Easings::EaseOutQuart(float timeRate)
{
	timeRate -= 1.0f;
	return -1.0f * (timeRate * timeRate * timeRate * timeRate - 1);
}

float Easings::EaseInQuart(float timeRate)
{
	return timeRate * timeRate * timeRate * timeRate;
}

float Easings::EaseInOutQuart(float timeRate)
{
	timeRate *= 2.0f;
	if (timeRate < 1) return 0.5f * timeRate * timeRate * timeRate * timeRate;
	timeRate -= 2.0f;
	return -0.5f * (timeRate * timeRate * timeRate * timeRate - 2.0f);
}

float Easings::EaseOutQuint(float timeRate)
{
	timeRate -= 1.0f;
	return timeRate * timeRate * timeRate * timeRate * timeRate + 1.0f;
}

float Easings::EaseInQuint(float timeRate)
{
	return timeRate * timeRate * timeRate * timeRate * timeRate;
}

float Easings::EaseInOutQuint(float timeRate)
{
	timeRate *= 2.0f;
	if (timeRate < 1.0f) return 0.5f * timeRate * timeRate * timeRate * timeRate * timeRate;
	timeRate -= 2.0f;
	return 0.5f * (timeRate * timeRate * timeRate * timeRate * timeRate + 2.0f);
}

float Easings::EaseOutExpo(float timeRate)
{
	return (float)(std::pow(2, -10 * timeRate) + 1);
}

float Easings::EaseInExpo(float timeRate)
{
	return (float)(std::pow(2, 10 * (timeRate - 1)));
}

float Easings::EaseInOutExpo(float timeRate)
{
	timeRate *= 2.0f;
	if (timeRate < 1.0f) return (float)(0.5 * std::pow(2, 10 * (timeRate - 1)));
	timeRate -= 1.0f;
	return (float)(0.5 * (std::pow(2, -10 * timeRate) + 2));
}

float Easings::EaseOutBack(float timeRate, float over)
{
	float s = 1.70158f * over;
	timeRate -= 1.0f;
	return (timeRate * timeRate * ((s + 1.0f) * timeRate + s) + 1.0f);
}

float Easings::EaseInBack(float timeRate, float over)
{
	float s = 1.70158f * over;
	return timeRate * timeRate * ((s + 1.0f) * timeRate - s);
}

float Easings::EaseInOutBack(float timeRate, float over)
{
	float s = 1.70158f * over;
	timeRate *= 2.0f;
	if (timeRate < 1.0f)
	{
		s *= (1.525f) * over;
		return 0.5f * (timeRate * timeRate * ((s + 1.0f) * timeRate - s));
	}
	timeRate -= 2.0f;
	s *= (1.525f * over);
	return 0.5f * (timeRate * timeRate * ((s + 1.0f) * timeRate + s) + 2.0f);
}

float Easings::EaseOutBounce(float timeRate)
{
	if (timeRate < (1.0f / 2.75f))
	{
		return 7.5625f * timeRate * timeRate;
	}
	else if (timeRate < (2.0f / 2.75f))
	{
		timeRate -= (1.5f / 2.75f);
		return 7.5625f * (timeRate)* timeRate + .75f;
	}
	else if (timeRate < (2.5f / 2.75))
	{
		timeRate -= (2.25f / 2.75f);
		return 7.5625f * (timeRate)* timeRate + .9375f;
	}
	else
	{
		timeRate -= (2.625f / 2.75f);
		return 7.5625f * (timeRate)* timeRate + .984375f;
	}
}

float Easings::EaseOutElastic(float timeRate, float over, float period)
{
	period /= 4.0f;
	float s = period / 4.0f;

	if (over > 1.0f && timeRate < 0.4f)
		over = 1.0f + (timeRate / 0.4f * (over - 1.0f));

	return (float)(1 + std::pow(2, -10 * timeRate) * std::sin((timeRate - s) * (2 * 3.14159265358979323846) / period) * over);
}
