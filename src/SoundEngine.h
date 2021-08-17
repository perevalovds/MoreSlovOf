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


	string callbacks_status_string(); //информация о callbacks - были или нет

protected:
	//поиск устройства по заданной строке вида namepart:portsin:out
	int find_device_by_string(const string &nameports, vector<ofSoundDevice> &devices);
	
	//фильтр микрофона
	ofxSoundUtilsFilter mic_filter[8];

	//буфер для passthru
	vector<float> pass_thru_buf_;
	int pass_thru_buf_n = 0;
	int pass_write_pos_ = 0;
	int pass_read_pos_ = 0;

	//запись звука по педали
	int max_mic_rec_n_ = 1000;
	vector<float> mic_recording_;
	int mic_rec_n_ = 0;
	int mic_rec_on_ = 0;

	vector<float> stereo_buffer_;
};

extern SoundEngine SOUND;