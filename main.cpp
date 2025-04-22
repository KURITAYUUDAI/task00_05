#include <Novice.h>
#include <cmath>
#include <stdlib.h>
#include <assert.h>

const char kWindowTitle[] = "LC1A_11_クリタ_ユウダイ_タイトル";


struct Vector3
{
	float x, y, z;
};

struct Matrix4x4
{
	float m[4][4];
};

// 00_01
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

// 内積
float Dot(const Vector3& v1, const Vector3& v2);

// 長さ(ノルム)
float Length(const Vector3& v);

// 正規化
Vector3 Normalize(const Vector3& v);

// 3次元ベクトルの数値表示
static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

// 00_02
// 1. 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

// 6. 単位行列の作成
Matrix4x4 MakeIdentity4x4();

static const int kRowHeight = 20;

// 4x4行列の数値表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

// 00_03
// 1. 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// 2. 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 3. 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 00_04
// 1. X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// 2. Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// 3. Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// 00_05
// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeAffineMatrixGPT(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeAffineMatrixMy(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 scale{ 1.2f, 0.79f, -2.1f };
	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Vector3 translate{ 2.7f, -4.15f, 1.57f };
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
	Matrix4x4 worldMatrixGPT = MakeAffineMatrixGPT(scale, rotate, translate);
	Matrix4x4 worldMatrixMy = MakeAffineMatrixMy(scale, rotate, translate);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, worldMatrixGPT, "worldMatrixGPT");
		MatrixScreenPrintf(0, kRowHeight * 10, worldMatrixMy, "worldMatrixMy"); 

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
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v)
{
	return { scalar * v.x, scalar * v.y, scalar * v.z };
}

// 内積
float Dot(const Vector3& v1, const Vector3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// 長さ(ノルム)
float Length(const Vector3& v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

// 正規化
Vector3 Normalize(const Vector3& v)
{
	float length = Length(v);

	return { v.x / length, v.y / length, v.z / length };
}
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}
// 1. 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 m3;
	m3 =
	{
		m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[0][1], m1.m[0][2] + m2.m[0][2], m1.m[0][3] + m2.m[0][3],
		m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1], m1.m[1][2] + m2.m[1][2], m1.m[1][3] + m2.m[1][3],
		m1.m[2][0] + m2.m[2][0], m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2], m1.m[2][3] + m2.m[2][3],
		m1.m[3][0] + m2.m[3][0], m1.m[3][1] + m2.m[3][1], m1.m[3][2] + m2.m[3][2], m1.m[3][3] + m2.m[3][3],
	};
	return m3;
}

// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 m3;
	m3 =
	{
		m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[0][1], m1.m[0][2] - m2.m[0][2], m1.m[0][3] - m2.m[0][3],
		m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1], m1.m[1][2] - m2.m[1][2], m1.m[1][3] - m2.m[1][3],
		m1.m[2][0] - m2.m[2][0], m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2], m1.m[2][3] - m2.m[2][3],
		m1.m[3][0] - m2.m[3][0], m1.m[3][1] - m2.m[3][1], m1.m[3][2] - m2.m[3][2], m1.m[3][3] - m2.m[3][3],
	};
	return m3;
}

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 m3;
	float factor1[4], factor2[4] = { 0.0f };
	for (int row = 0; row < 4; ++row)
	{
		factor1[0] = m1.m[row][0];
		factor1[1] = m1.m[row][1];
		factor1[2] = m1.m[row][2];
		factor1[3] = m1.m[row][3];
		for (int column = 0; column < 4; ++column)
		{
			factor2[0] = m2.m[0][column];
			factor2[1] = m2.m[1][column];
			factor2[2] = m2.m[2][column];
			factor2[3] = m2.m[3][column];
			m3.m[row][column]
				= factor1[0] * factor2[0] + factor1[1] * factor2[1] + factor1[2] * factor2[2] + factor1[3] * factor2[3];
		}
	}
	return m3;
}

// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& a)
{
	Matrix4x4 inverseM;
	inverseM.m[0][0]
		= (a.m[1][1] * a.m[2][2] * a.m[3][3]) + (a.m[1][2] * a.m[2][3] * a.m[3][1]) + (a.m[1][3] * a.m[2][1] * a.m[3][2])
		- (a.m[1][3] * a.m[2][2] * a.m[3][1]) - (a.m[1][2] * a.m[2][1] * a.m[3][3]) - (a.m[1][1] * a.m[2][3] * a.m[3][2]);
	inverseM.m[0][1]
		= -(a.m[0][1] * a.m[2][2] * a.m[3][3]) - (a.m[0][2] * a.m[2][3] * a.m[3][1]) - (a.m[0][3] * a.m[2][1] * a.m[3][2])
		+ (a.m[0][3] * a.m[2][2] * a.m[3][1]) + (a.m[0][2] * a.m[2][1] * a.m[3][3]) + (a.m[0][1] * a.m[2][3] * a.m[3][2]);
	inverseM.m[0][2]
		= (a.m[0][1] * a.m[1][2] * a.m[3][3]) + (a.m[0][2] * a.m[1][3] * a.m[3][1]) + (a.m[0][3] * a.m[1][1] * a.m[3][2])
		- (a.m[0][3] * a.m[1][2] * a.m[3][1]) - (a.m[0][2] * a.m[1][1] * a.m[3][3]) - (a.m[0][1] * a.m[1][3] * a.m[3][2]);
	inverseM.m[0][1]
		= -(a.m[0][1] * a.m[1][2] * a.m[2][3]) - (a.m[0][2] * a.m[1][3] * a.m[2][1]) - (a.m[0][3] * a.m[1][1] * a.m[2][2])
		+ (a.m[0][3] * a.m[1][2] * a.m[2][1]) + (a.m[0][2] * a.m[1][1] * a.m[2][3]) + (a.m[0][1] * a.m[1][3] * a.m[2][2]);

	inverseM.m[1][0]
		= -(a.m[1][0] * a.m[2][2] * a.m[3][3]) - (a.m[1][2] * a.m[2][3] * a.m[3][0]) - (a.m[1][3] * a.m[2][0] * a.m[3][2])
		+ (a.m[1][3] * a.m[2][2] * a.m[3][0]) + (a.m[1][2] * a.m[2][0] * a.m[3][3]) + (a.m[1][0] * a.m[2][3] * a.m[3][2]);
	inverseM.m[1][1]
		= (a.m[0][0] * a.m[2][2] * a.m[3][3]) + (a.m[0][2] * a.m[2][3] * a.m[3][0]) + (a.m[0][3] * a.m[2][0] * a.m[3][2])
		- (a.m[0][3] * a.m[2][2] * a.m[3][0]) - (a.m[0][2] * a.m[2][0] * a.m[3][3]) - (a.m[0][0] * a.m[2][3] * a.m[3][2]);
	inverseM.m[1][2]
		= -(a.m[0][0] * a.m[1][2] * a.m[3][3]) - (a.m[0][2] * a.m[1][3] * a.m[3][0]) - (a.m[0][3] * a.m[1][0] * a.m[3][2])
		+ (a.m[0][3] * a.m[1][2] * a.m[3][0]) + (a.m[0][2] * a.m[1][0] * a.m[3][3]) + (a.m[0][0] * a.m[1][3] * a.m[3][2]);
	inverseM.m[1][3]
		= (a.m[0][0] * a.m[1][2] * a.m[2][3]) + (a.m[0][2] * a.m[1][3] * a.m[2][0]) + (a.m[0][3] * a.m[1][0] * a.m[2][2])
		- (a.m[0][3] * a.m[1][2] * a.m[2][0]) - (a.m[0][2] * a.m[1][0] * a.m[2][3]) - (a.m[0][0] * a.m[1][3] * a.m[2][2]);

	inverseM.m[2][0]
		= (a.m[1][0] * a.m[2][1] * a.m[3][3]) + (a.m[1][1] * a.m[2][3] * a.m[3][0]) + (a.m[1][3] * a.m[2][0] * a.m[3][1])
		- (a.m[1][3] * a.m[2][1] * a.m[3][0]) - (a.m[1][1] * a.m[2][0] * a.m[3][3]) - (a.m[1][0] * a.m[2][3] * a.m[3][1]);
	inverseM.m[2][1]
		= -(a.m[0][0] * a.m[2][1] * a.m[3][3]) - (a.m[0][1] * a.m[2][3] * a.m[3][0]) - (a.m[0][3] * a.m[2][0] * a.m[3][1])
		+ (a.m[0][3] * a.m[2][1] * a.m[3][0]) + (a.m[0][1] * a.m[2][0] * a.m[3][3]) + (a.m[0][0] * a.m[2][3] * a.m[3][1]);
	inverseM.m[2][2]
		= (a.m[0][0] * a.m[1][1] * a.m[3][3]) + (a.m[0][1] * a.m[1][3] * a.m[3][0]) + (a.m[0][3] * a.m[1][0] * a.m[3][1])
		- (a.m[0][3] * a.m[1][1] * a.m[3][0]) - (a.m[0][1] * a.m[1][0] * a.m[3][3]) - (a.m[0][0] * a.m[1][3] * a.m[3][1]);
	inverseM.m[2][3]
		= -(a.m[0][0] * a.m[1][1] * a.m[2][3]) - (a.m[0][1] * a.m[1][3] * a.m[2][0]) - (a.m[0][3] * a.m[1][0] * a.m[2][1])
		+ (a.m[0][3] * a.m[1][1] * a.m[2][0]) + (a.m[0][1] * a.m[1][0] * a.m[2][3]) + (a.m[0][0] * a.m[1][3] * a.m[2][1]);

	inverseM.m[3][0]
		= -(a.m[1][0] * a.m[2][1] * a.m[3][2]) - (a.m[1][1] * a.m[2][2] * a.m[3][0]) - (a.m[1][2] * a.m[2][0] * a.m[3][1])
		+ (a.m[1][2] * a.m[2][1] * a.m[3][0]) + (a.m[1][1] * a.m[2][0] * a.m[3][2]) + (a.m[1][0] * a.m[2][2] * a.m[3][1]);
	inverseM.m[3][1]
		= (a.m[0][0] * a.m[2][1] * a.m[3][2]) + (a.m[0][1] * a.m[2][2] * a.m[3][0]) + (a.m[0][2] * a.m[2][0] * a.m[3][1])
		- (a.m[0][2] * a.m[2][1] * a.m[3][0]) - (a.m[0][1] * a.m[2][0] * a.m[3][2]) - (a.m[0][0] * a.m[2][2] * a.m[3][1]);
	inverseM.m[3][2]
		= -(a.m[0][0] * a.m[1][1] * a.m[3][2]) - (a.m[0][1] * a.m[1][2] * a.m[3][0]) - (a.m[0][2] * a.m[1][0] * a.m[3][1])
		+ (a.m[0][2] * a.m[1][1] * a.m[3][0]) + (a.m[0][1] * a.m[1][0] * a.m[3][2]) + (a.m[0][0] * a.m[1][2] * a.m[3][1]);
	inverseM.m[3][3]
		= (a.m[0][0] * a.m[1][1] * a.m[2][2]) + (a.m[0][1] * a.m[1][2] * a.m[2][0]) + (a.m[0][2] * a.m[1][0] * a.m[2][1])
		- (a.m[0][2] * a.m[1][1] * a.m[2][0]) - (a.m[0][1] * a.m[1][0] * a.m[2][2]) - (a.m[0][0] * a.m[1][2] * a.m[2][1]);

	float A =
		a.m[0][0] * a.m[1][1] * a.m[2][2] * a.m[3][3] + a.m[0][0] * a.m[1][2] * a.m[2][3] * a.m[3][1] + a.m[0][0] * a.m[1][3] * a.m[2][1] * a.m[3][2]
		- a.m[0][0] * a.m[1][3] * a.m[2][2] * a.m[3][1] - a.m[0][0] * a.m[1][2] * a.m[2][1] * a.m[3][3] - a.m[0][0] * a.m[1][1] * a.m[2][3] * a.m[3][2]
		- a.m[0][1] * a.m[1][0] * a.m[2][2] * a.m[3][3] - a.m[0][2] * a.m[1][0] * a.m[2][3] * a.m[3][1] - a.m[0][3] * a.m[1][0] * a.m[2][1] * a.m[3][2]
		+ a.m[0][3] * a.m[1][0] * a.m[2][2] * a.m[3][1] + a.m[0][2] * a.m[1][0] * a.m[2][1] * a.m[3][3] + a.m[0][1] * a.m[1][0] * a.m[2][3] * a.m[3][2]
		+ a.m[0][1] * a.m[1][2] * a.m[2][0] * a.m[3][3] + a.m[0][2] * a.m[1][3] * a.m[2][0] * a.m[3][1] + a.m[0][3] * a.m[1][1] * a.m[2][0] * a.m[3][2]
		- a.m[0][3] * a.m[1][2] * a.m[2][0] * a.m[3][1] - a.m[0][2] * a.m[1][1] * a.m[2][0] * a.m[3][3] - a.m[0][1] * a.m[1][3] * a.m[2][0] * a.m[3][2]
		- a.m[0][1] * a.m[1][2] * a.m[2][3] * a.m[3][0] - a.m[0][2] * a.m[1][3] * a.m[2][1] * a.m[3][0] - a.m[0][3] * a.m[1][1] * a.m[2][2] * a.m[3][0]
		+ a.m[0][3] * a.m[1][2] * a.m[2][1] * a.m[3][0] + a.m[0][2] * a.m[1][1] * a.m[2][3] * a.m[3][0] + a.m[0][1] * a.m[1][3] * a.m[2][2] * a.m[3][0];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			inverseM.m[i][j] *= 1 / A;
		}
	}

	return inverseM;
}

// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 m1 = { 0.0f };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m1.m[i][j] = m.m[j][i];
		}
	}

	return m1;
}

// 6. 単位行列の作成
Matrix4x4 MakeIdentity4x4()
{
	return { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f };
}

// 4x4行列の数値表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]
			);
		}
	}
}
// 1. 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	return
	{
		1.0f,		 0.0f,		  0.0f,		   0.0f,
		0.0f,		 1.0f,		  0.0f,		   0.0f,
		0.0f,		 0.0f,		  1.0f,		   0.0f,
		translate.x, translate.y, translate.z, 1.0f
	};
}

// 2. 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	return
	{
		scale.x,	0.0f,		0.0f,		0.0f,
		0.0f,		scale.y,	0.0f,		0.0f,
		0.0f,		0.0f,		scale.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
	};
}

// 3. 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0]
		+ vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1]
		+ vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2]
		+ vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float  w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3]
		+ vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}
// 1. X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian)
{
	return
	{
		 1.0f,	 0.0f,			   0.0f,			 0.0f,
		 0.0f,   std::cos(radian), std::sin(radian), 0.0f,
		 0.0f,	-std::sin(radian), std::cos(radian), 0.0f,
		 0.0f,	 0.0f,			   0.0f,			 1.0f
	};
}

