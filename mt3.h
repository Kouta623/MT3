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

struct Matrix4x4
{
    float m[4][4];
};

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%.02f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth*2, y, "%.02f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth*3, y, "%s", label);

}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column], label);
        }
    }
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


//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }

    return result;
}

//行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
        }
    }

    return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }

    return result;
}

//逆行列
Matrix4x4 Invers(const Matrix4x4& m) {
    Matrix4x4 result;
    

    return result;
}

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
   
}

//単位行列
Matrix4x4 MakeIdentity4x4() {

}