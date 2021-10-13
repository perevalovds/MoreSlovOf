#pragma once

//Звуковой движок
//Осуществляет подключение звуковой карты
//А для создания звука - пересылает вызовы в DAEMONS

#include "ofMain.h"
#include "Common.h"
#include "ofxSoundUtils.h"

struct SoundEngine {
	void setup();
	void update();
	void draw();
	void exit();

	bool toggleFileRecording();	//запись в WAV

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
	int pedal_index_ = 0;	//0 - техно, 1 - повторы, у техно - приоритет

	vector<float> stereo_buffer_;

	//Recording
	bool wav_recfile_ = false;
	const int wav_duration_sec = 60 * 60;		//час записи
	int wav_duration_samples = 0; //устанавливается в setup

	void recfile_setup();		//буферы для записи выделяются сразу, на час
	void recfile_start();
	void recfile_stop();   //Внимание, после этой функции wavsnd_ портится - в него пишем микс

	void wav_write_sound_sample(float mic, float sndL, float sndR);	//записать очередной звуковой сэмпл в WAV-буферы
	vector<short> wavmic_, wavsnd_;	//стереобуферы
	int wavpos_ = 0;
	string wav_file_name_;

};

extern SoundEngine SOUND;