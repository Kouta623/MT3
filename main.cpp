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

	Plane plane;
	plane.distance = 1.0f;
	plane.normal = { 0.0f,1.0f,0.0f };

	Segment segmrnt;
	segmrnt.diff = { 0.45f,0.78f,0.0f };
	segmrnt.origin = { 1.0f,0.58f,0.0f };


	Vector3 rotate{};
	Vector3 translate{};
	Vector3 Scale = { 1.0f,1.0f,1.0f };

	Vector3 SegmentDiff;
	Vector3 SegmentOrigin;
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



		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotato", &cameraRotato.x, 0.01f);
		ImGui::DragFloat3("segmrnt.diff", &segmrnt.diff.x, 0.01f);
		ImGui::DragFloat("segmrnt.origin", &segmrnt.origin.x, 0.01f);
		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("Plane.distance", &plane.distance, 0.01f);

		ImGui::End();

		plane.normal = Normalize(plane.normal);

		SegmentDiff = Transform(Transform(segmrnt.diff, viewProjectionMatrix), viewportMatrix);
		SegmentOrigin = Transform(Transform(segmrnt.origin, viewProjectionMatrix), viewportMatrix);
		///
		///
		/// ↑更新処理ここまで
		///




		///
		/// ↓描画処理ここから
		///



		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);

		Novice::DrawLine((int)SegmentDiff.x, (int)SegmentDiff.y, (int)SegmentOrigin.x, (int)SegmentOrigin.y, WHITE);

		if (IsCollision(segmrnt, plane)) {
			Novice::DrawLine((int)SegmentDiff.x, (int)SegmentDiff.y, (int)SegmentOrigin.x, (int)SegmentOrigin.y, RED);

		}



		DrawGrid(viewProjectionMatrix, viewportMatrix);


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
