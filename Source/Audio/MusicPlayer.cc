#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer():
music(),
fileNames(),
volume(100.f){

	fileNames[Music::mainTheme] = "Music/mainTheme.ogg";
	fileNames[Music::gameplay] = "Music/gameplay.ogg";
}

void MusicPlayer::play(Music theme){

	std::string fileName = fileNames[theme];

	if (!music.openFromFile(fileName))
		throw std::runtime_error(fileName + " failed to load.");

	music.setVolume(volume);
	music.setLoop(true);
	music.play();
}

void MusicPlayer::stop(){

	music.stop();
}

void MusicPlayer::pause(){

	music.pause();
}
	
void MusicPlayer::resume(){

	music.play();
}

void MusicPlayer::setVolume(float volume){

	this->volume = volume;
}

