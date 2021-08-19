#include "gui_generated.h"
//Auto-generated GUI file for ofxKuTextGui, 2021-08-19-09-41-33-066

Parameters params;
//--------------------------------------------------------------
Parameters::Parameters() {
	ClearLog=0;
	Save=0;
	Exit=0;
	fps_=0;
	vol_in_=0;
	vol_out_=0;
	_FPS_=70;
	_FULL_SCR_=2;
	update_scr=0;
	_scr_x_=20;
	_scr_y_=20;
	_scr_w_=1000;
	_scr_h_=800;
	_messages_n_=25;
	_messages_font_=25;
	_messages_x_=20;
	_messages_y_=320;
	_OSC_in_port_=12400;
	_in_channels_=2;
	_out_channel_start_=1;
	_out_channels_=2;
	_sample_rate_=4;
	_sound_buffers_=4;
	_sound_buffer_=512;
	sound_buffer_=512;
	_engine_=2;
	_selectby_=0;
	_device_in_=0;
	_device_out_=0;
	_devin_nameports_="...:...:..";
	_devout_nameports_="...:...:..";
	device_in_name_="";
	device_out_name_="";
	SOUND_STATUS_=0;
	SND_CALLB_="NO";
	ShowDevices=0;
	MIC_VOL=1;
	MIC_FILTER=0;
	mic_cutoff=0.1;
	PASS_THRU=0;
	PASS_VOL=1;
	SEA_VOL=1;
	pass_thru_delta_="0";
	OUT_VOL=1;
	_Arduino_Pedal_=0;
	_Pedal_baud_="57600";
	Pedal_invert=0;
	Pedal_status_="...";
	Print_Arduinos=0;
	PEDAL_=0;
	PEDAL2_=0;
	_APC_midi_in_="APC40";
	_APC_midi_out_="APC40";
	APC_status_="...";
	Print_MIDI=0;
	log_midi=0;
	_max_rec_msec_=10000;
	_max_words_=15;
	_max_polyphony_=10;
	BPM=120;
	Crop_Mode=2;
	Crop_thresh=5;
	Crop_ms=50;
	Crop_fade_ms=10;
	Min_Vol=0.2;
	WORDS_="...";
	REC=0;
	backup1=0;
	backup2=0;
	backup3=0;
	backup4=0;
	backup5=0;
	backup6=0;
	REC1=0;
	w_mode1=0;
	w_delay1=0;
	w_len1=0.5;
	w_spd1=0.5;
	w_grain_len1=0.01;
	w_flt1=0;
	w_cutoff1=0.5;
	w_vol1=0.5;
	w_pan1=0.5;
	w_louder1=0;
	w_voltype1=0;
	w_volstp1=1;
	w_volmov1=0.5;
	w_pantype1=0;
	w_panstp1=1;
	w_panmov1=0.5;
	w_morph1=0;
	w_percent1=0;
	w_pos1=0;
	REC2=0;
	w_mode2=0;
	w_delay2=0;
	w_len2=0.5;
	w_spd2=0.5;
	w_grain_len2=0.01;
	w_flt2=0;
	w_cutoff2=0.5;
	w_vol2=0.5;
	w_pan2=0.5;
	w_louder2=0;
	w_voltype2=0;
	w_volstp2=1;
	w_volmov2=0.5;
	w_pantype2=0;
	w_panstp2=1;
	w_panmov2=0.5;
	w_morph2=0;
	w_percent2=0;
	w_pos2=0;
	REC3=0;
	w_mode3=0;
	w_delay3=0;
	w_len3=0.5;
	w_spd3=0.5;
	w_grain_len3=0.01;
	w_flt3=0;
	w_cutoff3=0.5;
	w_vol3=0.5;
	w_pan3=0.5;
	w_louder3=0;
	w_voltype3=0;
	w_volstp3=1;
	w_volmov3=0.5;
	w_pantype3=0;
	w_panstp3=1;
	w_panmov3=0.5;
	w_morph3=0;
	w_percent3=0;
	w_pos3=0;
	REC4=0;
	w_mode4=0;
	w_delay4=0;
	w_len4=0.5;
	w_spd4=0.5;
	w_grain_len4=0.01;
	w_flt4=0;
	w_cutoff4=0.5;
	w_vol4=0.5;
	w_pan4=0.5;
	w_louder4=0;
	w_voltype4=0;
	w_volstp4=1;
	w_volmov4=0.5;
	w_pantype4=0;
	w_panstp4=1;
	w_panmov4=0.5;
	w_morph4=0;
	w_percent4=0;
	w_pos4=0;
	REC5=0;
	w_mode5=0;
	w_delay5=0;
	w_len5=0.5;
	w_spd5=0.5;
	w_grain_len5=0.01;
	w_flt5=0;
	w_cutoff5=0.5;
	w_vol5=0.5;
	w_pan5=0.5;
	w_louder5=0;
	w_voltype5=0;
	w_volstp5=1;
	w_volmov5=0.5;
	w_pantype5=0;
	w_panstp5=1;
	w_panmov5=0.5;
	w_morph5=0;
	w_percent5=0;
	w_pos5=0;
	REC6=0;
	w_mode6=0;
	w_delay6=0;
	w_len6=0.5;
	w_spd6=0.5;
	w_grain_len6=0.01;
	w_flt6=0;
	w_cutoff6=0.5;
	w_vol6=0.5;
	w_pan6=0.5;
	w_louder6=0;
	w_voltype6=0;
	w_volstp6=1;
	w_volmov6=0.5;
	w_pantype6=0;
	w_panstp6=1;
	w_panmov6=0.5;
	w_morph6=0;
	w_percent6=0;
	w_pos6=0;
	REC7=0;
	w_mode7=0;
	w_delay7=0;
	w_len7=0.5;
	w_spd7=0.5;
	w_grain_len7=0.01;
	w_flt7=0;
	w_cutoff7=0.5;
	w_vol7=0.5;
	w_pan7=0.5;
	w_louder7=0;
	w_voltype7=0;
	w_volstp7=1;
	w_volmov7=0.5;
	w_pantype7=0;
	w_panstp7=1;
	w_panmov7=0.5;
	w_morph7=0;
	w_percent7=0;
	w_pos7=0;
	REP_VOL=0.5;
	w_duration_msec=10000;
	w_evolution_perc=40;
	w_fadeout_perc=10;
	w_repeat0_msec=250;
	w_repeat1_msec=250;
	w_vol_perc=50;
	w_envelope=0;
	w_stereo_range=0;
	w_grain_msec=50;
	w_grain_move_perc=100;
	w_grain_pause_msec=0;
	w_flt=0;
	w_flt_cutoff0=500;
	w_flt_cutoff1=0.5;
	sea_x=400;
	sea_y=20;
	sea_w=1000;
	sea_h=600;
	thumb_x1=100;
	thumb_y=800;
	thumb_w=100;
	thumb_h=50;
	thumb_scl=1;
	thumb_x2=100;
	thumb_x3=100;
	_Backups7_=5;
	backup_x=10;
	backup_y=800;
	thumb_x4=100;
	thumb_x5=100;
	thumb_x6=100;
	thumb_x7=1400;
	SaveDebugSounds=0;
}

