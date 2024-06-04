#include <Novice.h>
#include <mt3.h>
#define _USE_MATH_DEFINES
#include<cmath>

const char kWindowTitle[] = "MT3_00-01";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//クロス積確認用	
	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	Vector3 rotate{};
	Vector3 translate{};

	Vector3 kLocalvertical[3] =
	{
		0.0f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f
	};

	Vector3 Scale = { 1.0f,1.0f,1.0f };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		rotate.y+=0.5f;
		Matrix4x4 worldMatrix = MakeAffineMatrix(Scale, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix(Scale, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,-5.0f });
		Matrix4x4 viewMatrix = Invers(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePersectiveFovMatrix(0.45f, float(kWindowWith) / float(kWindowHigat), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWith), float(kWindowHigat), 0.0f, 1.0f);
		Vector3 screeVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalvertical[i], worldViewProjectionMatrix);
			screeVertices[i] = Transform(ndcVertex, viewportMatrix);
		}


		if (preKeys[DIK_W]) {
			Scale.z-=0.1f;
		}
		if (preKeys[DIK_A]) {
			translate.x-= 0.1f;
		}
		if (preKeys[DIK_S]) {
			Scale.z+= 0.1f;
		}
		if (preKeys[DIK_D]) {
			translate.x+= 0.1f;
		}
		

		///
		/// ↑更新処理ここまで
		///
		

        

		///
		/// ↓描画処理ここから
		///
		Novice::DrawTriangle(int(screeVertices[0].x), int(screeVertices[0].y), int(screeVertices[1].x), int(screeVertices[1].y), int(screeVertices[2].x), int(screeVertices[2].y), RED, kFillModeSolid);

		
		VectorScreenPrintf(0, 0, cross, "Cross");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
