#pragma once
#include "_3dAudio.h"
class AudioSystem
{
private:
	vector<SoundBuffer*> buffers;
	map<string, Sound> sounds;
	map<string, Music*> themes;
	vector<string>CurrentSounds;
	unordered_map<string, vector<_3dAudio*>>_3d_audios;	
public:
	AudioSystem();
	virtual ~AudioSystem();

	void InitSound(const string name, const string file_directory, const unsigned volume);
	void InitTheme(const string name, const string file_directory, const unsigned volume);
	void PlayTheme(const string name);
	void StopTheme(const string name);
	void PauseTheme(const string name);
	void playSound(const string name, const bool ignoreplaying = false);
	void playSoundOnce(const string name);
	void stopSound(const string name);
	const bool SoundIsPlaying(const string name);

	void Init3dSound(const string name, Vector2f playerPos, vector<Vector2f>& SoundSource, float max_volume);
	void play3dSound(const string name, Vector2f playerPo, const vector<Vector2f>& SoundSource);

	void renderSoundRange(const string name, RenderTarget& target);
	void Stop3dSound(const string name);

	void stopAllSounds();
};

