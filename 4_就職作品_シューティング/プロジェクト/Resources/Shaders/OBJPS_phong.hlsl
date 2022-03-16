#include "OBJHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
		
	// 光沢度
	const float shininess = 4.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(camerapos - input.worldpos.xyz);
	//ハイライト用ハーフベクトル
	float3 harfv = normalize(lightv + eyedir);
	//陰影つけるやつ
	//光に当たってる面
	float intensity = saturate(dot(normalize(input.normal), lightv));
	//ハイライト面
	float specIntensity = saturate(dot(normalize(input.normal), harfv));
	float toon = 0.002;

	//環境光
	float3 ambient = texcolor.rgb * 0.3;
	//拡散反射光
	float3 diffuse = texcolor.rgb;
	//鏡面反射光
	float3 specular = pow(specIntensity, 80);

	//陰影をつける
	ambient *= (1 - intensity);
	diffuse *= intensity;

	//加算
	float3 color = ambient + diffuse + specular;
	//描画
	return float4(color.r, color.g, color.b, 1);
}