#include <Novice.h>
#include <mt3.h>
#define _USE_MATH_DEFINES
#include<cmath>
#include<imgui.h>
const char kWindowTitle[] = "MT3_00-01";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotato{ 0.26f,0.0f,0.0f };
	
	Sphere sphere;
	sphere.center={ 0.0f, -40, 162 };
	sphere.radius = 30;

	Vector3 rotate{};
	Vector3 translate{};
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
		//rotate.y += 0.5f;
		Matrix4x4 worldMatrix = MakeAffineMatrix(Scale, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix(Scale,  cameraRotato, cameraTranslate);
		Matrix4x4 viewMatrix = Invers(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePersectiveFovMatrix(0.45f, float(kWindowWith) / float(kWindowHigat), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWith), float(kWindowHigat), 0.0f, 1.0f);
		
		
		
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotato", &cameraRotato.x, 0.01f); 
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///
		

        

		///
		/// ↓描画処理ここから
		///
		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, WHITE);
	

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
