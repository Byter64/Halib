#include "Halib/Audio/Audio.h"
#include <cstdio>
#include "wav_reader_methods.h"
#include "wav_reader_types.h"
#include "Halib/System.h"

bool isChannelUsed[8];

Halib::Audio::Audio(const char* path)
{
	data = nullptr;

	FILE* file = fopen(path, "rb");
	bool isInvalid = check_file_format(file);
	if(isInvalid)
	{
		printf("ERROR: could not parse file as wav\n");
		printf("File: %s\n", path);
		return;
	}

	wav_header wavHeader;
	wavHeader.riff_header = read_riff_header(file);
    wavHeader.fmt_subchunk = read_fmt_subchunk(file);
    wavHeader.data_subchunk = read_data_subchunk(file);

	if(wavHeader.fmt_subchunk.audio_format == 1)
	{
		printf("ERROR: Wav file seems to have some kind of compression\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		return;
	}
	
	switch (wavHeader.fmt_subchunk.num_channels)
	{
	case 0:
		printf("ERROR: Wav file has 0 channels\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		return;
	case 1:
		type = MONO;
		break;
	case 2:
		type = STEREO;
		break;
	default:
		printf("ERROR: Wav file has more than 2 channels\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		return;
	}

	if(wavHeader.fmt_subchunk.sample_rate != 32000)
	{
		printf("ERROR: Wav file does not have a sample rate of 320000 kHz\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		return;
	}

	if(wavHeader.fmt_subchunk.bits_per_sample != 16)
	{
		printf("ERROR: Wav file does not have a bit rate of 16 Bit\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		return;
	}

	frameCount = wavHeader.data_subchunk.subchunk2_size / (2 * wavHeader.fmt_subchunk.num_channels);
	length = frameCount / 32000;
	isPlaying = false;
	isLooping = false;
	volume = 128;
 
	fclose(file);
}

void Halib::Audio::Play()
{
	isPlaying = true;
	playStartTime = GetTimeSinceStartup();
	unsigned char channelMask = 0;

	int i = 0;
	for(; i < 8; i++)
	{
		if(!isChannelUsed[i])
		{
			isChannelUsed[i] = true;
			channelID1 = i; 
			channelMask |= 1 << i;
			break;
		}
	}

	if(type == STEREO)
	{
		for(; i < 8; i++)
		{
			if(!isChannelUsed[i])
			{
				isChannelUsed[i] = true;
				channelID2 = i; 
				channelMask |= 1 << i;
				break;
			}
		}
	}

	if(i == 8)
	{
		printf("WARNING: Audio could not be played becaus no channel is free\n");
		return;
	}

	switch (type)
	{
	case MONO:
		Hall::SetupMono(channelID1, data.get(), frameCount, volume);
		break;
	case Stereo:
		Hall::SetupStereo(channelID1, channelID2, data.get(), frameCount, volume);
		break;
	}

	Hall::Play(channelMask);
}

void Halib::Audio::Pause()
{

}

void Halib::Audio::SetVolume(unsigned char volume)
{

}

void Halib::Audio::SetIsLooping(bool isLooping, int loopEnd, int loopStart)
{

}

bool Halib::Audio::GetIsPlaying()
{

}

unsigned char Halib::Audio::GetVolume()
{

}

bool Halib::Audio::GetIsMono()
{

}

bool Halib::Audio::GetIsStereo()
{

}

float Halib::Audio::GetLength()
{

}

bool Halib::Audio::GetIsLooping()
{

}

int Halib::Audio::GetLoopStart()
{

}

int Halib::Audio::GetLoopEnd()
{

}