//--------------------------------------------------------------
void Parameters::setup(ofxKuTextGui &gui, string fileName) {
	gui.addPage("Settings");
	gui.addButton("ClearLog",ClearLog);
	gui.addButton("Save",Save);
	gui.addButton("Exit",Exit);
	gui.addDummy("");
	gui.addInt("-fps",fps_,0,0,200,1,20);
	gui.addFloat("-vol_in",vol_in_,0,0,1,100,10);
	gui.addFloat("-vol_out",vol_out_,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Screen:");
	gui.addInt("*FPS",_FPS_,70,5,200,1,20);
	gui.addStringList("*FULL_SCR",_FULL_SCR_,2,3,"OFF","BORDERLESS","ON");
	gui.addDummy("Press to update screen:");
	gui.addButton("update_scr",update_scr);
	gui.addTab();
	gui.addDummy("Borderless screen:");
	gui.addInt("*scr_x",_scr_x_,20,-20000,20000,1,20);
	gui.addInt("*scr_y",_scr_y_,20,-20000,20000,1,20);
	gui.addInt("*scr_w",_scr_w_,1000,100,10000,1,20);
	gui.addInt("*scr_h",_scr_h_,800,100,10000,1,20);
	gui.addTab();
	gui.addDummy("Message log:");
	gui.addInt("*messages_n",_messages_n_,25,1,1000,1,10);
	gui.addInt("*messages_font",_messages_font_,25,0,1000,1,10);
	gui.addInt("*messages_x",_messages_x_,20,0,10000,1,20);
	gui.addInt("*messages_y",_messages_y_,320,0,10000,1,20);
	gui.addPage("Network");
	gui.addVar("ClearLog");
	gui.addVar("Save");
	gui.addVar("Exit");
	gui.addDummy("");
	gui.addVar("-fps");
	gui.addVar("-vol_in");
	gui.addVar("-vol_out");
	gui.addTab();
	gui.addDummy("OSC port for Config:");
	gui.addInt("*OSC_in_port",_OSC_in_port_,12400,1,65535,1,20);
	gui.addPage("SoundSetup");
	gui.addVar("ClearLog");
	gui.addVar("Save");
	gui.addVar("Exit");
	gui.addDummy("");
	gui.addVar("-fps");
	gui.addVar("-vol_in");
	gui.addVar("-vol_out");
	gui.addTab();
	gui.addDummy("Channels setup:");
	gui.addInt("*in_channels",_in_channels_,2,1,8,1,10);
	gui.addInt("*out_channel_start",_out_channel_start_,1,1,8,1,10);
	gui.addInt("*out_channels",_out_channels_,2,1,8,1,10);
	gui.addDummy("Sound setup:");
	gui.addStringList("*sample_rate",_sample_rate_,4,6,"8000","11025","22050","32000","44100","48000");
	gui.addInt("*sound_buffers",_sound_buffers_,4,1,16,1,10);
	gui.addInt("*sound_buffer",_sound_buffer_,512,8,4096,1,50);
	gui.addInt("-sound_buffer",sound_buffer_,512,8,4096,1,50);
	gui.addTab();
	gui.addDummy("Select devices:");
	gui.addStringList("*engine",_engine_,2,3,"WASAPI","ASIO","DS");
	gui.addStringList("*selectby",_selectby_,0,2,"ID","NAME");
	gui.addInt("*device_in",_device_in_,0,-1,20,1,10);
	gui.addInt("*device_out",_device_out_,0,-1,20,1,10);
	gui.addDummy("namepart:portsin:out");
	gui.addString("*devin_nameports",_devin_nameports_,"...:...:..");
	gui.addString("*devout_nameports",_devout_nameports_,"...:...:..");
	gui.addTab();
	gui.addDummy("Started devices:");
	gui.addString("-device_in_name",device_in_name_,"");
	gui.addString("-device_out_name",device_out_name_,"");
	gui.addDummy("Status:");
	gui.addStringList("-SOUND_STATUS",SOUND_STATUS_,0,2,"NOT_STARTED","STARTED");
	gui.addString("-SND_CALLB",SND_CALLB_,"NO");
	gui.addDummy("");
	gui.addDummy("");
	gui.addDummy("");
	gui.addButton("ShowDevices",ShowDevices);
	gui.addDummy("");
	gui.addDummy("MIC");
	gui.addFloat("MIC_VOL",MIC_VOL,1,0,100,1000,100);
	gui.addStringList("MIC_FILTER",MIC_FILTER,0,4,"BYPASS","LOWPASS","HIGHPASS","BANDPASS");
	gui.addFloat("mic_cutoff",mic_cutoff,0.1,0,1,1000,100);
	gui.addDummy("MIXER:");
	gui.addStringList("PASS_THRU",PASS_THRU,0,2,"OFF","ON");
	gui.addFloat("PASS_VOL",PASS_VOL,1,0,10,1000,100);
	gui.addFloat("SEA_VOL",SEA_VOL,1,0,10,1000,100);
	gui.addString("-pass_thru_delta",pass_thru_delta_,"0");
	gui.addDummy("Resulted sound:");
	gui.addFloat("OUT_VOL",OUT_VOL,1,0,10,1000,100);
	gui.addPage("PedalPult");
	gui.addStringList("*Arduino_Pedal",_Arduino_Pedal_,0,2,"OFF","ON");
	gui.addString("*Pedal_baud",_Pedal_baud_,"57600");
	gui.addStringList("Pedal_invert",Pedal_invert,0,2,"NORMAL","INVERTED");
	gui.addDummy("");
	gui.addString("-Pedal_status",Pedal_status_,"...");
	gui.addButton("Print_Arduinos",Print_Arduinos);
	gui.addTab();
	gui.addDummy("techno_keyZ");
	gui.addStringList("-PEDAL",PEDAL_,0,2,"OFF","ON");
	gui.addDummy("repeats_keySpace");
	gui.addStringList("-PEDAL2",PEDAL2_,0,2,"OFF","ON");
	gui.addTab();
	gui.addDummy("APC40");
	gui.addString("*APC_midi_in",_APC_midi_in_,"APC40");
	gui.addString("*APC_midi_out",_APC_midi_out_,"APC40");
	gui.addDummy("");
	gui.addString("-APC_status",APC_status_,"...");
	gui.addButton("Print_MIDI",Print_MIDI);
	gui.addDummy("");
	gui.addStringList("log_midi",log_midi,0,2,"OFF","ON");
	gui.addTab();
	gui.addTab();
	gui.addDummy("Sea_Params");
	gui.addInt("*max_rec_msec",_max_rec_msec_,10000,1000,10000,100,1000);
	gui.addInt("*max_words",_max_words_,15,5,100,1,10);
	gui.addInt("*max_polyphony",_max_polyphony_,10,1,20,1,10);
	gui.addDummy("");
	gui.addInt("BPM",BPM,120,60,200,1,10);
	gui.addDummy("");
	gui.addDummy("Crop_Record");
	gui.addStringList("Crop_Mode",Crop_Mode,2,3,"OFF","Manual","Auto");
	gui.addInt("Crop_thresh",Crop_thresh,5,0,100,1,10);
	gui.addInt("Crop_ms",Crop_ms,50,0,1000,5,50);
	gui.addInt("Crop_fade_ms",Crop_fade_ms,10,0,100,1,10);
	gui.addFloat("Min_Vol",Min_Vol,0.2,0,1,1000,100);
	gui.addPage("Sea");
	gui.addVar("-vol_in");
	gui.addVar("-vol_out");
	gui.addDummy("");
	gui.addString("-WORDS",WORDS_,"...");
	gui.addDummy("");
	gui.addVar("-PEDAL");
	gui.addVar("-PEDAL2");
	gui.addDummy("");
	gui.addStringList("REC",REC,0,7,"Techno1","Techno2","Techno3","Techno4","Techno5","Techno6","Techno7");
	gui.addDummy("Backups");
	gui.addButton("backup1",backup1);
	gui.addButton("backup2",backup2);
	gui.addButton("backup3",backup3);
	gui.addButton("backup4",backup4);
	gui.addButton("backup5",backup5);
	gui.addButton("backup6",backup6);
	gui.addTab();
	gui.addDummy("Techno1");
	gui.addStringList("REC1",REC1,0,2,"OFF","ON");
	gui.addStringList("w_mode1",w_mode1,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay1",w_delay1,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len1",w_len1,0.5,0,1,200,20);
	gui.addFloat("w_spd1",w_spd1,0.5,0,1,100,10);
	gui.addFloat("w_grain_len1",w_grain_len1,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt1",w_flt1,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff1",w_cutoff1,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol1",w_vol1,0.5,0,1,100,10);
	gui.addFloat("w_pan1",w_pan1,0.5,0,1,100,10);
	gui.addStringList("w_louder1",w_louder1,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype1",w_voltype1,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp1",w_volstp1,1,1,64,1,10);
	gui.addFloat("w_volmov1",w_volmov1,0.5,0,1,100,10);
	gui.addStringList("w_pantype1",w_pantype1,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp1",w_panstp1,1,1,64,1,10);
	gui.addFloat("w_panmov1",w_panmov1,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph1",w_morph1,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent1",w_percent1,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos1",w_pos1,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Techno2");
	gui.addStringList("REC2",REC2,0,2,"OFF","ON");
	gui.addStringList("w_mode2",w_mode2,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay2",w_delay2,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len2",w_len2,0.5,0,1,200,20);
	gui.addFloat("w_spd2",w_spd2,0.5,0,1,100,10);
	gui.addFloat("w_grain_len2",w_grain_len2,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt2",w_flt2,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff2",w_cutoff2,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol2",w_vol2,0.5,0,1,100,10);
	gui.addFloat("w_pan2",w_pan2,0.5,0,1,100,10);
	gui.addStringList("w_louder2",w_louder2,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype2",w_voltype2,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp2",w_volstp2,1,1,64,1,10);
	gui.addFloat("w_volmov2",w_volmov2,0.5,0,1,100,10);
	gui.addStringList("w_pantype2",w_pantype2,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp2",w_panstp2,1,1,64,1,10);
	gui.addFloat("w_panmov2",w_panmov2,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph2",w_morph2,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent2",w_percent2,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos2",w_pos2,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Techno3");
	gui.addStringList("REC3",REC3,0,2,"OFF","ON");
	gui.addStringList("w_mode3",w_mode3,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay3",w_delay3,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len3",w_len3,0.5,0,1,200,20);
	gui.addFloat("w_spd3",w_spd3,0.5,0,1,100,10);
	gui.addFloat("w_grain_len3",w_grain_len3,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt3",w_flt3,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff3",w_cutoff3,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol3",w_vol3,0.5,0,1,100,10);
	gui.addFloat("w_pan3",w_pan3,0.5,0,1,100,10);
	gui.addStringList("w_louder3",w_louder3,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype3",w_voltype3,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp3",w_volstp3,1,1,64,1,10);
	gui.addFloat("w_volmov3",w_volmov3,0.5,0,1,100,10);
	gui.addStringList("w_pantype3",w_pantype3,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp3",w_panstp3,1,1,64,1,10);
	gui.addFloat("w_panmov3",w_panmov3,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph3",w_morph3,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent3",w_percent3,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos3",w_pos3,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Techno4");
	gui.addStringList("REC4",REC4,0,2,"OFF","ON");
	gui.addStringList("w_mode4",w_mode4,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay4",w_delay4,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len4",w_len4,0.5,0,1,200,20);
	gui.addFloat("w_spd4",w_spd4,0.5,0,1,100,10);
	gui.addFloat("w_grain_len4",w_grain_len4,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt4",w_flt4,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff4",w_cutoff4,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol4",w_vol4,0.5,0,1,100,10);
	gui.addFloat("w_pan4",w_pan4,0.5,0,1,100,10);
	gui.addStringList("w_louder4",w_louder4,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype4",w_voltype4,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp4",w_volstp4,1,1,64,1,10);
	gui.addFloat("w_volmov4",w_volmov4,0.5,0,1,100,10);
	gui.addStringList("w_pantype4",w_pantype4,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp4",w_panstp4,1,1,64,1,10);
	gui.addFloat("w_panmov4",w_panmov4,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph4",w_morph4,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent4",w_percent4,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos4",w_pos4,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Techno5");
	gui.addStringList("REC5",REC5,0,2,"OFF","ON");
	gui.addStringList("w_mode5",w_mode5,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay5",w_delay5,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len5",w_len5,0.5,0,1,200,20);
	gui.addFloat("w_spd5",w_spd5,0.5,0,1,100,10);
	gui.addFloat("w_grain_len5",w_grain_len5,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt5",w_flt5,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff5",w_cutoff5,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol5",w_vol5,0.5,0,1,100,10);
	gui.addFloat("w_pan5",w_pan5,0.5,0,1,100,10);
	gui.addStringList("w_louder5",w_louder5,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype5",w_voltype5,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp5",w_volstp5,1,1,64,1,10);
	gui.addFloat("w_volmov5",w_volmov5,0.5,0,1,100,10);
	gui.addStringList("w_pantype5",w_pantype5,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp5",w_panstp5,1,1,64,1,10);
	gui.addFloat("w_panmov5",w_panmov5,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph5",w_morph5,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent5",w_percent5,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos5",w_pos5,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Techno6");
	gui.addStringList("REC6",REC6,0,2,"OFF","ON");
	gui.addStringList("w_mode6",w_mode6,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay6",w_delay6,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len6",w_len6,0.5,0,1,200,20);
	gui.addFloat("w_spd6",w_spd6,0.5,0,1,100,10);
	gui.addFloat("w_grain_len6",w_grain_len6,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt6",w_flt6,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff6",w_cutoff6,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol6",w_vol6,0.5,0,1,100,10);
	gui.addFloat("w_pan6",w_pan6,0.5,0,1,100,10);
	gui.addStringList("w_louder6",w_louder6,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype6",w_voltype6,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp6",w_volstp6,1,1,64,1,10);
	gui.addFloat("w_volmov6",w_volmov6,0.5,0,1,100,10);
	gui.addStringList("w_pantype6",w_pantype6,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp6",w_panstp6,1,1,64,1,10);
	gui.addFloat("w_panmov6",w_panmov6,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph6",w_morph6,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent6",w_percent6,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos6",w_pos6,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Techno7");
	gui.addStringList("REC7",REC7,0,2,"OFF","ON");
	gui.addStringList("w_mode7",w_mode7,0,3,"GRAIN","SPECTR","DELAY");
	gui.addStringList("w_delay7",w_delay7,0,7,"64","32","16","8","4","2","1");
	gui.addFloat("w_len7",w_len7,0.5,0,1,200,20);
	gui.addFloat("w_spd7",w_spd7,0.5,0,1,100,10);
	gui.addFloat("w_grain_len7",w_grain_len7,0.01,0.002,0.1,100,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt7",w_flt7,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addFloat("w_cutoff7",w_cutoff7,0.5,0,1,200,20);
	gui.addDummy("Vol-Pan");
	gui.addFloat("w_vol7",w_vol7,0.5,0,1,100,10);
	gui.addFloat("w_pan7",w_pan7,0.5,0,1,100,10);
	gui.addStringList("w_louder7",w_louder7,0,2,"OFF","ON");
	gui.addDummy("LFO");
	gui.addStringList("w_voltype7",w_voltype7,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_volstp7",w_volstp7,1,1,64,1,10);
	gui.addFloat("w_volmov7",w_volmov7,0.5,0,1,100,10);
	gui.addStringList("w_pantype7",w_pantype7,0,8,"const","up","down","rand","sin","-sin","cos","-cos");
	gui.addInt("w_panstp7",w_panstp7,1,1,64,1,10);
	gui.addFloat("w_panmov7",w_panmov7,0.5,0,1,100,10);
	gui.addDummy("Morph");
	gui.addStringList("w_morph7",w_morph7,0,4,"file1","file2","file3","file4");
	gui.addInt("w_percent7",w_percent7,0,0,100,1,10);
	gui.addDummy("Pos");
	gui.addFloat("w_pos7",w_pos7,0,0,1,100,10);
	gui.addTab();
	gui.addDummy("Repeats");
	gui.addDummy("");
	gui.addDummy("");
	gui.addFloat("REP_VOL",REP_VOL,0.5,0,1,100,10);
	gui.addDummy("");
	gui.addInt("w_duration_msec",w_duration_msec,10000,100,60000,10,500);
	gui.addInt("w_evolution_perc",w_evolution_perc,40,1,100,1,10);
	gui.addInt("w_fadeout_perc",w_fadeout_perc,10,1,100,1,10);
	gui.addDummy("Repeats");
	gui.addInt("w_repeat0_msec",w_repeat0_msec,250,0,1000,10,100);
	gui.addInt("w_repeat1_msec",w_repeat1_msec,250,0,1000,10,100);
	gui.addDummy("Vol_Stereo");
	gui.addInt("w_vol_perc",w_vol_perc,50,0,100,1,10);
	gui.addStringList("w_envelope",w_envelope,0,3,"const","fadeout","fadein");
	gui.addInt("w_stereo_range",w_stereo_range,0,0,100,1,10);
	gui.addDummy("Granular");
	gui.addInt("w_grain_msec",w_grain_msec,50,1,1000,1,10);
	gui.addInt("w_grain_move_perc",w_grain_move_perc,100,0,200,1,10);
	gui.addInt("w_grain_pause_msec",w_grain_pause_msec,0,0,1000,1,10);
	gui.addDummy("Filter");
	gui.addStringList("w_flt",w_flt,0,4,"No","Lopass","Hipass","Bandpass");
	gui.addInt("w_flt_cutoff0",w_flt_cutoff0,500,0,1000,5,50);
	gui.addInt("w_flt_cutoff1",w_flt_cutoff1,0.5,0,1000,5,50);
	gui.addPage("Draw");
	gui.addDummy("");
	gui.addInt("sea_x",sea_x,400,0,2000,10,50);
	gui.addInt("sea_y",sea_y,20,0,2000,10,50);
	gui.addInt("sea_w",sea_w,1000,0,2000,10,50);
	gui.addInt("sea_h",sea_h,600,0,2000,10,50);
	gui.addTab();
	gui.addDummy("Techno1");
	gui.addInt("thumb_x1",thumb_x1,100,0,2000,1,20);
	gui.addDummy("");
	gui.addInt("thumb_y",thumb_y,800,0,2000,1,20);
	gui.addInt("thumb_w",thumb_w,100,1,300,1,20);
	gui.addInt("thumb_h",thumb_h,50,1,300,1,20);
	gui.addDummy("");
	gui.addFloat("thumb_scl",thumb_scl,1,0,10,1000,100);
	gui.addTab();
	gui.addDummy("Techno2");
	gui.addInt("thumb_x2",thumb_x2,100,0,2000,1,20);
	gui.addTab();
	gui.addDummy("Techno3");
	gui.addInt("thumb_x3",thumb_x3,100,0,2000,1,20);
	gui.addDummy("");
	gui.addDummy("Backups7");
	gui.addInt("*Backups7",_Backups7_,5,1,10,1,10);
	gui.addInt("backup_x",backup_x,10,0,2000,1,20);
	gui.addInt("backup_y",backup_y,800,0,2000,1,20);
	gui.addTab();
	gui.addDummy("Techno4");
	gui.addInt("thumb_x4",thumb_x4,100,0,2000,1,20);
	gui.addTab();
	gui.addDummy("Techno5");
	gui.addInt("thumb_x5",thumb_x5,100,0,2000,1,20);
	gui.addTab();
	gui.addDummy("Techno6");
	gui.addInt("thumb_x6",thumb_x6,100,0,2000,1,20);
	gui.addTab();
	gui.addDummy("Techno7");
	gui.addInt("thumb_x7",thumb_x7,1400,0,2000,1,20);
	gui.addPage("Debug");
	gui.addVar("ClearLog");
	gui.addVar("Save");
	gui.addVar("Exit");
	gui.addDummy("");
	gui.addVar("-fps");
	gui.addVar("-vol_in");
	gui.addVar("-vol_out");
	gui.addTab();
	gui.addTab();
	gui.addStringList("SaveDebugSounds",SaveDebugSounds,0,2,"OFF","ON");
	gui.set_var_color("Save", ofColor(255,255,140));
	gui.set_var_color("Exit", ofColor(255,255,140));
	gui.set_var_color("*FPS", ofColor(255,140,255));
	gui.set_var_color("*FULL_SCR", ofColor(255,140,255));
	gui.set_var_color("update_scr", ofColor(255,140,255));
	gui.set_var_color("*scr_x", ofColor(255,140,255));
	gui.set_var_color("*scr_y", ofColor(255,140,255));
	gui.set_var_color("*scr_w", ofColor(255,140,255));
	gui.set_var_color("*scr_h", ofColor(255,140,255));
	gui.set_var_color("*in_channels", ofColor(255,140,140));
	gui.set_var_color("*out_channel_start", ofColor(255,140,140));
	gui.set_var_color("*out_channels", ofColor(255,140,140));
	gui.set_var_color("*sample_rate", ofColor(255,140,140));
	gui.set_var_color("*sound_buffers", ofColor(255,140,140));
	gui.set_var_color("*sound_buffer", ofColor(255,140,140));
	gui.set_var_color("-sound_buffer", ofColor(200,200,200));
	gui.set_var_color("*engine", ofColor(255,140,140));
	gui.set_var_color("*selectby", ofColor(255,140,140));
	gui.set_var_color("*device_in", ofColor(255,140,140));
	gui.set_var_color("*device_out", ofColor(255,140,140));
	gui.set_var_color("*devin_nameports", ofColor(255,140,140));
	gui.set_var_color("*devout_nameports", ofColor(255,140,140));
	gui.set_var_color("-device_in_name", ofColor(255,140,140));
	gui.set_var_color("-device_out_name", ofColor(255,140,140));
	gui.set_var_color("-SOUND_STATUS", ofColor(255,255,0));
	gui.set_var_color("-SND_CALLB", ofColor(255,255,0));
	gui.set_var_color("ShowDevices", ofColor(255,255,0));
	gui.set_var_color("MIC_VOL", ofColor(100,255,100));
	gui.set_var_color("MIC_FILTER", ofColor(100,255,100));
	gui.set_var_color("mic_cutoff", ofColor(100,255,100));
	gui.set_var_color("PASS_THRU", ofColor(255,100,100));
	gui.set_var_color("PASS_VOL", ofColor(255,100,100));
	gui.set_var_color("SEA_VOL", ofColor(255,100,100));
	gui.set_var_color("-pass_thru_delta", ofColor(200,200,200));
	gui.set_var_color("OUT_VOL", ofColor(255,100,100));
	gui.set_var_color("*Arduino_Pedal", ofColor(100,100,255));
	gui.set_var_color("*Pedal_baud", ofColor(100,100,255));
	gui.set_var_color("Pedal_invert", ofColor(100,100,255));
	gui.set_var_color("-Pedal_status", ofColor(255,255,100));
	gui.set_var_color("Print_Arduinos", ofColor(255,255,100));
	gui.set_var_color("-PEDAL", ofColor(255,100,100));
	gui.set_var_color("-PEDAL2", ofColor(255,100,100));
	gui.set_var_color("*APC_midi_in", ofColor(100,100,255));
	gui.set_var_color("*APC_midi_out", ofColor(100,100,255));
	gui.set_var_color("-APC_status", ofColor(255,255,100));
	gui.set_var_color("Print_MIDI", ofColor(255,255,100));
	gui.set_var_color("log_midi", ofColor(255,255,100));
	gui.set_var_color("*max_rec_msec", ofColor(255,100,100));
	gui.set_var_color("*max_words", ofColor(255,100,100));
	gui.set_var_color("*max_polyphony", ofColor(255,100,100));
	gui.set_var_color("BPM", ofColor(100,100,255));
	gui.set_var_color("Crop_Mode", ofColor(200,100,100));
	gui.set_var_color("Crop_thresh", ofColor(200,100,100));
	gui.set_var_color("Crop_ms", ofColor(200,100,100));
	gui.set_var_color("Crop_fade_ms", ofColor(200,100,100));
	gui.set_var_color("Min_Vol", ofColor(200,100,100));
	gui.set_var_color("-WORDS", ofColor(255,255,100));
	gui.set_var_color("REC", ofColor(255,255,100));
	gui.set_var_color("backup1", ofColor(200,200,200));
	gui.set_var_color("backup2", ofColor(200,200,200));
	gui.set_var_color("backup3", ofColor(200,200,200));
	gui.set_var_color("backup4", ofColor(200,200,200));
	gui.set_var_color("backup5", ofColor(200,200,200));
	gui.set_var_color("backup6", ofColor(200,200,200));
	gui.set_var_color("REC1", ofColor(255,100,100));
	gui.set_var_color("w_mode1", ofColor(255,100,255));
	gui.set_var_color("w_delay1", ofColor(255,100,255));
	gui.set_var_color("w_len1", ofColor(255,100,255));
	gui.set_var_color("w_spd1", ofColor(255,100,255));
	gui.set_var_color("w_grain_len1", ofColor(255,100,255));
	gui.set_var_color("w_flt1", ofColor(100,100,255));
	gui.set_var_color("w_cutoff1", ofColor(100,100,255));
	gui.set_var_color("w_vol1", ofColor(255,100,100));
	gui.set_var_color("w_pan1", ofColor(255,100,100));
	gui.set_var_color("w_louder1", ofColor(255,100,100));
	gui.set_var_color("w_voltype1", ofColor(100,100,255));
	gui.set_var_color("w_volstp1", ofColor(100,100,255));
	gui.set_var_color("w_volmov1", ofColor(100,100,255));
	gui.set_var_color("w_pantype1", ofColor(100,100,255));
	gui.set_var_color("w_panstp1", ofColor(100,100,255));
	gui.set_var_color("w_panmov1", ofColor(100,100,255));
	gui.set_var_color("w_morph1", ofColor(255,100,100));
	gui.set_var_color("w_percent1", ofColor(255,100,100));
	gui.set_var_color("w_pos1", ofColor(255,100,255));
	gui.set_var_color("REC2", ofColor(255,100,100));
	gui.set_var_color("w_mode2", ofColor(255,100,255));
	gui.set_var_color("w_delay2", ofColor(255,100,255));
	gui.set_var_color("w_len2", ofColor(255,100,255));
	gui.set_var_color("w_spd2", ofColor(255,100,255));
	gui.set_var_color("w_grain_len2", ofColor(255,100,255));
	gui.set_var_color("w_flt2", ofColor(100,100,255));
	gui.set_var_color("w_cutoff2", ofColor(100,100,255));
	gui.set_var_color("w_vol2", ofColor(255,100,100));
	gui.set_var_color("w_pan2", ofColor(255,100,100));
	gui.set_var_color("w_louder2", ofColor(255,100,100));
	gui.set_var_color("w_voltype2", ofColor(100,100,255));
	gui.set_var_color("w_volstp2", ofColor(100,100,255));
	gui.set_var_color("w_volmov2", ofColor(100,100,255));
	gui.set_var_color("w_pantype2", ofColor(100,100,255));
	gui.set_var_color("w_panstp2", ofColor(100,100,255));
	gui.set_var_color("w_panmov2", ofColor(100,100,255));
	gui.set_var_color("w_morph2", ofColor(255,100,100));
	gui.set_var_color("w_percent2", ofColor(255,100,100));
	gui.set_var_color("w_pos2", ofColor(255,100,255));
	gui.set_var_color("REC3", ofColor(255,100,100));
	gui.set_var_color("w_mode3", ofColor(255,100,255));
	gui.set_var_color("w_delay3", ofColor(255,100,255));
	gui.set_var_color("w_len3", ofColor(255,100,255));
	gui.set_var_color("w_spd3", ofColor(255,100,255));
	gui.set_var_color("w_grain_len3", ofColor(255,100,255));
	gui.set_var_color("w_flt3", ofColor(100,100,255));
	gui.set_var_color("w_cutoff3", ofColor(100,100,255));
	gui.set_var_color("w_vol3", ofColor(255,100,100));
	gui.set_var_color("w_pan3", ofColor(255,100,100));
	gui.set_var_color("w_louder3", ofColor(255,100,100));
	gui.set_var_color("w_voltype3", ofColor(100,100,255));
	gui.set_var_color("w_volstp3", ofColor(100,100,255));
	gui.set_var_color("w_volmov3", ofColor(100,100,255));
	gui.set_var_color("w_pantype3", ofColor(100,100,255));
	gui.set_var_color("w_panstp3", ofColor(100,100,255));
	gui.set_var_color("w_panmov3", ofColor(100,100,255));
	gui.set_var_color("w_morph3", ofColor(255,100,100));
	gui.set_var_color("w_percent3", ofColor(255,100,100));
	gui.set_var_color("w_pos3", ofColor(255,100,255));
	gui.set_var_color("REC4", ofColor(255,100,100));
	gui.set_var_color("w_mode4", ofColor(255,100,255));
	gui.set_var_color("w_delay4", ofColor(255,100,255));
	gui.set_var_color("w_len4", ofColor(255,100,255));
	gui.set_var_color("w_spd4", ofColor(255,100,255));
	gui.set_var_color("w_grain_len4", ofColor(255,100,255));
	gui.set_var_color("w_flt4", ofColor(100,100,255));
	gui.set_var_color("w_cutoff4", ofColor(100,100,255));
	gui.set_var_color("w_vol4", ofColor(255,100,100));
	gui.set_var_color("w_pan4", ofColor(255,100,100));
	gui.set_var_color("w_louder4", ofColor(255,100,100));
	gui.set_var_color("w_voltype4", ofColor(100,100,255));
	gui.set_var_color("w_volstp4", ofColor(100,100,255));
	gui.set_var_color("w_volmov4", ofColor(100,100,255));
	gui.set_var_color("w_pantype4", ofColor(100,100,255));
	gui.set_var_color("w_panstp4", ofColor(100,100,255));
	gui.set_var_color("w_panmov4", ofColor(100,100,255));
	gui.set_var_color("w_morph4", ofColor(255,100,100));
	gui.set_var_color("w_percent4", ofColor(255,100,100));
	gui.set_var_color("w_pos4", ofColor(255,100,255));
	gui.set_var_color("REC5", ofColor(255,100,100));
	gui.set_var_color("w_mode5", ofColor(255,100,255));
	gui.set_var_color("w_delay5", ofColor(255,100,255));
	gui.set_var_color("w_len5", ofColor(255,100,255));
	gui.set_var_color("w_spd5", ofColor(255,100,255));
	gui.set_var_color("w_grain_len5", ofColor(255,100,255));
	gui.set_var_color("w_flt5", ofColor(100,100,255));
	gui.set_var_color("w_cutoff5", ofColor(100,100,255));
	gui.set_var_color("w_vol5", ofColor(255,100,100));
	gui.set_var_color("w_pan5", ofColor(255,100,100));
	gui.set_var_color("w_louder5", ofColor(255,100,100));
	gui.set_var_color("w_voltype5", ofColor(100,100,255));
	gui.set_var_color("w_volstp5", ofColor(100,100,255));
	gui.set_var_color("w_volmov5", ofColor(100,100,255));
	gui.set_var_color("w_pantype5", ofColor(100,100,255));
	gui.set_var_color("w_panstp5", ofColor(100,100,255));
	gui.set_var_color("w_panmov5", ofColor(100,100,255));
	gui.set_var_color("w_morph5", ofColor(255,100,100));
	gui.set_var_color("w_percent5", ofColor(255,100,100));
	gui.set_var_color("w_pos5", ofColor(255,100,255));
	gui.set_var_color("REC6", ofColor(255,100,100));
	gui.set_var_color("w_mode6", ofColor(255,100,255));
	gui.set_var_color("w_delay6", ofColor(255,100,255));
	gui.set_var_color("w_len6", ofColor(255,100,255));
	gui.set_var_color("w_spd6", ofColor(255,100,255));
	gui.set_var_color("w_grain_len6", ofColor(255,100,255));
	gui.set_var_color("w_flt6", ofColor(100,100,255));
	gui.set_var_color("w_cutoff6", ofColor(100,100,255));
	gui.set_var_color("w_vol6", ofColor(255,100,100));
	gui.set_var_color("w_pan6", ofColor(255,100,100));
	gui.set_var_color("w_louder6", ofColor(255,100,100));
	gui.set_var_color("w_voltype6", ofColor(100,100,255));
	gui.set_var_color("w_volstp6", ofColor(100,100,255));
	gui.set_var_color("w_volmov6", ofColor(100,100,255));
	gui.set_var_color("w_pantype6", ofColor(100,100,255));
	gui.set_var_color("w_panstp6", ofColor(100,100,255));
	gui.set_var_color("w_panmov6", ofColor(100,100,255));
	gui.set_var_color("w_morph6", ofColor(255,100,100));
	gui.set_var_color("w_percent6", ofColor(255,100,100));
	gui.set_var_color("w_pos6", ofColor(255,100,255));
	gui.set_var_color("REC7", ofColor(100,100,255));
	gui.set_var_color("w_mode7", ofColor(150,150,150));
	gui.set_var_color("w_delay7", ofColor(255,100,255));
	gui.set_var_color("w_len7", ofColor(150,150,150));
	gui.set_var_color("w_spd7", ofColor(150,150,150));
	gui.set_var_color("w_grain_len7", ofColor(150,150,150));
	gui.set_var_color("w_flt7", ofColor(150,150,150));
	gui.set_var_color("w_cutoff7", ofColor(150,150,150));
	gui.set_var_color("w_vol7", ofColor(255,100,100));
	gui.set_var_color("w_pan7", ofColor(255,100,100));
	gui.set_var_color("w_louder7", ofColor(255,100,100));
	gui.set_var_color("w_voltype7", ofColor(150,150,150));
	gui.set_var_color("w_volstp7", ofColor(150,150,150));
	gui.set_var_color("w_volmov7", ofColor(150,150,150));
	gui.set_var_color("w_pantype7", ofColor(150,150,150));
	gui.set_var_color("w_panstp7", ofColor(150,150,150));
	gui.set_var_color("w_panmov7", ofColor(150,150,150));
	gui.set_var_color("w_morph7", ofColor(150,150,150));
	gui.set_var_color("w_percent7", ofColor(150,150,150));
	gui.set_var_color("w_pos7", ofColor(150,150,150));
	gui.set_var_color("REP_VOL", ofColor(255,100,100));
	gui.set_var_color("w_duration_msec", ofColor(255,255,100));
	gui.set_var_color("w_evolution_perc", ofColor(255,255,100));
	gui.set_var_color("w_fadeout_perc", ofColor(255,255,100));
	gui.set_var_color("w_repeat0_msec", ofColor(100,255,100));
	gui.set_var_color("w_repeat1_msec", ofColor(100,255,100));
	gui.set_var_color("w_vol_perc", ofColor(100,100,255));
	gui.set_var_color("w_envelope", ofColor(100,100,255));
	gui.set_var_color("w_stereo_range", ofColor(100,100,255));
	gui.set_var_color("w_grain_msec", ofColor(100,100,255));
	gui.set_var_color("w_grain_move_perc", ofColor(100,100,255));
	gui.set_var_color("w_grain_pause_msec", ofColor(100,100,255));
	gui.set_var_color("w_flt", ofColor(255,255,100));
	gui.set_var_color("w_flt_cutoff0", ofColor(255,255,100));
	gui.set_var_color("w_flt_cutoff1", ofColor(255,255,100));
	gui.set_var_color("sea_x", ofColor(128,128,128));
	gui.set_var_color("sea_y", ofColor(128,128,128));
	gui.set_var_color("sea_w", ofColor(128,128,128));
	gui.set_var_color("sea_h", ofColor(128,128,128));
	gui.set_var_color("thumb_x1", ofColor(200,200,200));
	gui.set_var_color("thumb_y", ofColor(200,200,200));
	gui.set_var_color("thumb_w", ofColor(200,200,200));
	gui.set_var_color("thumb_h", ofColor(200,200,200));
	gui.set_var_color("thumb_scl", ofColor(200,200,200));
	gui.set_var_color("thumb_x2", ofColor(200,200,200));
	gui.set_var_color("thumb_x3", ofColor(200,200,200));
	gui.set_var_color("*Backups7", ofColor(255,100,100));
	gui.set_var_color("backup_x", ofColor(200,200,200));
	gui.set_var_color("backup_y", ofColor(200,200,200));
	gui.set_var_color("thumb_x4", ofColor(200,200,200));
	gui.set_var_color("thumb_x5", ofColor(200,200,200));
	gui.set_var_color("thumb_x6", ofColor(200,200,200));
	gui.set_var_color("thumb_x7", ofColor(200,200,200));
	gui.set_var_color("SaveDebugSounds", ofColor(80,80,255));
	fileName_ = fileName;
	gui_ = &gui;
	gui.loadFromFile(fileName);
	FPS = _FPS_;
	FULL_SCR = _FULL_SCR_;
	scr_x = _scr_x_;
	scr_y = _scr_y_;
	scr_w = _scr_w_;
	scr_h = _scr_h_;
	messages_n = _messages_n_;
	messages_font = _messages_font_;
	messages_x = _messages_x_;
	messages_y = _messages_y_;
	OSC_in_port = _OSC_in_port_;
	in_channels = _in_channels_;
	out_channel_start = _out_channel_start_;
	out_channels = _out_channels_;
	sample_rate = _sample_rate_;
	sound_buffers = _sound_buffers_;
	sound_buffer = _sound_buffer_;
	engine = _engine_;
	selectby = _selectby_;
	device_in = _device_in_;
	device_out = _device_out_;
	devin_nameports = _devin_nameports_;
	devout_nameports = _devout_nameports_;
	Arduino_Pedal = _Arduino_Pedal_;
	Pedal_baud = _Pedal_baud_;
	APC_midi_in = _APC_midi_in_;
	APC_midi_out = _APC_midi_out_;
	max_rec_msec = _max_rec_msec_;
	max_words = _max_words_;
	max_polyphony = _max_polyphony_;
	Backups7 = _Backups7_;
}

//--------------------------------------------------------------
void Parameters::save() {
	gui_->saveToFile(fileName_);
}

//--------------------------------------------------------------

