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

	Vector3 cameraTranslate{ 0.0f,0.0f,-10.0f };
	Vector3 cameraRotato{ 0.0f,0.0f,0.0f };

	Segment segmrnt;
	segmrnt.diff = { 0.45f,0.78f,0.0f };
	segmrnt.origin = { 1.0f,0.58f,0.0f };


	AABB aabb{
				.min{-0.5f, -0.5f, -0.5f},
				.max{0.0f, 0.0f, 0.0f},
	};
	Vector3 rotate{};
	Vector3 translate{};
	Vector3 Scale = { 1.0f,1.0f,1.0f };

	Vector3 start{};
	Vector3 end{};
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

		Matrix4x4 worldMatrix = MakeAffineMatrix(Scale, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix(Scale, cameraRotato, cameraTranslate);
		Matrix4x4 viewMatrix = Invers(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePersectiveFovMatrix(0.45f, float(kWindowWith) / float(kWindowHigat), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWith), float(kWindowHigat), 0.0f, 1.0f);



		ImGui::DragFloat3("sphere.center", &segmrnt.diff.x, 0.01f);
		ImGui::DragFloat("sphere.origin", &segmrnt.origin.x, 0.01f);
		ImGui::DragFloat3("aabb.min", &aabb.min.x, 0.01f);
		ImGui::DragFloat3("aabb.max", &aabb.max.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotato.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);

		start = Transform(Transform(segmrnt.diff, viewProjectionMatrix), viewportMatrix);
		end = Transform(Transform(segmrnt.origin, viewProjectionMatrix), viewportMatrix);
		///
		///
		/// ↑更新処理ここまで
		///




		///
		/// ↓描画処理ここから
		///



		DrawGrid(viewProjectionMatrix, viewportMatrix);

		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, WHITE);
		DrawAABB(aabb, viewProjectionMatrix, viewportMatrix, WHITE);


		if (IsCollision(aabb, segmrnt)) {
			Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, RED);

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