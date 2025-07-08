#include "Halib/Audio/Audio.h"
#include <cstdio>
#include "wav_reader_methods.h"
#include "wav_reader_types.h"
#include "Halib/System.h"

Halib::Audio::Audio(const char* path)
{
	this->isInvalid = false;
	data = nullptr;

	FILE* file = fopen(path, "rb");
	bool isInvalid = check_file_format(file);
	if(isInvalid)
	{
		printf("ERROR: could not parse file as wav\n");
		printf("File: %s\n", path);
		this->isInvalid = true;
		fclose(file);
		return;
	}

	
	fseek(file, 0, SEEK_SET);

	wav_header wavHeader;
	wavHeader.riff_header = read_riff_header(file);
    wavHeader.fmt_subchunk = read_fmt_subchunk(file);
    wavHeader.data_subchunk = read_data_subchunk(file);

	if(wavHeader.fmt_subchunk.audio_format != 1)
	{
		printf("ERROR: Wav file seems to have some kind of compression\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		this->isInvalid = true;
		fclose(file);
		return;
	}
	
	switch (wavHeader.fmt_subchunk.num_channels)
	{
	case 0:
		printf("ERROR: Wav file has 0 channels\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		this->isInvalid = true;
		fclose(file);
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
		this->isInvalid = true;
		fclose(file);
		return;
	}

	if(wavHeader.fmt_subchunk.sample_rate != 32000)
	{
		printf("ERROR: Wav file does not have a sample rate of 320000 kHz\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		this->isInvalid = true;
		fclose(file);
		return;
	}

	if(wavHeader.fmt_subchunk.bits_per_sample != 16)
	{
		printf("ERROR: Wav file does not have a bit rate of 16 Bit\n");
		printf("I die.\n");
		printf("File: %s\n", path);
		this->isInvalid = true;
		fclose(file);
		return;
	}

	frameCount = wavHeader.data_subchunk.subchunk2_size / (2 * wavHeader.fmt_subchunk.num_channels);
	length = frameCount / 32000;
	isPlaying = false;
	isLooping = false;
	volume = 128;
	this->path = path;
	data = std::make_shared<Hall::Sample[]>(wavHeader.data_subchunk.subchunk2_size / 2);
	fread(data.get(), wavHeader.data_subchunk.subchunk2_size, 1, file);
	printf("Error?: %i \n", ferror(file));
	printf("EOF?: %i \n", feof(file));
 
	fclose(file);
}