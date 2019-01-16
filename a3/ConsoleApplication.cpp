// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "al.h"
#include <Windows.h>
#include "alc.h"
#include "alut.h"
#pragma warning(disable: 4996)
//used to maximize screen
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"user32.lib")
using namespace std;
int main()
{
	//tells screen to maximize
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MAXIMIZE);
	cout << "Starting game, original version of game had ascii art here." << endl;
	

	//First we ensure there are audio devices to use
	ALCdevice *device;
	device = alcOpenDevice(NULL);
	if (!device)
	{
		printf("No audio device!");
		exit(1);
	}

	//Create a context for an OpenAL sound scene
	ALCcontext *context;
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		printf("%s", alGetString(alGetError()));
		exit(2);
	}

	float newVolume = 0.05f;

	ALenum error;

	ALuint source[3];
	alGenSources(3, source);

	error = alGetError();
	if (error != AL_NO_ERROR) exit(3);

	// BGM Source: looping true
	alSourcef(source[0], AL_PITCH, 1);
	alSourcef(source[0], AL_GAIN, 1);
	alSource3f(source[0], AL_POSITION, 0, 0, 0);
	alSource3f(source[0], AL_VELOCITY, 0, 0, 0);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);

	// Dialogue source
	alSourcef(source[1], AL_PITCH, 1);
	alSourcef(source[1], AL_GAIN, 1);
	alSource3f(source[1], AL_POSITION, 0, 0, 0);
	alSource3f(source[1], AL_VELOCITY, 0, 0, 0);
	alSourcei(source[1], AL_LOOPING, AL_FALSE);

	// Sound effect source
	alSourcef(source[2], AL_PITCH, 1);
	alSourcef(source[2], AL_GAIN, 1);
	alSource3f(source[2], AL_POSITION, 0, 0, 0);
	alSource3f(source[2], AL_VELOCITY, 0, 0, 0);
	alSourcei(source[2], AL_LOOPING, AL_FALSE);


	// Create one Buffer
	ALuint buffer[50];
	alGenBuffers(50, buffer);
	// buffer 0-13 for dialogue
	// buffer 14-17 for bgm
	//18+ for sound effects

	// Load sound into buffer
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop;

	// dialogue
	alutLoadWAVFile((ALbyte *) "sounds\\helloworld.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[0], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\character_selection.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[1], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\you_have_selected.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[2], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\the_wizard.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[3], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\the_knight.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[4], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\the_goblin.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[5], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\the_demon.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[6], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\the_berzerker.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[7], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\the_banshee.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[8], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\main_menu.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[9], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\armory_main_menu.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[10], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\arena_main_menu.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[11], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\fight_powerup.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[12], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\upgrade_attribute.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[13], format, data, size, freq);

	// bgm
	alutLoadWAVFile((ALbyte *) "sounds\\main_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[14], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\battle_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[15], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\armory_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[16], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\victory_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[17], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\gameover_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[34], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\godomega_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[35], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\godvictory_bgm.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[36], format, data, size, freq);

	// sound effects
	alutLoadWAVFile((ALbyte *) "sounds\\attack.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[18], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\buff sound.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[19], format, data, size, freq);

	alutLoadWAVFile((ALbyte *) "sounds\\heal_bubble.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[21], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\level up.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[22], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\magic.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[23], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\game.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[24], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\opponent_attack.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[25], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\purchase.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[26], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\selection.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[27], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\swing.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[28], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\sword-unsheathe.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[29], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\walking.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[30], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\evil_laugh.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[31], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\soon.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[32], format, data, size, freq);
	alutLoadWAVFile((ALbyte *) "sounds\\experience.wav", &format, &data, &size, &freq, &loop);
	alBufferData(buffer[33], format, data, size, freq);


	// Bind main bgm
	alSourcei(source[0], AL_BUFFER, buffer[14]);
	// Play
	alSourcePlay(source[0]);
	ALint source_state_main;
	alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
	alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);
	alSourcef(source[0], AL_GAIN, newVolume);

	ALfloat position[3];
	ALfloat velocity[3];
	ALfloat orientation[6];
	// Initial position of the listener
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 0.0;

	// Initial velocity of the listener
	velocity[0] = 1.0;
	velocity[1] = 1.0;
	velocity[2] = 1.0;

	// Initial orientation of the listener = direction + direction up
	orientation[0] = 0.0;
	orientation[1] = 0.0;
	orientation[2] = -1.0;
	orientation[3] = 0.0;
	orientation[4] = 1.0;
	orientation[5] = 0.0;

	// Setup the initial listener parameters
	// -> location
	alListenerfv(AL_POSITION, position);

	// -> velocity
	alListenerfv(AL_VELOCITY, velocity);

	// -> orientation
	alListenerfv(AL_ORIENTATION, orientation);
	alSourcei(source[1], AL_BUFFER, buffer[0]);
	// Play!
	alSourcePlay(source[1]);
	ALint source_state;
	alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
	alSourcef(source[1], AL_GAIN, 1.0);
	while (source_state == AL_PLAYING)
	{
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
	}
	system("cls");
	int person, opponent = -1, atk, asuccess, msuccess, game = 1, counter1 = 1, level = 1, atr, a, b, c = 0, d, decision, item;
	//opponent
	int attackop, defenseop, speedop, healthop = 100, opac, expo = 0, moneyo = 0;
	//user
	int magicus, attackus, defenseus, speedus, healthus = 100, exp = 0, money = 0, levelup = 200;
	//names
	string nameus, nameop;
	char exit;
	//classes

	int healus = 0; // TODO: continue playing main music
	do {
		cout << "(1)\n***************\nThe Wizard:\n attack - 30\n defense - 40\n magic - 60\n speed - 60\n***************" << endl << endl;
		cout << "(2)\n***************\nThe Knight:\n attack - 50\n defense - 75\n magic - 40\n speed - 30\n***************" << endl << endl;
		cout << "(3)\n***************\nThe Berzerker:\n attack - 60\n defense - 50\n magic - 30\n speed - 50\n***************" << endl << endl;
		cout << "(4)\n***************\nThe Banshee:\n attack - 40\n defense - 40\n magic - 50\n speed - 65\n***************" << endl << endl;
		cout << "(5)\n***************\nThe Goblin:\n attack - 60\n defense - 65\n magic - 30\n speed - 40\n***************" << endl << endl;
		cout << "(6)\n***************\nThe Demon:\n attack - 65\n defense - 70\n magic - 25\n speed - 30\n***************" << endl << endl;
		cout << "Which Class would you like to be?: ";
		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[1]);
		alSourcePlay(source[1]);
		ALint source_state;
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		cin >> person;
		if ((person > 6) && (person != 666))
		{
			system("cls");
			cout << "You must enter an integer between 1 and 6!!!!\n\n";
			system("pause");
			system("cls");
		}
		if (person == 666)
		{
			system("cls");
			alSourcef(source[0], AL_GAIN, 0.02);
			alSourcei(source[1], AL_BUFFER, buffer[31]); // the wizard
			alSourcef(source[1], AL_GAIN, 0.3);
			alSourcePlay(source[1]);
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
			while (source_state == AL_PLAYING)
			{
				alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
			}
			cout << "Muahahahaha!! You have unleashed Satan!!!";
			cout << "\n***************\nSatan:\n attack - 100\n defense - 100\n magic - 100\n speed - 100\n***************" << endl << endl;
			alSourcef(source[0], AL_GAIN, 0.06);
			alSourcef(source[1], AL_GAIN, 1);

			system("pause");
			system("cls");
		}
	} while ((person > 6) && (person != 666));
	//information for user
	switch (person)
	{

	case 1:
		attackus = 30, defenseus = 40, magicus = 60, speedus = 60, nameus = "Wizard";

		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[2]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[3]); // the wizard
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		break;
	case 2:
		attackus = 50, defenseus = 60, magicus = 40, speedus = 40, nameus = "Knight";
		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[2]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}

		alSourcei(source[1], AL_BUFFER, buffer[4]); // the knight
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		break;
	case 3:
		attackus = 60, defenseus = 50, magicus = 30, speedus = 50, nameus = "Berzerker";
		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[27]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[2]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[7]); // the wizard
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		break;
	case 4:
		attackus = 40, defenseus = 40, magicus = 50, speedus = 65, nameus = "Banshee";
		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[27]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[2]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[8]); // the wizard
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		break;
	case 5:
		attackus = 60, defenseus = 65, magicus = 30, speedus = 40, nameus = "Goblin";
		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[27]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[2]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[5]); // the wizard
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		break;
	case 6:
		attackus = 65, defenseus = 70, magicus = 30, speedus = 25, nameus = "Demon";
		alSourcef(source[0], AL_GAIN, 0.02);
		alSourcei(source[1], AL_BUFFER, buffer[27]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[2]); // you have selected
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcei(source[1], AL_BUFFER, buffer[6]); // the wizard
		alSourcePlay(source[1]);
		alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		while (source_state == AL_PLAYING)
		{
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
		}
		alSourcef(source[0], AL_GAIN, 0.06);
		break;
	case 666:
		attackus = 200, defenseus = 200, magicus = 200, speedus = 200, nameus = "Satan";
		money = 10000;
		break;
	default:
		cout << "No One";
	}
	do {
		do {
			system("cls");
			alSourceStop(source[0]);
			alSourcei(source[0], AL_BUFFER, buffer[14]);
			// Play
			alSourcePlay(source[0]);
			ALint source_state_main;
			alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
			alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
			alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

			alSourcef(source[0], AL_GAIN, newVolume);
			alSourcef(source[1], AL_GAIN, 1.3);
			cout << "Hello, " << nameus << ", what would you like to do?\n\n";
			alSourcef(source[0], AL_GAIN, 0.02);
			alSourcei(source[1], AL_BUFFER, buffer[9]); // you have selected
			alSourcePlay(source[1]);
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
			while (source_state == AL_PLAYING)
			{
				alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
			}
			alSourcef(source[0], AL_GAIN, 0.06);
			cout << "(1)\n**********\nGo right to the Arena\n**********\n\n";
			cout << "(2)\n**********\nGo left to the Armory\n**********\n:";
			cin >> decision;
			if (decision == 1)
			{
				alSourcef(source[0], AL_GAIN, 0.02);
				alSourcei(source[1], AL_BUFFER, buffer[30]); // the wizard
				alSourcef(source[1], AL_GAIN, 4);
				alSourcePlay(source[1]);
				alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);

				alSource3i(source[1], AL_POSITION, 5, 0, 0); // left
				alSourcef(source[1], AL_CONE_INNER_ANGLE, 75);
				// 90.1 is the cutoff seems like
				alSourcef(source[1], AL_CONE_OUTER_ANGLE, 92.0);
				alSourcef(source[1], AL_CONE_OUTER_GAIN, 0.0);
				while (source_state == AL_PLAYING)
				{
					alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
				}
				alSourcef(source[1], AL_CONE_INNER_ANGLE, 360);
				// 90.1 is the cutoff seems like
				alSourcef(source[1], AL_CONE_OUTER_ANGLE, 360);
				alSourcef(source[1], AL_CONE_OUTER_GAIN, 1.0);
				alSource3i(source[1], AL_POSITION, 0, 0, 0); // left

			}
			else if (decision == 2)
			{

				alSourcef(source[0], AL_GAIN, 0.02);
				alSourcei(source[1], AL_BUFFER, buffer[30]); // the wizard
				alSourcef(source[1], AL_GAIN, 6);
				alSourcePlay(source[1]);
				alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
				alSource3i(source[1], AL_POSITION, -5, 0, 0); // right
				alSourcef(source[1], AL_CONE_INNER_ANGLE, 75);
				// 90.1 is the cutoff seems like
				alSourcef(source[1], AL_CONE_OUTER_ANGLE, 92.0);
				alSourcef(source[1], AL_CONE_OUTER_GAIN, 0.0);
				while (source_state == AL_PLAYING)
				{
					alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
				}
				alSourcef(source[1], AL_CONE_INNER_ANGLE, 360);
				// 90.1 is the cutoff seems like
				alSourcef(source[1], AL_CONE_OUTER_ANGLE, 360);
				alSourcef(source[1], AL_CONE_OUTER_GAIN, 1.0);
				alSource3i(source[1], AL_POSITION, 0, 0, 0); // left
			}
			switch (decision)
			{
			case 1:
				int random3, random4, random5;
				srand((unsigned)time(0));
				random3 = (rand() % 4) + 1;
				random4 = (rand() % 4) + 1;
				random5 = (rand() % 4) + 1;
				if (healthop == 0)
					healthop = 100;
				system("cls");
				do {

					alSourceStop(source[0]);
					alSourcei(source[0], AL_BUFFER, buffer[15]);
					// Play
					alSourcePlay(source[0]);
					ALint source_state_main;
					alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
					alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
					alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

					alSourcef(source[0], AL_GAIN, newVolume);

					while (source_state_main == AL_PLAYING) {
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state_main);
					}
					alSourcef(source[0], AL_GAIN, 0.02);
					cout << "Welcome to the arena, " << nameus << ", which opponent would you like to face?" << endl;


					alSourcei(source[1], AL_BUFFER, buffer[11]); // you have selected
					alSourcePlay(source[1]);
					alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
					while (source_state == AL_PLAYING)
					{
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
					}
					alSourcef(source[0], AL_GAIN, 0.06);
					d = (level * -1);
					switch (random3)
					{
					case 1:
						if (level <= 1)
						{
							cout << "(" << d + 2 << ")\n***************\nThe Tree(lvl 1):\n attack - 0\n defense - 20\n speed - 0\n***************\n";
							cout << endl;
						}
						break;
					case 2:
						if (level <= 1)
						{
							cout << "(" << d + 2 << ")\n***************\nThe Rock(lvl 1):\n attack - 0\n defense - 30\n speed - 0\n***************\n";
							cout << endl;
						}
						break;
					case 3:
						if (level <= 1)
						{
							cout << "(" << d + 2 << ")\n***************\nThe Computer(lvl 1):\n attack - 0\n defense - 10\n speed - 0\n***************\n";
							cout << endl;
						}
						break;
					case 4:
						if (level <= 1)
						{
							cout << "(" << d + 2 << ")\n***************\nThe Book(lvl 1):\n attack - 0\n defense - 5\n speed - 0\n***************\n";
							cout << endl;
						}
						break;
					default:
						cout << "Can't Happen";
					}
					switch (random4)
					{
					case 1:
						if (level <= 2)
						{
							cout << "(" << d + 3 << ")\n***************\nThe Rat(lvl 2):\n attack - 30\n defense - 20\n speed - 30\n***************\n";
							cout << endl;
						}
						break;
					case 2:
						if (level <= 2)
						{
							cout << "(" << d + 3 << ")\n***************\nThe Cat(lvl 2):\n attack - 40\n defense - 20\n speed - 30\n***************\n";
							cout << endl;
						}
						break;
					case 3:
						if (level <= 2)
						{
							cout << "(" << d + 3 << ")\n***************\nThe Dog(lvl 2):\n attack - 45\n defense - 25\n speed - 30\n***************\n";
							cout << endl;
						}
						break;
					case 4:
						if (level <= 2)
						{
							cout << "(" << d + 3 << ")\n***************\nThe Bat(lvl 2):\n attack - 30\n defense - 20\n speed - 35\n***************\n";
							cout << endl;
						}
						break;
					default:
						cout << "Can't Happen";
					}
					switch (random5)
					{
					case 1:
						if (level <= 3)
						{
							cout << "(" << d + 4 << ")\n***************\nThe Mage(lvl 3):\n attack - 65\n defense - 35\n speed - 45\n***************\n";
							cout << endl;
						}
						break;
					case 2:
						if (level <= 3)
						{
							cout << "(" << d + 4 << ")\n***************\nThe Jackal(lvl 3):\n attack - 60\n defense - 50\n speed - 50\n***************\n";
							cout << endl;
						}
						break;
					case 3:
						if (level <= 3)
						{
							cout << "(" << d + 4 << ")\n***************\nThe Crusader(lvl 3):\n attack - 65\n defense - 55\n speed - 45\n***************\n";
							cout << endl;
						}
						break;
					case 4:
						if (level <= 3)
						{
							cout << "(" << d + 4 << ")\n***************\nThe Wolf(lvl 3):\n attack - 55\n defense - 45\n speed - 55\n***************\n";
							cout << endl;
						}
						break;
					default:
						cout << "Can't Happen";
					}
					switch (random3)
					{
					case 1:
						if ((level <= 4) && (level >= 2))
						{
							cout << "(" << d + 5 << ")\n***************\nThe Assassin(lvl 4):\n attack - 75\n defense - 35\n speed - 55\n***************\n";
							cout << endl;
						}
						break;
					case 2:
						if ((level <= 4) && (level >= 2))
						{
							cout << "(" << d + 5 << ")\n***************\nThe Pacman(lvl 4):\n attack - 65\n defense - 30\n speed - 60\n***************\n";
							cout << endl;
						}
						break;
					case 3:
						if ((level <= 4) && (level >= 2))
						{
							cout << "(" << d + 5 << ")\n***************\nThe Man Eating Bunny(lvl 4):\n attack - 75\n defense - 35\n speed - 55\n***************\n";
							cout << endl;
						}
						break;
					case 4:
						if ((level <= 4) && (level >= 2))
						{
							cout << "(" << d + 5 << ")\n***************\nThe Warlock(lvl 4):\n attack - 70\n defense - 40\n speed - 50\n***************\n";
							cout << endl;
						}
						break;
					default:
						cout << "Can't Happen";
					}
					switch (random4)
					{
					case 1:
						if ((level <= 5) && (level >= 3))
						{
							cout << "(" << d + 6 << ")\n***************\nPoseidon(lvl 5):\n attack - 80\n defense - 45\n speed - 45\n***************\n";
							cout << endl;
						}
						break;
					case 2:
						if ((level <= 5) && (level >= 3))
						{
							cout << "(" << d + 6 << ")\n***************\nMinitaur(lvl 5):\n attack - 65\n defense - 55\n speed - 50\n***************\n";
							cout << endl;
						}
						break;
					case 3:
						if ((level <= 5) && (level >= 3))
						{
							cout << "(" << d + 6 << ")\n***************\nThe Cyclops(lvl 5):\n attack - 75\n defense - 45\n speed - 50\n***************\n";
							cout << endl;
						}
						break;
					case 4:
						if ((level <= 5) && (level >= 3))
						{
							cout << "(" << d + 6 << ")\n***************\nThe Dragon(lvl 5):\n attack - 80\n defense - 55\n speed - 30\n***************\n";
							cout << endl;
						}
						break;
					default:
						cout << "Can't Happen";
					}
					switch (random4)
					{
					case 1:
						if ((level <= 6) && (level >= 4))
						{
							cout << "(" << d + 7 << ")\n***************\nAthena(lvl 6):\n attack - 85\n defense - 55\n speed - 60\n***************\n";
							cout << endl;
						}
						break;
					case 2:
						if ((level <= 6) && (level >= 4))
						{
							cout << "(" << d + 7 << ")\n***************\nZeus(lvl 6):\n attack - 90\n defense - 65\n speed - 55\n***************\n";
							cout << endl;
						}
						break;
					case 3:
						if ((level <= 6) && (level >= 4))
						{
							cout << "(" << d + 7 << ")\n***************\nHades(lvl 6):\n attack - 75\n defense - 70\n speed - 50\n***************\n";
							cout << endl;
						}
						break;
					case 4:
						if ((level <= 6) && (level >= 4))
						{
							cout << "(" << d + 7 << ")\n***************\nOsiris(lvl 6):\n attack - 70\n defense - 60\n speed - 55\n***************\n";
							cout << endl;
						}
						break;
					default:
						cout << "Can't Happen";
					}
					if ((level <= 99) && (level >= 5))
					{
						cout << "(" << d + 8 << ")\n***************\nGod(lvl ?):\n attack - ??\n defense - ??\n speed - ??\n***************\n";
						cout << endl;
					}
					cout << ":";
					cin >> opponent;
					if ((opponent > 3) || (opponent < 1))
					{
						system("cls");
						cout << "You must enter an integer between 1 and 3!!!!\n\n";
						system("pause");
						system("cls");
					}
				} while ((opponent > 3) || (opponent < 1));
				system("cls");
				opponent = opponent + c;
				switch (opponent)
				{
				case 1:
					switch (random3)
					{
					case 1:
						attackop = 0, defenseop = 20, speedop = 0, nameop = "Tree", expo = 40, moneyo = 20;
						break;
					case 2:
						attackop = 0, defenseop = 30, speedop = 0, nameop = "Rock", expo = 60, moneyo = 30;
						break;
					case 3:
						attackop = 0, defenseop = 10, speedop = 0, nameop = "Computer", expo = 20, moneyo = 10;
						break;
					case 4:
						attackop = 0, defenseop = 5, speedop = 0, nameop = "Book", expo = 10, moneyo = 5;
						break;
					}
					break;
				case 2:
					switch (random4)
					{
					case 1:
						attackop = 30, defenseop = 20, speedop = 30, nameop = "Rat", expo = 160, moneyo = 80;
						break;
					case 2:
						attackop = 40, defenseop = 20, speedop = 30, nameop = "Cat", expo = 180, moneyo = 90;
						break;
					case 3:
						attackop = 45, defenseop = 25, speedop = 30, nameop = "Dog", expo = 200, moneyo = 100;
						break;
					case 4:
						attackop = 35, defenseop = 20, speedop = 35, nameop = "Bat", expo = 180, moneyo = 90;
						break;
					}
					break;
				case 3:
					switch (random5)
					{
					case 1:
						attackop = 65, defenseop = 35, speedop = 45, nameop = "Mage", expo = 290, moneyo = 145;
						break;
					case 2:
						attackop = 60, defenseop = 50, speedop = 50, nameop = "Jackel", expo = 320, moneyo = 160;
						break;
					case 3:
						attackop = 65, defenseop = 55, speedop = 45, nameop = "Crusader", expo = 330, moneyo = 165;
						break;
					case 4:
						attackop = 55, defenseop = 45, speedop = 55, nameop = "Wolf", expo = 310, moneyo = 155;
						break;
					}
					break;
				case 4:
					switch (random3)
					{
					case 1:
						attackop = 85, defenseop = 35, speedop = 65, nameop = "Assassin", expo = 330, moneyo = 165;
						break;
					case 2:
						attackop = 75, defenseop = 30, speedop = 70, nameop = "Pacman", expo = 310, moneyo = 155;
						break;
					case 3:
						attackop = 85, defenseop = 35, speedop = 85, nameop = "Man Eating Bunny", expo = 330, moneyo = 165;
						break;
					case 4:
						attackop = 80, defenseop = 40, speedop = 60, nameop = "Warlock", expo = 320, moneyo = 160;
						break;
					}
					break;
				case 5:
					switch (random4)
					{
					case 1:
						attackop = 90, defenseop = 45, speedop = 55, nameop = "Poseidon", expo = 340, moneyo = 170;
						break;
					case 2:
						attackop = 80, defenseop = 55, speedop = 60, nameop = "Minitaur", expo = 350, moneyo = 175;
						break;
					case 3:
						attackop = 85, defenseop = 45, speedop = 70, nameop = "Cyclops", expo = 340, moneyo = 170;
						break;
					case 4:
						attackop = 90, defenseop = 55, speedop = 45, nameop = "Dragon", expo = 340, moneyo = 170;
						break;
					}
					break;
				case 6:
					switch (random5)
					{
					case 1:
						attackop = 105, defenseop = 55, speedop = 70, nameop = "Athena", expo = 400, moneyo = 200;
						break;
					case 2:
						attackop = 110, defenseop = 65, speedop = 65, nameop = "Zeus", expo = 420, moneyo = 210;
						break;
					case 3:
						attackop = 95, defenseop = 70, speedop = 60, nameop = "Hades", expo = 390, moneyo = 195;
						break;
					case 4:
						attackop = 90, defenseop = 60, speedop = 65, nameop = "Osiris", expo = 370, moneyo = 185;
						break;
					}
					break;
				case 7:
					attackop = 110, defenseop = 90, speedop = 80, nameop = "God";
					break;
				default:
					cout << "No One";
				}
				//success rate
				asuccess = speedus - defenseop + 50;
				msuccess = speedus - defenseop + 50;

				// Bind main bgm


				cout << "First Round is: " << nameus << " vs. " << nameop << "!!!";
				if (opponent != 7)
					Sleep(1000);
				if (opponent == 7)
				{
					alSourceStop(source[0]);
					alSourcei(source[0], AL_BUFFER, buffer[35]);
					// Play
					alSourcePlay(source[0]);
					ALint source_state_main;
					alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
					alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
					alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

					alSourcef(source[0], AL_GAIN, newVolume);

					while (source_state_main == AL_PLAYING) {
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state_main);
					}
				}
				//amount of damage dealt
				a = attackus - defenseop;
				b = magicus - defenseop;
				opac = 100 - defenseus;
				attackop = attackop - defenseus;
				if (attackop < 0)
					attackop = 0;
				else
					attackop = attackop;
				do {
					//Random Number Generator
					int random, random2;
					random = rand() % 100;
					random2 = rand() % 100;
					system("CLS");
					//limitation
					if (asuccess > 100)
						asuccess = 100;
					else
						asuccess = asuccess;
					if (msuccess > 100)
						msuccess = 100;
					else
						msuccess = msuccess;
					//options
					do {
						if ((random < 80) && (random > 75))
						{
							system("cls");
							alSourcef(source[1], AL_GAIN, 0.3);
							alSourcei(source[1], AL_BUFFER, buffer[19]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 1);
							alSourcef(source[0], AL_GAIN, 0.02);
							cout << "Incredible..a mythical sword has fallen from the sky and into your fist.\nYour attack has rose an additional 5 points!\n(only used on THIS round.)\n\n";
							alSourcei(source[1], AL_BUFFER, buffer[12]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[0], AL_GAIN, 0.06);
							a = a + 5;
							system("pause");

							system("cls");
						}
						if ((random < 76) && (random > 70))
						{
							system("cls");
							alSourcef(source[1], AL_GAIN, 0.3);
							alSourcei(source[1], AL_BUFFER, buffer[19]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 1);
							alSourcef(source[0], AL_GAIN, 0.02);
							cout << "You have just returned from the shoe store, with sneakers faster than lightning!\nYour Speed rose an additional 5 points!\n(only used on THIS round.)\n\n";
							alSourcei(source[1], AL_BUFFER, buffer[12]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[0], AL_GAIN, 0.06);
							asuccess = asuccess + 5;
							msuccess = msuccess + 5;
							system("pause");

							system("cls");
						}
						if ((random < 71) && (random > 65))
						{
							system("cls");
							alSourcef(source[1], AL_GAIN, 0.3);
							alSourcei(source[1], AL_BUFFER, buffer[19]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 1);
							alSourcef(source[0], AL_GAIN, 0.02);
							cout << "An ancient wizard visited you in your sleep, and gave you a new spell.\nYour magic has rose an additional 5 points!\n(only used on THIS round.)\n\n";
							alSourcei(source[1], AL_BUFFER, buffer[12]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[0], AL_GAIN, 0.06);
							b = b + 5;
							system("pause");
							alSourcef(source[1], AL_GAIN, 1);
							system("cls");
						}
						if ((random < 66) && (random > 60))
						{
							system("cls");
							alSourcef(source[1], AL_GAIN, 0.3);
							alSourcei(source[1], AL_BUFFER, buffer[19]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 1);
							alSourcef(source[0], AL_GAIN, 0.02);
							cout << "Athena has just granted you a new sheild!\nYour defense has rose an additional 5 points!\n(only used on THIS round.)\n\n";
							alSourcei(source[1], AL_BUFFER, buffer[12]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[0], AL_GAIN, 0.06);
							opac = opac - 5;
							system("pause");
							alSourcef(source[1], AL_GAIN, 1);
							system("cls");
						}
						healus = attackop - 5;
						if (healus <= 0)
							healus = 10;
						cout << "What would you like to use?\n\n"
							<< "(1)\n***************\nattack: " << asuccess << "% chance of success\n***************\n\n"
							<< "(2)\n***************\nmagic: " << msuccess << "% chance of success\n***************\n\n"
							<< "(3)\n***************\nheal + " << healus << "hp\n***************\n\n";
						cout << ": ";
						cin >> atk;
						if (atk > 3)
						{
							system("cls");
							cout << "You MUST enter a number between 1 and 3!!!\n\n";
							system("pause");
							system("cls");
						}
					} while (atk > 3);
					system("CLS");
					cout << "Calculating results";
					for (int counter = 0; counter <= 6; counter++)
					{
						Sleep(00);
						cout << ".";
					}
					system("CLS");
					switch (atk)
					{
					case 1:
						if (random <= asuccess)
						{
							alSourcef(source[1], AL_GAIN, 0.6);
							/*alSourceStop(source[0]);
							alSourcei(source[0], AL_BUFFER, buffer[15]);
							// Play
							alSourcePlay(source[0]);
							ALint source_state_main;
							alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
							alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
							alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

							alSourcef(source[0], AL_GAIN, newVolume);*/
							alSourcei(source[1], AL_BUFFER, buffer[18]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							if (random <= 10)
							{
								cout << "CRITICAL!!!!\n\n";
								a = a * 2;
							}
							if (a < 0)
								a = 5;
							cout << "You took away " << a << " health points from the " << nameop << "!\n\n";
							healthop = healthop - a;
							if (healthop < 0)
								healthop = 0;
							cout << "The " << nameop << "'s health is: " << healthop << endl << "Your health is: " << healthus << endl << endl;
							if (random <= 10)
								a = a / 2;
						}
						else
						{

							alSourcei(source[1], AL_BUFFER, buffer[28]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You missed!\n\n";
							cout << "The " << nameop << "'s health is: " << healthop << endl << "Your health is: " << healthus << endl << endl;
						}
						break;
					case 2:
						if (random <= msuccess)
						{
							alSourcef(source[1], AL_GAIN, 0.35);
							alSourcei(source[1], AL_BUFFER, buffer[23]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							if (random <= 10)
							{
								cout << "CRITICAL!!!!\n\n";
								b = b * 2;

							}
							if (b < 0)
								b = 5;
							cout << "You took away " << b << " health points from the " << nameop << "!\n\n";
							healthop = healthop - b;
							if (healthop < 0)
								healthop = 0;
							cout << "The " << nameop << "'s health is: " << healthop << endl << "Your health is: " << healthus << endl << endl;
							if (random <= 10)
								b = b / 2;
						}
						else
						{
							alSourcei(source[1], AL_BUFFER, buffer[28]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							// TODO: switsh
							cout << "You missed!\n\n";
							cout << "The " << nameop << "'s health is: " << healthop << endl << "Your health is: " << healthus << endl << endl;
						}
						break;
					case 3:
						if (healthus < 100)
						{
							alSourcef(source[1], AL_GAIN, 0.5);
							alSourcei(source[1], AL_BUFFER, buffer[21]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							// TODO: heal/bubble
							healthus = healthus + healus;
							cout << "Your health rose from " << healthus - healus << ", to " << healthus << "!!!" << endl << endl;
						}
						else
							cout << "Your health is already 100%!!!" << endl << endl;
						break;
					default:
						cout << "Attack Not available";
					}
					system("pause");
					system("cls");
					if (healthop > 0)
					{
						cout << "Opponent is now attacking";
						for (int counter = 6; counter >= 0; counter--)
						{
							Sleep(00);
							cout << ".";
						}
						system("cls");
						if (opac <= random2)
						{
							if (random2 <= 5)
							{
								cout << "CRITICAL!!!!\n\n";
								attackop = attackop + 15;
								// TODO: play crit sound else play normal attack
							}
							if (attackop <= 0)
								attackop = 5;
							if (opponent == 1)
								attackop = 0;
							alSourcei(source[1], AL_BUFFER, buffer[25]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "The opponent took away " << attackop << " health points from you!\n\n";
							healthus = healthus - attackop;
							if (healthus < 0)
								healthus = 0;
							cout << "Opponent's health is: " << healthop << endl << "Your health is: " << healthus << endl << endl;
							if (random2 <= 5)
								attackop = attackop - 15;
						}
						else
						{
							alSourcei(source[1], AL_BUFFER, buffer[28]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "The opponent missed!\n\n";
							cout << "Opponent's health is: " << healthop << endl << "Your health is: " << healthus << endl << endl;
						}
						system("pause");
					}
				} while ((healthop >= 1) && (healthus >= 1));
				system("cls");
				if (healthop >= 1)
				{
					cout << "You were beat by the " << nameop << "!!! Whhaaaahaahaaaaa\n\n";
					alSourceStop(source[0]);

					// Bind main bgm
					alSourcei(source[0], AL_BUFFER, buffer[34]);
					// Play
					alSourcePlay(source[0]);
					ALint source_state_main;
					alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
					alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
					alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

					alSourcef(source[0], AL_GAIN, newVolume);

					while (source_state_main == AL_PLAYING) {
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state_main);
					}



				}
				else if (opponent != 7)
				{
					// TODO: victory bgm
					alSourceStop(source[0]);

					// Bind main bgm
					alSourcei(source[0], AL_BUFFER, buffer[17]);
					// Play
					alSourcePlay(source[0]);
					ALint source_state_main;
					alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
					alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
					alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

					alSourcef(source[0], AL_GAIN, newVolume);

					while (source_state_main == AL_PLAYING) {
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state_main);
					}


					if (healthus > 0)
					{
						healthus = 100;
						cout << "You have gained " << expo << " experience, and " << moneyo << " money!!!\n\n";
						alSourcef(source[0], AL_GAIN, 0.01);
						alSourcei(source[1], AL_BUFFER, buffer[33]);
						// Play!
						alSourcePlay(source[1]);
						ALint source_state;
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						float x = 0.0;
						alSourcef(source[1], AL_GAIN, 0.08);
						while (source_state == AL_PLAYING)
						{
							alSourcef(source[1], AL_PITCH, 1 + x);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							Sleep(100);
							if (x < 1)
							{
								x = x + 0.1;
							}

						}
						alSourcef(source[0], AL_GAIN, 0.05);
						alSourcef(source[1], AL_GAIN, 1);
						alSourcef(source[1], AL_PITCH, 1);
						exp = exp + expo;
						money = money + moneyo;
						cout << "You have " << exp << " experience points!\n";

						if (levelup > exp)
							cout << "You need " << levelup - exp << " more exp points to level up.\n";
						cout << "You have $" << money << endl << endl;
						system("pause");
						system("cls");
					}
					if (exp >= levelup)
					{
						c++;
						level++;
						alSourcei(source[1], AL_BUFFER, buffer[22]); // you have selected
						alSourcePlay(source[1]);
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						while (source_state == AL_PLAYING)
						{
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						}
						alSourcef(source[0], AL_GAIN, 0.02);
						cout << "Congratulations on your victory! You have graduated to level " << level << "!!!.\n\n";
						cout << "Which attribute would you like to increase by 5 points?\n";
						alSourcei(source[1], AL_BUFFER, buffer[13]); // you have selected
						alSourcePlay(source[1]);
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						alSourcef(source[1], AL_GAIN, 1.2);
						while (source_state == AL_PLAYING)
						{
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						}
						alSourcef(source[1], AL_GAIN, 1);
						alSourcef(source[0], AL_GAIN, 0.06);
						cout << endl << "(1)\n*****\nattack\n*****\n\n(2)\n*****\nmagic\n*****\n\n(3)\n*****\nspeed\n*****\n\n(4)\n*****\ndefense\n*****\n:";
						cin >> atr;
						switch (atr)
						{
						case 1:
							attackus = attackus + 5;
							break;
						case 2:
							magicus = magicus + 5;
							break;
						case 3:
							speedus = speedus + 5;
							break;
						case 4:
							defenseus = defenseus + 5;
							break;
						default:
							defenseus = defenseus;
							break;
						}
						system("cls");
						cout << "Your current Stats are:\nattack - " << attackus << endl << "magic - " << magicus << endl << "speed - " << speedus << endl << "defense - " << defenseus << endl << endl;
						system("pause");
						system("cls");
						levelup = levelup * 2;
					}
				}
				system("pause");
				break;
			case 2:
				// TODO Maybe move shop bgm here
				do {

					do {
						system("cls");
						cout << "You have $" << money << " left.";
						cout << " Which Item would you like to buy?\n\n";

						alSourceStop(source[0]);

						// Bind main bgm
						alSourcei(source[0], AL_BUFFER, buffer[16]);
						// Play
						alSourcePlay(source[0]);
						ALint source_state_main;
						alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
						alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
						alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

						alSourcef(source[0], AL_GAIN, newVolume);

						while (source_state_main == AL_PLAYING) {
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state_main);
						}

						alSourcef(source[0], AL_GAIN, 0.02);
						alSourcef(source[1], AL_GAIN, 1);
						alSourcei(source[1], AL_BUFFER, buffer[10]); // you have selected
						alSourcePlay(source[1]);
						alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						while (source_state == AL_PLAYING)
						{
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
						}
						alSourcef(source[0], AL_GAIN, 0.06);
						cout << "(1)\n**********\nRusty Sword(+3 attack) - 300$\n**********\n";
						cout << "(2)\n**********\nSteel Sword(+6 attack) - 500$\n**********\n";
						cout << "(3)\n**********\nGreat Sword(+9 attack) - 700$\n**********\n\n";
						cout << "(4)\n**********\nWooden Shield(+3 defense) - 300$\n**********\n";
						cout << "(5)\n**********\nSmall Shield(+6 defense) - 500$\n**********\n";
						cout << "(6)\n**********\nGaurdian's Shield(+9 defense) - 700$\n**********\n\n";
						cout << "(7)\n**********\nWooden Staff(+3 magic) - 300$\n**********\n";
						cout << "(8)\n**********\nCurved Staff(+6 magic) - 500$\n**********\n";
						cout << "(9)\n**********\nWarlock's Staff(+9 magic) - 700$\n**********\n\n";
						cout << "(10)\n**********\nPatched Loafers(+3 speed) - 300$\n**********\n";
						cout << "(11)\n**********\nRegular Sneakers(+6 speed) - 500$\n**********\n";
						cout << "(12)\n**********\nRunning Shoes(+9 speed) - 700$\n**********\n";
						cout << "(13)\n**********\nExit\n**********\n";
						cin >> item;
						system("cls");
					} while ((item > 13) || (item < 1));
					switch (item)
					{
					case 1: // TODO: money sound for each case
						if (money >= 300)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 attack!\n\n";
							money = money - 300;
							attackus = attackus + 3;
							break;
						}
					case 2:
						if (money >= 500)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 6 attack!\n\n";
							money = money - 500;
							attackus = attackus + 6;
							break;
						}
					case 3:
						if (money >= 700)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 9 attack!\n\n";
							money = money - 700;
							attackus = attackus + 9;
							break;
						}
					case 4:
						if (money >= 300)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 defense!\n\n";
							money = money - 300;
							defenseus = defenseus + 3;
							break;
						}
					case 5:
						if (money >= 500)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 6 defense!\n\n";
							money = money - 500;
							defenseus = defenseus + 6;
							break;
						}
					case 6:
						if (money >= 700)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 9 defense!\n\n";
							money = money - 700;
							defenseus = defenseus + 9;
							break;
						}
					case 7:
						if (money >= 300)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 magic!\n\n";
							money = money - 300;
							magicus = magicus + 3;
							break;
						}
					case 8:
						if (money >= 500)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 magic!\n\n";
							money = money - 500;
							magicus = magicus + 6;
							break;
						}
					case 9:
						if (money >= 700)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 magic!\n\n";
							money = money - 700;
							magicus = magicus + 9;
							break;
						}
					case 10:
						if (money >= 300)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 speed!\n\n";
							money = money - 300;
							speedus = speedus + 3;
							break;
						}
					case 11:
						if (money >= 500)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 speed!\n\n";
							money = money - 500;
							speedus = speedus + 6;
							break;
						}
					case 12:
						if (money >= 700)
						{
							alSourcef(source[1], AL_GAIN, 0.4);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							alSourcef(source[1], AL_GAIN, 0.08);
							alSourcei(source[1], AL_BUFFER, buffer[26]); // you have selected
							alSourcePlay(source[1]);
							alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							while (source_state == AL_PLAYING)
							{
								alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
							}
							cout << "You have gained 3 speed!\n\n";
							money = money - 700;
							speedus = speedus + 9;
							break;
						}
					default:
						speedus = speedus;
					}
					//END Armory
					cout << "Would you like to exit? (y or n): ";
					cin >> exit;
					system("cls");
					// TODO: Walking away

				} while (exit != 'y');
				alSourcef(source[1], AL_GAIN, 0.5);
				alSourcei(source[1], AL_BUFFER, buffer[30]); // you have selected
				alSourcePlay(source[1]);
				alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
				while (source_state == AL_PLAYING)
				{
					alGetSourcei(source[1], AL_SOURCE_STATE, &source_state);
				}
				break;
			default:
				cout << "Please select 1 or 2!!!";
			}
		} while ((healthus > 0) && (opponent != 7));
	} while ((healthus >= 1) && (opponent != 7));
	if (healthus >= 1)
	{
		cout << "Wow you did it!\n" << endl;
		cout << "                     ********                                               " << endl;
		cout << "                   ************    **                                       " << endl;
		cout << "                  ************** ******                                     " << endl;
		cout << "                 ***********************                                    " << endl;
		cout << "                 ***********************                                    " << endl;
		cout << "                 **************** *****                                     " << endl;
		cout << "                  **************   ***                                      " << endl;
		cout << "                   ************     *                                       " << endl;
		cout << "                     ********      ***      * *                             " << endl;
		cout << "                       ****          *     *   *                            " << endl;
		cout << "                        **            *   *    *                            " << endl;
		cout << "                       ****            * *      *                           " << endl;
		cout << "                         *                                                  " << endl;
		cout << "                          *                                                 " << endl;
		cout << "                           * * *                                            " << endl;
		cout << "                          * *   *                                           " << endl;
		cout << "                        *    * *                                            " << endl;
		cout << "                        *                                                   " << endl;
		cout << "                        *                                                   " << endl;
		cout << "                         *                                                  " << endl;

		//TODO: Play Victory then close

		alSourceStop(source[0]);

		// Bind main bgm
		alSourcei(source[0], AL_BUFFER, buffer[36]);
		// Play
		alSourcePlay(source[0]);
		ALint source_state_main;
		alGetSourcei(source[0], AL_SOURCE_STATE, &source_state_main);
		alSourcei(source[0], AL_SOURCE_RELATIVE, AL_TRUE);
		alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0);

		alSourcef(source[0], AL_GAIN, newVolume);

		while (source_state_main == AL_PLAYING) {
			alGetSourcei(source[1], AL_SOURCE_STATE, &source_state_main);
		}

		Sleep(5000);

		 
		alDeleteSources(3, source);
		alDeleteBuffers(2, buffer);
		context = alcGetCurrentContext(); // only used to shutdown the audio
		device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}
}