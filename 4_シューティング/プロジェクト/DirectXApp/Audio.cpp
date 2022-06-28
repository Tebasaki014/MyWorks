#include "Audio.h"
#include <fstream>
#include <cassert>

#include "SDelete.h"


#pragma comment(lib,"xaudio2.lib")

bool Audio::Initialize()
{
	HRESULT result;

	//XAudioエンジンのインスタンスを生成
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result) {
		assert(0);
		return false;
	}

	//マスターボイスを生成
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	if FAILED(result) {
		assert(0);
		return false;
	}

	return true;
}

Sound* Audio::LoadWave(const char* filename)
{
	HRESULT result;
	//ファイルストリーム
	std::ifstream file;
	//開く
	file.open(filename, std::ios_base::binary);
	//失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	//RIFFヘッダー読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//RIFFならOK
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	//Formatチャンク読み込み
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	//Dataチャンク読み込み
	Chunk data;
	file.read((char*)&data, sizeof(data));

	//Dataチャンクのデータ部読み込み
	char* pBuff = new char[data.size];
	file.read(pBuff, data.size);

	//ファイル閉じる
	file.close();

	//Sound* sound = new Sound();
	//sound->pBuffer = pBuff;
	//sound->size = data.size;

	//波形フォーマット設定
	WAVEFORMATEX wfex{};
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	//波形データ設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)pBuff;
	buf.pContext = pBuff;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = data.size;

	Sound* sound = new Sound();
	sound->buf = buf;
	sound->wfex = wfex;

	return sound;
}

void Audio::PlayWave(Sound* sound, bool loopFlag)
{
	HRESULT result;

	if (loopFlag) {
		sound->buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	//SourceVoicceが既に生成されている場合は消す
	if (sound->pSource) {
		sound->pSource->DestroyVoice();
	}
	//波形フォーマットからSourceVoice生成
	result = xAudio2->CreateSourceVoice(&sound->pSource, &sound->wfex, 0, 2.0f, &voiceCallback);
	if FAILED(result) {
		SDelete(sound);
		assert(0);
		return;
	}

	//波形データ再生
	result = sound->pSource->SubmitSourceBuffer(&sound->buf);
	if FAILED(result) {
		SDelete(sound);
		assert(0);
		return ;
	}

	result = sound->pSource->Start();
	if FAILED(result) {
		SDelete(sound);
		assert(0);
		return;
	}
}

void Audio::PauseWave(Sound* sound)
{
	HRESULT result;

	result = sound->pSource->Stop();
	if FAILED(result) {
		SDelete(sound);
		assert(0);
		return;
	}
}

void Audio::SetVolume(Sound* sound, const float volume)
{
	sound->pSource->SetVolume(volume);
}