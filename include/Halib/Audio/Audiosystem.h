#pragma once
#include <memory>
#include "Halib/Audio/Audio.h"
#include <vector>
#include <tuple>

namespace Halib
{
	class Audiosystem
	{
		struct AudioContainer
		{
			std::shared_ptr<Audio> audio;
			int channelID1 = -1;
			int channelID2 = -1;
			bool isUsed;

			AudioContainer(std::shared_ptr<Audio> audio, bool isUsed, int channelID1 = -1, int channelID2 = -1);

			unsigned char GetChannelSelect();

			bool operator==(const AudioContainer& other) const;
			bool operator!=(const AudioContainer& other) const;
		};

		//Maps channelID to audio. Always has a length of 8
		std::vector<AudioContainer> audios;

		char FindEmptyChannel();
		std::tuple<char, char> FindEmptyChannels();
		void ClearFinishedSounds();
public:
		void Reset();

		/// @brief 
		/// @param path 
		/// @param loopEnd The end of the loop in seconds
		/// @param loopStart The start of the loop in seconds
		/// @return 
		std::shared_ptr<Audio> LoadMusic(const char* path, float loopEnd = -1, float loopStart = 0);
		std::shared_ptr<Audio> LoudSound(const char* path);
		void Play(std::shared_ptr<Audio> audio);
		void Pause(std::shared_ptr<Audio> audio);
		
		void SetVolume(std::shared_ptr<Audio> audio, unsigned char volume);
		void SetGlobalVolume(unsigned char volume);
		
		/// @brief 
		/// @param audio 
		/// @param isLooping 
		/// @param loopEnd The end of the loop in seconds
		/// @param loopStart The start of the loop in seconds
		void SetIsLooping(std::shared_ptr<Audio> audio, bool isLooping, float loopEnd = 0, float loopStart = 0);

		bool GetIsPlaying(std::shared_ptr<Audio> audio);
		unsigned char GetVolume(std::shared_ptr<Audio> audio);
		bool GetIsMono(std::shared_ptr<Audio> audio);
		bool GetIsStereo(std::shared_ptr<Audio> audio);
		float GetLength(std::shared_ptr<Audio> audio);
		bool GetIsLooping(std::shared_ptr<Audio> audio);
		float GetLoopStart(std::shared_ptr<Audio> audio);
		float GetLoopEnd(std::shared_ptr<Audio> audio);
	};
} // namespace Halib
