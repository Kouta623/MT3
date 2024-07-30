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
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	AABB aabb{
			.min{-0.5f, -0.5f, -0.5f},
			.max{0.0f, 0.0f, 0.0f},
	};

	Sphere sphere;
	sphere.center = { 0.0f, 0.0f, 0.0f };
	sphere.radius = 0.5;



	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraRotate = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate = { 0.0f, 0.0f, -9.49f };
	Vector3 cameraPosition = { 0,0,-5.0f };

	Vector3 start{};
	Vector3 end{};

	Matrix4x4 viewProjectionMatrix = {};
	Matrix4x4 viewportMatrix = {};


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

		viewProjectionMatrix = MakeViewProjectionMatrix({ 1, 1, 1 }, rotate, translate, { 1, 1, 1 }, cameraRotate, cameraTranslate);
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWith), float(kWindowHigat), 0.0f, 1.0f);


		ImGui::DragFloat3("sphere.center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("sphere.radius", &sphere.radius, 0.01f);
		ImGui::DragFloat3("aabb.min", &aabb.min.x, 0.01f);
		ImGui::DragFloat3("aabb.max", &aabb.max.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);

		aabb.min.x = (std::min)(aabb.min.x, aabb.max.x);
		aabb.max.x = (std::max)(aabb.min.x, aabb.max.x);
		aabb.min.y = (std::min)(aabb.min.y, aabb.max.y);
		aabb.max.y = (std::max)(aabb.min.y, aabb.max.y);
		aabb.min.z = (std::min)(aabb.min.z, aabb.max.z);
		aabb.max.z = (std::max)(aabb.min.z, aabb.max.z);
		

		///
		/// ↑更新処理ここまで
		///




		///
		/// ↓描画処理ここから
		///


		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawAABB(aabb, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, WHITE);
	
		if (IsCollision(aabb, sphere)) {
			DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, RED);
		}
		
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
