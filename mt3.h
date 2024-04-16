#include<math.h>
#include<assert.h>
#include <Novice.h>
#include <stdio.h>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;




struct Vector3 {
	float x, y, z;
};

struct Matrix3x3
{
    float m[3][3];
};


void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%.02f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth*2, y, "%.02f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth*3, y, "%s", label);

}

//加算
Vector3 Add(const Vector3& v1, Vector3& v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);

}

//減算
Vector3 Subtract(const Vector3& v1, Vector3& v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

//スカラー倍
Vector3 Multiply(float scalar, Vector3& v) {

    Vector3 result;
    result.x = scalar * v.x;
    result.y = scalar * v.y;
    result.z = scalar * v.z;
    return result;

}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//長さ
float Length(const Vector3& v) {
   return sqrtf(Dot(v,v));
}


//正規化
Vector3 Normalize(const Vector3& v) {

    Vector3 result;
    result.x = v.x / Length(v);
    result.y = v.y / Length(v);
    result.z = v.z / Length(v);
    return result;

  
}
