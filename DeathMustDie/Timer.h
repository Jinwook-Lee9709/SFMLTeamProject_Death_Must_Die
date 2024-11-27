#pragma once
class Timer
{
protected:
	float defaultDuration;
	float timer;
	float duration;

	bool isPlaying;
	bool isLoop;
public:
	void StartTimer(bool loop = true);

	bool UpdateTimer(float dt);

	void SetDefaultDuration(float defaultDuration);
	void SetDuration(float duration);
	void MutiplyDuration(float multiply);	//Insert Decimal number

};

