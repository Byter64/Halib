#pragma once
#include <memory>
#include <Hall/Hall.h>

namespace Halib
{
	class Audiosystem;

	class Audio
	{
		friend class Audiosystem;
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
		unsigned char volume;
		bool isInvalid;
		int loopStart, loopEnd;
		const char* path; //For debugging messages only
		
		int frameCount; //Number of frames in the audio. frame = totalSamples/channelCount
		float length; //lenth of the audio in seconds
		float playStartTime;

public:
		//Please call Audiosystem::MakeSound/MakeMusic instead
		Audio() = default;
		//Please call Audiosystem::MakeSound/MakeMusic instead
		Audio(const char* path);

	};
} // namespace Halib