// 2. Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian)
{
	return
	{
		 std::cos(radian), 0.0f, -std::sin(radian), 0.0f,
		 0.0f,			   1.0f,  0.0f,				0.0f,
		 std::sin(radian), 0.0f,  std::cos(radian), 0.0f,
		 0.0f,			   0.0f,  0.0f,				1.0f
	};
}

// 3. Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian)
{
	return
	{
		 std::cos(radian), std::sin(radian), 0.0f, 0.0f,
		-std::sin(radian), std::cos(radian), 0.0f, 0.0f,
		 0.0f,			   0.0f,			 1.0f, 0.0f,
		 0.0f,			   0.0f,			 0.0f, 1.0f
	};
}

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	return
		Multiply(MakeScaleMatrix(scale),
			Multiply(
				Multiply(MakeRotateXMatrix(rotate.x),
				Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z))), 
				MakeTranslateMatrix(translate)));
}

Matrix4x4 MakeAffineMatrixMy(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	return Matrix4x4
	{

		scale.x * (std::cos(rotate.y) * std::cos(rotate.z)),
		scale.x * (std::cos(rotate.y) * std::sin(rotate.z)),
		scale.x * (-std::sin(rotate.y)),
		0.0f,

		scale.y * (-std::cos(rotate.x) * std::sin(rotate.z) + std::sin(rotate.x) * std::sin(rotate.y) * std::cos(rotate.z)),
		scale.y * (std::cos(rotate.x) * std::cos(rotate.z) + std::sin(rotate.x) * std::sin(rotate.y) * std::sin(rotate.z)),
		scale.y * (std::sin(rotate.x) * std::cos(rotate.y)),
		0.0f,

		scale.z * (std::sin(rotate.x) * std::sin(rotate.z) + std::cos(rotate.x) * std::sin(rotate.y) * std::cos(rotate.z)),
		scale.z * (-std::sin(rotate.x) * std::cos(rotate.z) + std::cos(rotate.x) * std::sin(rotate.y) * std::sin(rotate.z)),
		scale.z * (std::cos(rotate.x) * std::cos(rotate.y)),
		0.0f,

		translate.x,
		translate.y,
		translate.z,
		1.0f
	};
}

Matrix4x4 MakeAffineMatrixGPT(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	float cx = std::cos(rotate.x), sx = std::sin(rotate.x);
	float cy = std::cos(rotate.y), sy = std::sin(rotate.y);
	float cz = std::cos(rotate.z), sz = std::sin(rotate.z);

	// Rx * Ry * Rz の合成
	float r00 = cy * cz;
	float r01 = cy * sz;
	float r02 = -sy;

	float r10 = -cx * sz + sx * sy * cz;
	float r11 = cx * cz + sx * sy * sz;
	float r12 = sx * cy;

	float r20 = sx * sz + cx * sy * cz;
	float r21 = -sx * cz + cx * sy * sz;
	float r22 = cx * cy;

	// スケーリング適用（各行ごと）
	r00 *= scale.x;  r01 *= scale.x;  r02 *= scale.x;
	r10 *= scale.y;  r11 *= scale.y;  r12 *= scale.y;
	r20 *= scale.z;  r21 *= scale.z;  r22 *= scale.z;

	// アフィン行列を構築
	return Matrix4x4{
		r00, r01, r02, 0.0f,
		r10, r11, r12, 0.0f,
		r20, r21, r22, 0.0f,
		translate.x, translate.y, translate.z, 1.0f
	};
}