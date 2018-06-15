#include <iostream>
#include<fstream>
#include<stdexcept>
#include<cstdio>
#include<cmath>

using namespace std;

#include"audio\wav\wav.h"
#include"audio\audio.h"
#include"stream\FileInputStream.h"
#include"stream\FileOutputStream.h"


using namespace vocal_studio;
int main(int argc, char *argv[])
{
	std::FILE * file = nullptr;
	file=std::fopen("b.wav", "wb");
	if (file==nullptr)
	{
		throw std::runtime_error("fail to open file.");
	}
	Audio16 myaudio;
	myaudio.attribute.channels = 2;
	myaudio.attribute.samplesPerSec = 44100;
	myaudio.attribute.bitsPerSample = 16;
	
	for (int i = 0; i < 441000;++i)
	{
		myaudio.push_back(10000*sin(i)+10000);
	}
	stream::FileOutputStream outstream(file);
	WaveWriter writer(outstream);
	writer.write(myaudio);

	std::fclose(file);
	return 0;
}