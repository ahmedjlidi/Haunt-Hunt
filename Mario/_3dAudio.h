#pragma once

class _3dAudio
{
private:
	Sound sound;
	SoundBuffer buffer;
	/*Vector2f& PlayerPos;*/
	float offset;
	//Vector2f& SoundPos
	//;
	float maxVolume;

public:
	_3dAudio(Sound sound,float radius, float max_volume);
	CircleShape range;
	const float getVolume();
	void setSound(const Sound& sound);
	const float getOffset();
	const  Vector2f position();
	void update(Vector2f player_pos, Vector2f sound_pos);
	void render(RenderTarget& target);
	void setVolume(const float volume);
	void stop();
};

