//#define _XM_NO_INTRINSICS_

#include "pch.h"
#include <iostream>
#include <d3d9.h>
//#pragma comment (lib, "d3d9.lib")
#include <DirectXMath.h>

#define PI 3.14159265359

using namespace std;
using namespace DirectX;

void TestMatrix();
void TestMatrixLinear();
void TestMatrixQuaternion();
void printTitle(const char *title);
void printMatrix(XMMATRIX &mat);
void printMatrix(const char* title, XMMATRIX &mat);
void printVector(XMVECTOR &vec);
void printVector(const char* title, XMVECTOR &vec);

int main() {
	//TestMatrix();
	//TestMatrixLinear();
	TestMatrixQuaternion();
	return 0;
}
void TestMatrixQuaternion() {
	printTitle("회전 행렬을 쿼터니온으로 만드는 함수");
	{
		XMMATRIX matRotation = XMMatrixRotationX(PI);
		printMatrix("matRotation", matRotation);
		/*
		1.0     0.0     0.0     0.0
		0.0     -1.0    0.0     0.0
		0.0     -0.0    -1.0    0.0
		0.0     0.0     0.0     1.0
		*/
		XMVECTOR vQuaternion = XMQuaternionRotationMatrix(matRotation);
		printVector("vQuaternion", vQuaternion);
		/*
		1.0     0.0     0.0     0.0
		*/
	}
	printTitle("yaw, pitch, roll에 의한 쿼터니온을 만드는 함수");
	{
		XMVECTOR vQuaternion = XMQuaternionRotationRollPitchYaw(PI, PI, PI);
		printVector("vQuaternion", vQuaternion);
		/*
		-0.0    0.0     0.0     1.0
		*/
	}
	printTitle("임의의 축에 대해서 회전한 쿼터니온을 구하는 함수");
	{
		XMVECTOR vQuaternion = XMQuaternionRotationAxis({ 1.0, 0, 0, 0 }, PI);
		printVector("vQuaternion", vQuaternion);
		/*
		1.0     0.0     0.0     -0.0
		*/
	}
	printTitle("쿼터니온으로부터 회전 행렬을 구하는 함수");
	{
		XMVECTOR vQuaternion = XMQuaternionRotationAxis({ 1.0, 0, 0, 0 }, PI);
		printVector("vQuaternion", vQuaternion);
		/*
		1.0     0.0     0.0     -0.0
		*/
		XMMATRIX matRotation = XMMatrixRotationQuaternion(vQuaternion);
		printMatrix("matRotation", matRotation);
		/*
		1.0     0.0     0.0     0.0
		0.0     -1.0    -0.0    0.0
		0.0     0.0     -1.0    0.0
		0.0     0.0     0.0     1.0
		*/
	}
	printTitle("길이가 1인 쿼터이온을 구하는 함수");
	{
		XMVECTOR vQuaternion = { 1.0, 2.0, 3.0, 4.0 };
		printVector("vQuaternion", vQuaternion);
		/*
		1.0     2.0     3.0     4.0
		*/
		vQuaternion = XMQuaternionNormalize(vQuaternion);
		printVector("vQuaternion", vQuaternion);
		/*
		0.2     0.4     0.5     0.7
		*/
	}
}
void TestMatrixLinear() {
	printTitle("이동행렬");
	{
		XMMATRIX matTranslation = XMMatrixTranslation(10, 20, 30);
		printMatrix("matTranslation", matTranslation);
		/*
		1.0     0.0     0.0     0.0
		0.0     1.0     0.0     0.0
		0.0     0.0     1.0     0.0
		10.0    20.0    30.0    1.0
		*/
	}
	printTitle("크기행렬");
	{
		XMMATRIX matScaling = XMMatrixScaling(0.5, 0.5, 0.5);
		printMatrix("matScaling", matScaling);
		/*
		0.5     0.0     0.0     0.0
		0.0     0.5     0.0     0.0
		0.0     0.0     0.5     0.0
		0.0     0.0     0.0     1.0
		*/
	}
	printTitle("라디안과 호도값");
	{
		printf_s("%f\n", XMConvertToRadians(90) );
		//1.570796
		printf_s("%f\n", XMConvertToDegrees(3.14) );
		//179.908737
	}
	printTitle("회전행렬");
	{
		XMMATRIX matRotationX = XMMatrixRotationX(PI);
		printMatrix("matRotationX", matRotationX);
		/*
		1.0     0.0     0.0     0.0
		0.0     -1.0    0.0     0.0
		0.0     -0.0    -1.0    0.0
		0.0     0.0     0.0     1.0
		*/
		XMMATRIX matRotationRollPitchYaw = XMMatrixRotationRollPitchYaw(PI, PI, PI);
		printMatrix("matRotationRollPitchYaw", matRotationRollPitchYaw);
		/*
		1.0     0.0     -0.0    0.0
		-0.0    1.0     -0.0    0.0
		0.0     0.0     1.0     0.0
		0.0     0.0     0.0     1.0
		*/
		XMMATRIX matRotationAxis = XMMatrixRotationAxis({1.0, 0, 0,0}, PI);
		printMatrix("matRotationAxis", matRotationAxis);
		/*
		1.0     0.0     0.0     0.0
		0.0     -1.0    0.0     0.0
		0.0     0.0     -1.0    0.0
		0.0     0.0     0.0     1.0
		*/
	}
	printTitle("크기, 회전, 이동 행렬의 결합");
	{
		XMMATRIX matComposite = XMMatrixScaling(0.5, 0.5, 0.5)
			* XMMatrixRotationRollPitchYaw(PI, PI, PI)
			* XMMatrixTranslation(10, 20, 30);
		printMatrix("matComposite", matComposite);
		/*
		0.5     0.0     -0.0    0.0
		-0.0    0.5     -0.0    0.0
		0.0     0.0     0.5     0.0
		10.0    20.0    30.0    1.0
		*/
	}
}
void TestMatrix() {
	printTitle("행렬과 단위행렬의 곱");
	{
		XMMATRIX matMatrix = {
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
			{41, 42, 43, 44},
		};
		//단위행렬
		XMMATRIX matIdentity = XMMatrixIdentity();
		//행렬과 단위행렬의 곱 방법1
		XMMATRIX matResult = matMatrix * matIdentity;
		//행렬과 단위행렬의 곱 방법2
		matResult = XMMatrixMultiply(matMatrix, matIdentity);
		//출력
		printMatrix("matMatrix", matMatrix);
		printMatrix("matIdentity", matIdentity);
		printMatrix("matResult", matResult);
		/*
		- matMatrix -
		11.0    12.0    13.0    14.0
		21.0    22.0    23.0    24.0
		31.0    32.0    33.0    34.0
		41.0    42.0    43.0    44.0
		- matIdentity -
		1.0     0.0     0.0     0.0
		0.0     1.0     0.0     0.0
		0.0     0.0     1.0     0.0
		0.0     0.0     0.0     1.0
		- matResult -
		11.0    12.0    13.0    14.0
		21.0    22.0    23.0    24.0
		31.0    32.0    33.0    34.0
		41.0    42.0    43.0    44.0
		*/
	}
	printTitle("전치행렬");
	{
		XMMATRIX matMatrix = {
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
			{41, 42, 43, 44},
		};
		//전치행렬
		XMMATRIX matTranspose = XMMatrixTranspose(matMatrix);
		printMatrix("matMatrix", matMatrix);
		printMatrix("matTranspose", matTranspose);
		/*
		- matMatrix -
		11.0    12.0    13.0    14.0
		21.0    22.0    23.0    24.0
		31.0    32.0    33.0    34.0
		41.0    42.0    43.0    44.0
		- matTranspose -
		11.0    21.0    31.0    41.0
		12.0    22.0    32.0    42.0
		13.0    23.0    33.0    43.0
		14.0    24.0    34.0    44.0
		*/
		//전치행렬을 다시 전치행렬로 만들기
		XMMATRIX matResult = XMMatrixTranspose(matTranspose);
		printMatrix("matResult", matResult);
		/*
		- matResult -
		11.0    12.0    13.0    14.0
		21.0    22.0    23.0    24.0
		31.0    32.0    33.0    34.0
		41.0    42.0    43.0    44.0
		*/
	}
	printTitle("역행렬");
	{
		XMMATRIX matMatrix;
		//회전행렬
		XMMATRIX matRotation = XMMatrixRotationX(0.3f);
		//행렬식값(0이면 역행렬이 존재하지 않고 0이외의 값이면 역행렬이 존재한다)
		XMVECTOR fDeterminant;
		//역행렬(회전행렬은 항상 역행렬이 존재)
		XMMATRIX matInverse = XMMatrixInverse(&fDeterminant, matRotation);
		printMatrix("matRotation", matRotation);
		printMatrix("matInverse", matInverse);
		printf_s("- fDeterminant : %f\n", fDeterminant.vector4_f32[0]);
		/*
		- matRotation -
		1.0     0.0     0.0     0.0
		0.0     1.0     0.3     0.0
		0.0     -0.3    1.0     0.0
		0.0     0.0     0.0     1.0
		- matInverse -
		1.0     -0.0    0.0     0.0
		0.0     1.0     -0.3    0.0
		0.0     0.3     1.0     0.0
		0.0     0.0     0.0     1.0
		- fDeterminant : 1.000000
		*/
		//회전행렬과 역행렬의 곱 = 단위행렬
		XMMATRIX matResult = XMMatrixMultiply(matRotation, matInverse);
		printMatrix("matResult", matResult);
		/*
		- matResult -
		1.0     0.0     0.0     0.0
		0.0     1.0     0.0     0.0
		0.0     0.0     1.0     0.0
		0.0     0.0     0.0     1.0
		*/
	}
}
//functions
void printTitle(const char *title) {
	printf_s("=== %s ===\n", title);
}
void printMatrix(XMMATRIX &mat) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t ii = 0; ii < 4; ii++) {
			printf_s("%#2.1f\t", mat.m[i][ii]);
			//printf_s("%f\t", mat(i, ii));
		}
		printf_s("\n");
	}
}
void printVector(XMVECTOR &vec) {
	for (size_t i = 0; i < 4; i++) {
		printf_s("%#2.1f\t", vec.vector4_f32[i]);
	}
	printf_s("\n");
}
void printMatrix(const char *title, XMMATRIX &mat) {
	printf_s("- %s\n", title);
	printMatrix(mat);
}
void printVector(const char *title, XMVECTOR &vec) {
	printf_s("- %s\n", title);
	printVector(vec);
}