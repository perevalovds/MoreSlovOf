#pragma once

//Звуковой движок
//Осуществляет подключение звуковой карты
//А для создания звука - пересылает вызовы в DAEMONS

#include "ofMain.h"
#include "ofxSoundUtils.h"

struct SoundEngine {
	void setup();
	void update();
	void draw();
	void exit();

	void show_devices();
	void start_stream();

	//Звук
	void audioIn(ofSoundBuffer &input);
	void audioOut(ofSoundBuffer &output);
	ofSoundStream soundStream;

	int in_started_ = 0;
	int out_started_ = 0;
	int started_ = 0;
	int sound_in_called = 0;
	int sound_out_called = 0;

	//Эмуляция микрофона
	int emulation_in = 0;
	vector<float> emulation_data;
	int emulation_pos = 0;
	ofSoundBuffer emulate_buffer;
	bool setup_emulation_in();
	//при эмуляции мы посылаем на audioIn данные по столько же, как приходит в audioOut
	void emulate_in_perform(const ofSoundBuffer &such_this_buffer);

	string callbacks_status_string(); //информация о callbacks - были или нет

protected:
	//поисе устройства по заданной строке вида namepart:portsin:out
	int find_device_by_string(const string &nameports, vector<ofSoundDevice> &devices);
	
	//фильт микрофона
	ofxSoundUtilsFilter mic_filter[8];

};

extern SoundEngine SOUND;