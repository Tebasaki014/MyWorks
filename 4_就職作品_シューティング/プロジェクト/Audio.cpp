#include "Audio.h"
#include <fstream>
#include <cassert>

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

bool Audio::LordSound(Sound* sound, const char* filename)
{
	//ファイルストリーム
	std::ifstream file;
	//Waveファイルを開く
	file.open(filename, std::ios_base::binary);
	//ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	//Dataチャンクの読み込み
	Chunk data;
	file.read((char*)&data, sizeof(data));

	//Dataチャンクのデータ部（波形データ）の読み込み
	file.read(sound->pBuffer, data.size);

	//Waveファイルを閉じる
	file.close();

	//波形フォーマットの設定
	memcpy(&sound->wfex, &format.fmt, sizeof(format.fmt));
	sound->wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	sound->size = data.size;
	return false;
}

void Audio::PlayWave(Sound* sound)
{
	HRESULT result;
	
	//ぬるちぇっく
	if (!sound) return;

	//波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &sound->wfex, 0, 2.0f, &voiceCallback);
	if FAILED(result) {
		delete[] sound->pBuffer;
		assert(0);
		return;
	}

	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)sound->pBuffer;
	buf.pContext = sound->pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = sound->size;

	//波形データの再生
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	if FAILED(result) {
		delete[] sound->pBuffer;
		assert(0);
		return;
	}

	result = pSourceVoice->Start();
	if FAILED(result) {
		delete[] sound->pBuffer;
		assert(0);
		return;
	}
}