﻿#pragma once
#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>

#include "Singleton.h"

/// <summary>
/// オーディオコールバック
/// </summary>
class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:
	//ボイス処理パスの開始時
	//STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
	void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
	//ボイス処理パスの終了時
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
	//バッファストリームの再生が終了した時
	STDMETHOD_(void, OnStreamEnd) (THIS) {};
	//バッファの使用開始時
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
	//バッファの末尾に達した時
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
		//バッファを解放する
		delete[] pBufferContext;
	};
	//再生がループ位置に達した時
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
	//ボイスの実行エラー時
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

//サウンド
struct Sound {
	WAVEFORMATEX wfex{};
	XAUDIO2_BUFFER buf{};
	IXAudio2SourceVoice* pSource = nullptr;

	~Sound() {
		if (pSource) {
			pSource->DestroyVoice();
		}
	}
};

/// <summary>
/// オーディオ
/// </summary>
class Audio : public Singleton_Unique<Audio>
{
private:
	friend Singleton_Unique<Audio>;
	Audio() = default;
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//チャンクヘッダ
	struct Chunk
	{
		char	id[4]; //チャンク毎のID
		int		size;  //チャンクサイズ
	};

	// RIFFヘッダチャンク
	struct RiffHeader
	{
		Chunk	chunk;   //"RIFF"
		char	type[4]; //"WAVE"
	};

	//FMTチャンク
	struct FormatChunk
	{
		Chunk		chunk; //"fmt "
		WAVEFORMAT	fmt;   //波形フォーマット
	};

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize();

	//サウンドファイル読み込み
	Sound* LoadWave(const char* filename);

	//サウンドファイル再生
	void PlayWave(Sound* sound, bool loopFlag = false);
	//サウンド停止
	void PauseWave(Sound* sound);
	//音量
	void SetVolume(Sound* sound, const float volume);

private:
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	XAudio2VoiceCallback voiceCallback;
};