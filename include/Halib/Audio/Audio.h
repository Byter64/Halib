#pragma once
#include <memory>
#include <Hall/Hall.h>

namespace Halib
{
	class Audio
	{
public:
		enum Type : char
		{
			MONO,
			STEREO
		};
private:
		std::shared_ptr<Hall::Sample> data;
		Type type;
		bool isPlaying;
		bool isLooping;
		int loopStart, loopEnd;
		unsigned char volume;
		
		int frameCount; //Number of frames in the audio. frame = totalSamples/channelCount
		float length; //lenth of the audio in seconds
		float playStartTime;

		Audio() = default;
		Audio(const char* path);
public:


		void Play();
		void Pause();
		
		void SetVolume(unsigned char volume);
		void SetIsLooping(bool isLooping, int loopEnd = 0, int loopStart = 0);

		bool GetIsPlaying();
		unsigned char GetVolume();
		bool GetIsMono();
		bool GetIsStereo();
		float GetLength();
		bool GetIsLooping();
		int GetLoopStart();
		int GetLoopEnd();

	};
} // namespace Halib
