//#define _XM_NO_INTRINSICS_

#include "pch.h"
#include <iostream>
#include <d3d9.h>
//#pragma comment (lib, "d3d9.lib")
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

void TestMatrix();
void printTitle(const char *title);
void printm(XMMATRIX &mat);
void printm(const char* title, XMMATRIX &mat);

int main() {
	TestMatrix();
	return 0;
}
void TestMatrix() {
	printTitle("행렬과 단위행렬의 곱");
	{
		XMMATRIX matMatrix, matResult;
		for (size_t i = 0; i < 4; i++) {
			for (size_t ii = 0; ii < 4; ii++) {
				matMatrix(i, ii) = i;
			}
		}
		//단위행렬
		XMMATRIX matIdentity = XMMatrixIdentity();
		//행렬과 단위행렬의 곱 방법1.
		matResult = matMatrix * matIdentity;
		//행렬과 단위행렬의 곱 방법2.
		matResult = XMMatrixMultiply(matMatrix, matIdentity);

		printm("matMatrix", matMatrix);
		printm("matIdentity", matIdentity);
		printm("matResult", matResult);
	}
	printTitle("전치행렬");
	{
		XMMATRIX matMatrix;
		for (size_t i = 0; i < 4; i++) {
			for (size_t ii = 0; ii < 4; ii++) {
				matMatrix(i, ii) = i;
			}
		}
		//전치행렬
		XMMATRIX matTranspose = XMMatrixTranspose(matMatrix);
		printm("matMatrix", matMatrix);
		printm("matTranspose", matTranspose);
		//전치행렬을 다시 전치행렬로 만들기
		XMMATRIX matResult = XMMatrixTranspose(matTranspose);
		printm("matResult", matResult);
	}
	printTitle("역행렬");
	{
		XMMATRIX matMatrix;
		//회전행렬
		XMMATRIX matRotation = XMMatrixRotationX(0.3f);
		//역행렬
		XMVECTOR det;
		XMMATRIX matInverse = XMMatrixInverse(&det, matRotation);
		printm("matRotation", matRotation);
		printm("matInverse", matInverse);
		printf_s("det : %f\n", det.vector4_f32[0]);
		//회전행렬과 역행렬의 곱 = 단위행렬
		XMMATRIX matResult = XMMatrixMultiply(matRotation, matInverse);
		printm("matResult", matResult);
	}
}
//functions
void printTitle(const char *title) {
	printf_s("=== %s ===\n", title);
}
void printm(XMMATRIX &mat) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t ii = 0; ii < 4; ii++) {
			printf_s("%.1f\t", mat.m[i][ii]);
			//printf_s("%f\t", mat(i, ii));
		}
		printf_s("\n");
	}
}
void printm(const char *title, XMMATRIX &mat) {
	printf_s("= %s =\n", title);
	printm(mat);
}