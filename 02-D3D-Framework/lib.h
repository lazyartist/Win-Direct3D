#pragma once

#include <vector>
#include <deque>
#include <list>
#include "windows.h"
//#include "function.h"
#define _USE_MATH_DEFINES // math.h�� ����ϱ� ���� �ʿ�
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm")
#include <d3d9.h>
#include <DirectXMath.h>
#include <d3dx9math.h>
//#include <DirectXMath.h>

using namespace DirectX;

// ===== vertex =====
#define D3DFVF_SVertex (D3DFVF_XYZ | D3DFVF_DIFFUSE)
struct SVertex {
	float x, y, z;
	DWORD color;
};
struct SVertex2{
	XMFLOAT3 position;
	DWORD color;
};
//#define D3DFVF_SVertex3 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)
#define D3DFVF_SVertex3 (D3DFVF_XYZ | D3DFVF_NORMAL)
struct SVertex3 {
	D3DXVECTOR3 xyz;
	D3DXVECTOR3 normal;
	//DWORD diffuse;
};
#define D3DFVF_SVertexTexture (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
struct SVertexTexture {
	D3DXVECTOR3 xyz;
	D3DXVECTOR3 normal;
	float tu, tv;
};
#define D3DFVF_SVertexRHW (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
struct SVertexRHW {
	float x, y, z, rhw;
	DWORD color;
};
// ===== vertex ===== end

static class Const {
public:
	// string length
	const static int szMax_Path = MAX_PATH;
	const static int szMax_ItemCount = _MAX_INT_DIG;
	const static int szMax_ListColumnName = 32;
	const static int szMax_ItemLine = MAX_PATH;
	const static int szMax_StageName = MAX_PATH;

	// float
	// static float�� Ŭ���� ���ο��� �ʱ�ȭ �� �� ���� int�� �����ϱ� ������ �Լ��� �����.
	// �����Ӵ� �̵��� �Ÿ���ŭ�� �̵��ϸ� "�̵� -> ���̵� -> �̵�" �̷������� ���̵� ���°� ���� �ִϸ��̼��� �����.
	// ���� ������ �� �̵��Ÿ��� �÷� �� �����ӿ� �̵��� �Ϸ���� ���ϵ����ؼ� �߰��� ���̵� ���°� �����ʰ� �ϱ����� ��.
	//const static int fSpeedPerFrameMagnification = 2;
	static float fSpeedPerFrameMagnification() {
		return 2.0;
	};
	static float fGravity() {
		return 800.0;
		//return 10.0;
		//return 9.8;
	};
	static float fPI() {
		return 3.14159265359;
	};
	static float fPI14() {
		return 3.14159265359 / 4;
	};
	static float fPI34() {
		return 3.14159265359 * 3 / 4;
	};

	// string
	//static const char *szActionTypesAsString[EActionType::EActionType_Count];
	//static const char *szUnitTypesAsString[EUnitType::EUnitType_Count];
	//static const char *szControlTypesAsString[EControlType::EControlType_Count];
	//static const char *szStageSettingFileName;
};

// ===== log =====
// for string
inline void _dlog(UINT count, const char *args, ...) {
	va_list ap; // �������� �޸� �ּ�
	va_start(ap, args); // �������� �޸� �ּ� ����
	OutputDebugString(args); // ������ �ִ� ���� �׳� ���
	for (size_t i = 0; i < count - 1; i++) {
		OutputDebugString(", ");
		char *str = va_arg(ap, char *); // �������ڴ� va_list���� �ڷ��� ũ�⸸ŭ �̵��� ���� ���� ���
		OutputDebugString(str);

	}
	OutputDebugString("\n");
	va_end(ap);
};
// for int
inline void _dlog(const char *title, UINT count, int args, ...) {
	va_list ap; // �������� �޸� �ּ�
	va_start(ap, args); // �������� �޸� �ּ� ����
	// ���� ���
	if (title[0] != '\0') {
		OutputDebugString(title); // ������ �ִ� ���� �׳� ���
		OutputDebugString(" : "); // ������ �ִ� ���� �׳� ���
	}
	// ù��° ���� ���
	{
		char buffer[11];
		sprintf_s(buffer, 11, "%d", args);
		OutputDebugString(buffer);
	}
	// �������� ���
	for (size_t i = 0; i < count - 1; i++) {
		// char, short, int�� int Ÿ�� ũ��� �̵�
		// �������ڴ� va_list���� �ڷ��� ũ�⸸ŭ �̵��� ���� ���� ���
		int arg = va_arg(ap, int);
		OutputDebugString(", ");
		char buffer[11];
		sprintf_s(buffer, 11, "%d", arg);
		OutputDebugString(buffer);
	}
	OutputDebugString("\n");
	va_end(ap);
};
// for float
inline void _dlog(const char *title, UINT count, float args, ...) {
	va_list ap; // �������� �޸� �ּ�
	va_start(ap, args); // �������� �޸� �ּ� ����
	// ���� ���
	OutputDebugString(title); // ������ �ִ� ���� �׳� ���
	OutputDebugString(" : ");
	// ù��° ���� ���
	{
		char buffer[FLT_MAX_10_EXP];
		sprintf_s(buffer, FLT_MAX_10_EXP, "%f", args);
		OutputDebugString(buffer);
	}
	// �������� ���
	for (size_t i = 0; i < count - 1; i++) {
		// float�� double Ÿ�� ũ��� �̵�
		// https://stackoverflow.com/questions/11270588/variadic-function-va-arg-doesnt-work-with-float
		float arg = va_arg(ap, double);
		OutputDebugString(", ");
		char buffer[FLT_MAX_10_EXP];
		sprintf_s(buffer, FLT_MAX_10_EXP, "%f", arg);
		OutputDebugString(buffer);
	}
	OutputDebugString("\n");
	va_end(ap);
};
inline void dlog(LPCSTR lpStr) {
	_dlog(1, lpStr);
};
inline void dlog(LPCSTR lpStr, LPCSTR lpStr2) {
	_dlog(2, lpStr, lpStr2);
};
inline void dlog(LPCSTR lpStr, LPCSTR lpStr2, LPCSTR lpStr3) {
	_dlog(3, lpStr, lpStr2, lpStr3);
};
inline void dlog(LPCSTR title, int i) {
	_dlog(title, 1, i);
};
inline void dlog(LPCSTR title, int i, int ii) {
	_dlog(title, 2, i, ii);
};
inline void dlog(LPCSTR title, int i, int ii, int iii) {
	_dlog(title, 3, i, ii, iii);
};
inline void dlog(int i) {
	_dlog("", 1, i);
};
inline void dlog(int i, int ii) {
	_dlog("", 2, i, ii);
};
inline void dlog(int i, int ii, int iii) {
	_dlog("", 3, i, ii, iii);
};
inline void dlog(LPCSTR title, float i) {
	_dlog(title, 1, i);
};
inline void dlog(float i) {
	_dlog("", 1, i);
};
inline void dlog(float i, float ii) {
	_dlog("", 2, i, ii);
};
inline void dlog(float i, float ii, float iii) {
	_dlog("", 3, i, ii, iii);
};
inline void dlog(float i, float ii, float iii, float iiii) {
	_dlog("", 4, i, ii, iii, iiii);
};
inline void dlog(RECT rect) {
	_dlog("", 4, rect.left, rect.top, rect.right, rect.bottom);
};
inline void dlog(const char *title, RECT rect) {
	_dlog(title, 4, rect.left, rect.top, rect.right, rect.bottom);
};
// ===== log ===== end