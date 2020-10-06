#pragma once
namespace bf
{
	class Time
	{
	public:
		static float totalTime;
		static float deltaTime;
		static float tmpDeltaTime;
	};
	float Time::deltaTime = 0.0f;
	float Time::totalTime = 0.0f;
	float Time::tmpDeltaTime = 0.0f;
}

