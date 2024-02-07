#include "stdafx.h"
#include "AudioSystem.h"


AudioSystem::AudioSystem()
{
	
}

AudioSystem::~AudioSystem()
{
	for (auto& e : this->_3d_audios)
	{
		const string name = e.first;
		for (auto& audio : this->_3d_audios[name])
		{
			delete audio;
		}
		this->_3d_audios[name].clear();
	}


	for (auto& theme : this->themes)
	{
		{
			delete theme.second;
		}
	}

}

void AudioSystem::InitSound(const string name, const string file_directory, const unsigned volume)
{

	SoundBuffer* soundbuffer  = new SoundBuffer();
	soundbuffer->loadFromFile(file_directory);
	
	this->buffers.push_back(soundbuffer);


	this->sounds[name].setBuffer(*this->buffers[this->buffers.size() - 1]);
	this->sounds[name].setVolume(volume);

	
	
}

void AudioSystem::InitTheme(const string name, const string file_directory, const unsigned volume)
{
	Music* music = new Music();
	music->openFromFile(file_directory);
	this->themes[name] = music;
	this->themes[name]->setVolume(volume);
	this->themes[name]->setLoop(true);

}

void AudioSystem::PlayTheme(const string name)
{
	if (this->themes[name])
	{
		if (this->themes[name]->getStatus() != Music::Playing)
		{
			this->themes[name]->play();
		}

		for (auto& e : this->themes)
		{
			if (e.second->getStatus() == Music::Playing
				&& e.first != name)
			{
				e.second->pause();
			}
		}
	}
}

void AudioSystem::StopTheme(const string name)
{
	if(this->themes[name])
		this->themes[name]->stop();
}

void AudioSystem::PauseTheme(const string name)
{
	if (this->themes[name]->getStatus() != Music::Paused
		&&this->themes[name])
	{
		this->themes[name]->pause();
	}
}

void AudioSystem::playSound(const string name, const bool ignoreplaying)
{
	if (!ignoreplaying)
	{
		if (this->sounds[name].getStatus() != Sound::Playing)
			this->sounds[name].play();
	}
	else
		this->sounds[name].play();
}

void AudioSystem::playSoundOnce(const string name)
{
	if (this->sounds[name].getStatus() != Sound::Playing || this->sounds[name].getStatus() != Sound::Stopped)
		this->sounds[name].play();

	if (this->sounds[name].getStatus() == Sound::Stopped)
	{
		this->sounds[name].stop();
	}
}

void AudioSystem::stopSound(const string name)
{
	this->sounds[name].stop();
}

const bool AudioSystem::SoundIsPlaying(const string name)
{
	return this->sounds[name].getStatus() == Sound::Playing;
}

void AudioSystem::Init3dSound(const string name, Vector2f playerPos, vector<Vector2f>& SoundSource, float max_volume)
{

	int n = SoundSource.size();
	while (n--)
	{
		this->_3d_audios[name].push_back(new _3dAudio(this->sounds[name], 500.f, max_volume));
	}
}

void AudioSystem::play3dSound(const string name, Vector2f playerPos, const vector<Vector2f>& SoundSource)
{

	for (size_t i = 0; i < this->_3d_audios[name].size(); i++)
	{
		this->_3d_audios[name][i]->update(playerPos, SoundSource[i]);
	}
}


void AudioSystem::renderSoundRange(const string name, RenderTarget& target)
{
	
	for (auto& e : this->_3d_audios[name])
	{
		if(e)
			e->render(target);
	}
}

void AudioSystem::Stop3dSound(const string name)
{
	for (auto& e : this->_3d_audios[name])
	{
		if(e)
			e->stop();
	}
}

void AudioSystem::stopAllSounds()
{
	for (auto& e : this->sounds)
	{
		e.second.stop();
	}

	for (auto& e : this->_3d_audios)
	{
		const string name = e.first;
		for (auto& audio : this->_3d_audios[name])
		{
			delete audio;
		}
		this->_3d_audios[name].clear();
	}

	for (auto& e : this->themes)
	{
		const string name = e.first;
		for (auto& theme : this->themes)
		{
			 theme.second->stop();
		}
	}
}









