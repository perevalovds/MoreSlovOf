#include "ofxSoundUtils.h"
#include "SoundUtils.h"
#include "ofxKuFile.h"
#include "ofxKuDrawRasters.h"

//--------------------------------------------------------------------------------
vector<float> sample_and_hold_random_stereo(vector<float> &sound) {
	cout << "sample_and_hold_random_stereo..." << endl;
	int n = sound.size();
	vector<float> output_stereo(n * 2);
	
	int winner = 0;
	float value[2] = { 0,0 };
	double pos[2] = { 0,0 };	//положение для воспроизведения "в обратную сторону" не победителей
	double pos0[2] = { 0,0 };
	double speed[2] = { 1,1 };
	double speed_down[2] = { 1,1 };

	//вероятность переключения
	float switch_prop = //0.001;//0.01; //0.1;	// 0.3;
		0.0001;

	//замедление реверса, зависит от нейросети
	double speed_down0 = //0.999;  
		0.99995;	
	double speed_down1 = 
		0.99990;	
	
	//скорость возврата в звук
	double speed_up = 0.999;  

	for (int i = 0; i < n; i++) {
		float p = ofRandom(1);
		//переключение победителя
		if (p < switch_prop) {
			winner = 1 - winner;

			//для ускорения
			int k = winner;
			pos0[k] = pos[k];

			//для замедления
			int q = 1 - winner;
			//speed[q] = 1;
			speed_down[q] = ofRandom(speed_down0, speed_down1);
		}

		//ускорение - победитель
		int k = winner;
		speed[k] = 1 - (1 - speed[k]) * speed_up;	//возврат к 1

		pos[k] = ofLerp(pos0[k], i, speed[k]);
		float sound_old = ofxSoundUtils::interpolate_stereo(output_stereo, pos[k], k);
		value[k] = ofLerp(sound_old, sound[i], speed[k]);

		//замедление - проигравший
		//не победитель воспроизводит реверс, замедляющийся
		//как эффект Допплера, как будто он улетает
		int q = 1 - winner;
		pos[q]-=speed[q];
		speed[q] *= speed_down[q]; //замедление

		//взятие с интерполяцией
		value[q] = ofxSoundUtils::interpolate_stereo(output_stereo, pos[q], q);

		output_stereo[i * 2] = value[0];
		output_stereo[i * 2+1] = value[1];
	}

	return output_stereo;


}


//--------------------------------------------------------------------------------
//вычисление статистики фазового пространства
//рекомендуется использовать mu-преобразованный звук
void SpaceStat::setup(int w, int h, float *sound_mono, int n) {
	this->w = w;
	this->h = h;
	v.resize(w*h);

	float amp_y = 2;
	fill(v.begin(), v.end(), 0);
	for (int i = 1; i < n; i++) {
		ofPoint p = ofxSoundUtils::get_sound_amp_vel(sound_mono, i, n);
		int x = int(ofMap(p.x, -1, 1, 0, w, true));
		x = min(max(x, 0), w - 1);
		int y = int(ofMap(p.y * amp_y, -1, 1, 0, h, true));	//при резких скачках тут может быть -2*amp_y,2*amp_y, но считаем это редкостью
		y = min(max(y, 0), h - 1);
		v[x + w * y] += 1;
		//cout << "(" << x << "," << y << ") ";
	}
	int N = n - 1;
	if (N > 0) {
		for (int i = 0; i < w*h; i++) {
			v[i] /= N;
		}
	}
}

//--------------------------------------------------------------------------------
void SpaceStat::setup(int w, int h, vector<float> &sound_mono, int i0, int n) {
	setup(w, h, &sound_mono[i0], n);
}

//--------------------------------------------------------------------------------
void SpaceStat::draw(float x, float y, float W, float H) {
	ofSetColor(255);
	ofxKuDrawRaster(v, w, h, x, y, W, H, 0, 0.1);
}

//--------------------------------------------------------------------------------
