#include "Halib/Audio/Audiosystem.h"
#include <Hall/Hall.h>
#include "Halib/System.h"

Halib::Audiosystem::AudioContainer::AudioContainer(std::shared_ptr<Audio> audio, bool isUsed, int channelID1, int channelID2) : audio(audio), isUsed(isUsed), channelID1(channelID1), channelID2(channelID2)
{

}

unsigned char Halib::Audiosystem::AudioContainer::GetChannelSelect()
{
	unsigned char channelSelect = 0;
	if(channelID1 != -1) channelSelect |= 1 << channelID1;
	if(channelID2 != -1) channelSelect |= 1 << channelID2;
	return channelSelect;
}

bool Halib::Audiosystem::AudioContainer::operator==(const AudioContainer& other) const
{
	return audio == other.audio;
}

bool Halib::Audiosystem::AudioContainer::operator!=(const AudioContainer& other) const
{
	return !(*this == other);
}

signed char Halib::Audiosystem::FindEmptyChannel()
{
	for(int i = 0; i < 8; i++)
		if(!audios[i].isUsed)
			return i;
	return -1;
}

std::tuple<signed char, signed char> Halib::Audiosystem::FindEmptyChannels()
{
	std::tuple<signed char, signed char> result;
	signed char firstID = -1;
	for(int i = 0; i < 8; i++)
	{
		if(!audios[i].isUsed)
		{
			if(firstID == -1)
				firstID = i;
			else
				return std::make_tuple(firstID, i);
		}
	}
	return std::make_tuple(-1, -1);
}

void Halib::Audiosystem::ClearFinishedSounds()
{
	for(int i = 0; i < 8; i++)
	{
		AudioContainer& container = audios[i];
		if (!container.isUsed) continue;
		float time = Halib::GetTimeSinceStartup();
		float deltaTime = time - container.audio->playStartTime;
		if(deltaTime > container.audio->length)
		{
			container.isUsed = false;
			container.audio = nullptr;
			container.channelID1 = -1;
			container.channelID2 = -1;
		}
	}
}

void Halib::Audiosystem::Reset()
{
	for(int i = audios.size(); i < 8; i++)
	{
		audios.push_back(AudioContainer{nullptr, false});
	}

	for(int i = 0; i < 8; i++)
	{
		audios[i].isUsed = false;
	}
}

std::shared_ptr<Halib::Audio> Halib::Audiosystem::LoadMusic(const char* path, float loopEnd, float loopStart)
{
	std::shared_ptr<Audio> music = std::make_shared<Audio>(path);
	if(music->isInvalid) return nullptr;

	if(loopEnd != -1)
	{
		music->loopEnd = loopEnd * 32000;
		music->loopStart = loopStart * 32000;
		music->isLooping = true;
	}
	else
	{
		music->isLooping = false;
	}
	return music;
}

std::shared_ptr<Halib::Audio> Halib::Audiosystem::LoudSound(const char* path)
{
	std::shared_ptr<Audio> sound = std::make_shared<Audio>(path);
	if(sound->isInvalid) return nullptr;
	
	sound->isLooping = false;
	return sound;
}

void Halib::Audiosystem::Play(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return;
	
	ClearFinishedSounds();
	if(audio->type == Audio::MONO) 
	{
		signed char channel = FindEmptyChannel();
		if(channel == -1)
		{
			printf("WARNING: Audio could not be loaded\n");
			printf("All channels are already in use\n");
			printf("File: %s\n", audio->path);
			return;
		}
		if(audio->isLooping)
			Hall::SetupMono(channel, audio->data.get(), audio->frameCount * 1, audio->loopStart, audio->loopEnd, audio->volume);
		else
			Hall::SetupMono(channel, audio->data.get(), audio->frameCount * 1, audio->volume);

		Hall::Play(1 << channel);
		audio->playStartTime = Halib::GetTimeSinceStartup();
		audio->isPlaying = true;
		audios[channel] = AudioContainer(audio, true, channel);
	}
	else if (audio->type == Audio::STEREO)
	{
		const auto [channel1, channel2] = FindEmptyChannels();
		if(channel1 == -1)
		{
			printf("WARNING: Audio could not be loaded\n");
			printf("All channels are already in use\n");
			printf("File: %s\n", audio->path);
			return;
		}
		if (audio->isLooping)
			Hall::SetupStereo(channel1, channel2, audio->data.get(), audio->frameCount * 2, audio->loopStart, audio->loopEnd, audio->volume);
		else
			Hall::SetupStereo(channel1, channel2, audio->data.get(), audio->frameCount * 2, audio->volume);
		unsigned char channelSelect = (1 << channel1) | (1 << channel2);
		Hall::Play(channelSelect);
		audio->playStartTime = Halib::GetTimeSinceStartup();
		audio->isPlaying = true;
		audios[channel1] = AudioContainer(audio, true, channel1, channel2);
		audios[channel2] = AudioContainer(audio, true, channel1, channel2);
	}
}

void Halib::Audiosystem::Pause(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return;

	for(int i = 0; i < 8; i++)
	{
		AudioContainer& container = audios[i];

		if(container.audio == audio)
		{
			Hall::Pause(container.GetChannelSelect());
			audio->isPlaying = false;
			break;
		}
	}
}

void Halib::Audiosystem::SetVolume(std::shared_ptr<Audio> audio, unsigned char volume)
{
	if(audio == nullptr || audio->isInvalid) return;

	audio->volume = volume;
	for(int i = 0; i < 8; i++)
	{
		AudioContainer& container = audios[i];

		if(container.audio == audio)
		{
			Hall::SetVolume(container.GetChannelSelect(), volume);
			break;
		}
	}
}

void Halib::Audiosystem::SetGlobalVolume(unsigned char volume)
{
	Hall::SetGlobalVolume(volume);
}

void Halib::Audiosystem::SetIsLooping(std::shared_ptr<Audio> audio, bool isLooping, float loopEnd, float loopStart)
{
	if(audio == nullptr || audio->isInvalid) return;

	audio->isLooping = isLooping;
	audio->loopStart = loopStart * 32000;
	audio->loopEnd = loopEnd * 32000;
	for(int i = 0; i < 8; i++)
	{
		AudioContainer& container = audios[i];

		if(container.audio == audio)
		{
			Hall::SetLoop(container.GetChannelSelect(), isLooping);
			Hall::SetLoopBoundaries(container.GetChannelSelect(), audio->loopStart, audio->loopEnd);
			break;
		}
	}
}

bool Halib::Audiosystem::GetIsPlaying(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return false;

	ClearFinishedSounds();

	for(int i = 0; i < 8; i++)
	{
		AudioContainer& container = audios[i];

		if(container.audio == audio)
		{
			return true;
		}
	}
	return false;
}

unsigned char Halib::Audiosystem::GetVolume(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return 0;

	return audio->volume;
}

bool Halib::Audiosystem::GetIsMono(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return false;

	return audio->type == Audio::MONO;
}

bool Halib::Audiosystem::GetIsStereo(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return false;

	return audio->type == Audio::STEREO;
}

float Halib::Audiosystem::GetLength(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return 0;

	return audio->length;
}

bool Halib::Audiosystem::GetIsLooping(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return false;

	return audio->isLooping;
}

float Halib::Audiosystem::GetLoopStart(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return 0;

	return audio->loopStart / (float)32000;
}

float Halib::Audiosystem::GetLoopEnd(std::shared_ptr<Audio> audio)
{
	if(audio == nullptr || audio->isInvalid) return 0;

	return audio->loopEnd / (float)32000;
}
