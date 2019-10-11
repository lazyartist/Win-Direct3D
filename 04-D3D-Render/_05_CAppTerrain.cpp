#include "stdafx.h"
#include <d3dx9shape.h>
#include "_05_CAppTerrain.h"

CAppTerrain::CAppTerrain() {
}
CAppTerrain::~CAppTerrain(){
}
void CAppTerrain::OnInit() {
	pD3DFramework->vCameraEye = {10.0f, 10.0f, -10.0f};

	//지형 버텍스 생성, 행과 열로 생성한다.
	int iTerrainVertexCount = iTerrainVertexRow * iTerrainVertexCol;
	vTerrainVertices = new SVertex[iTerrainVertexCount];
	for (size_t i = 0; i < iTerrainVertexCount; i++)
	{
		int iRow = i / iTerrainVertexCol;
		int iCol = i % iTerrainVertexCol;
		//평평한 지형
		//vTerrainVertices[i] = { (float)iCol * fTerrainTriangleScale, 0.0f, (float)iRow * -fTerrainTriangleScale, 0xffffffff };
		//가운데가 솟아오른 지형
		vTerrainVertices[i] = { (float)iCol * fTerrainTriangleScale, 
			-(sin(D3DX_PI * 2.0f / iTerrainVertexCount * i + D3DX_PI * 0.5f)) * fTerrainHeight + fTerrainHeight, 
			(float)iRow * -fTerrainTriangleScale, 0xffffffff };
	}

	//버텍스버퍼 생성
	pD3DFramework->pD3DDevice->CreateVertexBuffer(
		sizeof(SVertex)*iTerrainVertexCount,//버텍스배열의 크기
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFVF_SVertex,//버텍스 타입
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pVB,//반환된 버텍스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//버텍스버퍼에 버텍스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 정점을 저장할 메모리 포인터를 반환한다.
	void *pVertices;//버텍스를 저장할 메모리의 시작 주소를 받을 변수
	pVB->Lock(0, 0, (void**)&pVertices, 0);
	memcpy(pVertices, vTerrainVertices, sizeof(SVertex)*iTerrainVertexCount);//버텍스버퍼에 버텍스를 메모리 복사
	pVB->Unlock();//잠금을 해제

	//버텍스개수로 삼각형개수 구하기
	//=(버텍스로우-1) * (버텍스컬럼-1)*2
	//첫번째 버텍스행은 무시(일직선의 버텍스들로는 삼각형을 만들 수 없기 때문)
	//두번째 버텍스행부터 가장 좌측 버텍스를 제외하고 모든 버텍스가 삼각형을 두개씩 생성
	int iTriangleColCount = (iTerrainVertexCol - 1) * 2;//한줄당 삼각형 개수
	int iTriangleCount = (iTerrainVertexRow - 1) * iTriangleColCount;

	//버텍스인덱스 생성
	//방법1. 좌상에서 우하로 나뉘는 삼각형
	//이 방식의 장점은 사각형 단위로 그리기 때문에 로직이 단순하다.
	int iIndicesCount = iTriangleCount * 3;
	vTerrainIndices = new WORD[iIndicesCount];
	for (size_t i = 0; i < iTriangleCount; i+=2)
	{
		int iTriangleRow = i / iTriangleColCount;//현재 삼각형의 행번호
		int iVerticesIndex = iTriangleRow + i / 2;
		int iIndicesIndex = i * 3;
		//↘←↑
		vTerrainIndices[iIndicesIndex] = iVerticesIndex;
		vTerrainIndices[iIndicesIndex + 1] = iVerticesIndex + 1 + iTerrainVertexCol;
		vTerrainIndices[iIndicesIndex + 2] = iVerticesIndex + iTerrainVertexCol;
		//→↓↖
		vTerrainIndices[iIndicesIndex + 3] = iVerticesIndex;
		vTerrainIndices[iIndicesIndex + 4] = iVerticesIndex + 1;
		vTerrainIndices[iIndicesIndex + 5] = iVerticesIndex + 1 + iTerrainVertexCol;
	}

	////버텍스인덱스 생성
	////방법2. 좌하에서 우상으로 나뉘는 삼각형
	////이 방식의 단점은 사각형 단위로 그리지 않고 삼각형 단위로 그리기 때문에 로직이 복잡하다.
	////인덱스를 1부터 시작하면 가능하지만 1로 시작하는 것부터 복잡하다.
	//int iIndicesCount = iTriangleCount * 3;
	//vTerrainIndices = new WORD[iIndicesCount];
	//for (size_t i = 0; i < iTriangleCount; i++)
	//{
	//	int iTriangleRow = i / iTriangleColCount;//현재 삼각형의 행번호
	//	//가장 오른쪽 정점은 삼각형을 만들지 않으므로 다음 행 첫번째 정점으로 건너뛰기 위해 행번호를 더해준다.
	//	int iVerticesIndex = iTriangleRow;
	//	int iIndicesIndex = 0;
	//	iIndicesIndex = i * 3;
	//	if (i % 2 == 0) {
	//		//짝수번째 삼각형은 →↙↑이렇게 그린다.
	//		iVerticesIndex += i / 2;
	//		vTerrainIndices[iIndicesIndex] = iVerticesIndex;
	//		vTerrainIndices[iIndicesIndex + 1] = iVerticesIndex + 1;
	//		vTerrainIndices[iIndicesIndex + 2] = iVerticesIndex + iTerrainVertexCol;
	//	}
	//	else {
	//		//홀수번째 삼각형은 ↓←↗이렇게 그린다.
	//		iVerticesIndex += i - (int)(i / 2);
	//		vTerrainIndices[iIndicesIndex] = iVerticesIndex;
	//		vTerrainIndices[iIndicesIndex + 1] = iVerticesIndex + iTerrainVertexCol;
	//		vTerrainIndices[iIndicesIndex + 2] = iVerticesIndex + iTerrainVertexCol - 1;
	//	}
	//}

	//인덱스버퍼 생성
	pD3DFramework->pD3DDevice->CreateIndexBuffer(
		sizeof(WORD)*iIndicesCount,//인덱스배열의 크기
		D3DUSAGE_WRITEONLY,//리소스 사용법을 지정(D3DUSAGE_WRITEONLY:어플에서 버텍스버퍼의 쓰기 조작만 수행함을 지정)
		D3DFMT_INDEX16,//인덱스 타입
		D3DPOOL_DEFAULT,//리소스버퍼를 저장할 시스템, 비디오 메모리를 지정(D3DPOOL_DEFAULT:최적의 메모리를 자동 선택)
		&pIB,//반환된 인덱스버퍼를 받을 포인터
		nullptr//사용하지 않는 변수, nullptr
	);
	//인덱스버퍼에 인덱스를 저장하기 위해 잠금
	//Lock을 하면 다른 자원이 접근할 수 없게되고 인덱스를 저장할 메모리 포인터를 반환한다.
	void *pIndices;//인덱스를 저장할 메모리의 시작 주소를 받을 변수
	pIB->Lock(0, sizeof(vTerrainIndices), (void**)&pIndices, 0);
	memcpy(pIndices, vTerrainIndices, sizeof(WORD)*iIndicesCount);//인덱스버퍼에 인덱스를 메모리 복사
	pIB->Unlock();//잠금을 해제
	//Viewport
	//D3DVIEWPORT9 d3dViewport9 = {};
	//d3dViewport9.X = 0;//렌더링타겟 표면에서 뷰포트가 시작될 x위치
	//d3dViewport9.Y = 0;//렌더링타겟 표면에서 뷰포트가 시작될 y위치
	//d3dViewport9.Width = 800;//렌더링타겟에서 출력될 가로 크기
	//d3dViewport9.Height = 800;//렌더링타겟에서 출력될 세로 크기
	//d3dViewport9.MinZ = 0.0;//깊이버퍼의 최소 범위
	//d3dViewport9.MaxZ = 1.0;//깊이버퍼의 최대 범위
	//pD3DFramework->pD3DDevice->SetViewport(&d3dViewport9);
}

void CAppTerrain::OnUpdate(DWORD fDeltaTime) {
	if (GetAsyncKeyState(VK_UP) < 0) {
		//메쉬를 앞으로 이동, 메쉬의 정면 벡터의 초기값은 {0, 0, 1}이고 회전에 따라 방향이 바뀐다.
		D3DXVECTOR4 vMeshFront = {};
		D3DXMATRIX matFront;
		D3DXMatrixRotationY(&matFront, vMeshRotation.y);//회전행렬
		D3DXVec3Transform(&vMeshFront, &vMESH_FRONT/*(0,0,1)*/, &matFront);//메쉬정면 벡터를 회전
		D3DXVec4Normalize(&vMeshFront, &vMeshFront);//정면벡터 정규화
		vMeshTranslation += (D3DXVECTOR3)vMeshFront * 0.1;//현재 메쉬의 위치에 정면벡터를 더해서 이동시킨다.
	}
	if (GetAsyncKeyState(VK_DOWN) < 0) {
		//메쉬를 앞으로 이동, 메쉬의 정면 벡터의 초기값은 {0, 0, 1}이고 회전에 따라 방향이 바뀐다.
		D3DXVECTOR4 vMeshFront = {};
		D3DXMATRIX matFront;
		D3DXMatrixRotationY(&matFront, vMeshRotation.y);//회전행렬
		D3DXVec3Transform(&vMeshFront, &vMESH_FRONT/*(0,0,1)*/, &matFront);//메쉬정면 벡터를 회전
		D3DXVec4Normalize(&vMeshFront, &vMeshFront);//정면벡터 정규화
		vMeshTranslation -= (D3DXVECTOR3)vMeshFront * 0.1;//현재 메쉬의 위치에 정면벡터를 더해서 이동시킨다.
	}
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		//메쉬를 좌(CCW)로 회전
		vMeshRotation.y -= 0.1;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		//메쉬를 우(CW)로 회전
		vMeshRotation.y += 0.1;
	}
}

void CAppTerrain::OnRender(DWORD fDeltaTime) {
	//World transformation
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMatrixScaling(&matScale, vMeshScale.x, vMeshScale.y, vMeshScale.z);//크기행렬
	D3DXMatrixRotationY(&matRotation, vMeshRotation.y);//회전행렬
	D3DXMatrixTranslation(&matTranslation, vMeshTranslation.x, vMeshTranslation.y, vMeshTranslation.z);//이동행렬
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale * matRotation * matTranslation));
	//View, Projection transformation은 CD3DFramework에서 설정한다.

	//렌더링 상태 설정
	//Light Off
	//정점 쉐이더 작업을 하지 않을 때는 라이팅을 꺼줘야 버텍스 색상을 볼 수 있다.
	//그렇지 않으면 검은색으로 출력된다.
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//채우기모드를 와이어프레임으로 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//컬링을 하지 않도록 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pD3DFramework->pD3DDevice->SetStreamSource(
		0,//0으로 지정
		pVB, //버텍스버퍼
		0, //메모리시작 위치
		sizeof(SVertex) //버텍스 크기
	);
	//2. D3D에 정점 데이터를 어떻게 해석해하는지 설정한다.
	pD3DFramework->pD3DDevice->SetFVF(D3DFVF_SVertex);

	int iTriangleColCount = (iTerrainVertexCol - 1) * 2;//한줄당 삼각형 개수
	int iTriangleCount = (iTerrainVertexRow - 1) * iTriangleColCount;
	//인덱스버퍼 입력
	pD3DFramework->pD3DDevice->SetIndices(pIB);
	pD3DFramework->pD3DDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,//D3DPT_LINELIST, D3DPT_TRIANGLESTRIP
		0,//정점버퍼의 시작인덱스 오프셋. 만약 1일 경우 인덱스 버퍼의 0값이 정점 버퍼의 1인덱스를 가리킨다.
		0,//정점버퍼의 최소인덱스. 만약 1일 경우 0번 정점은 사용되지 않는다.
		iTerrainVertexRow * iTerrainVertexCol,//그려질 정점의 개수, BaseVertexIndex + MinIndex 만큼 빼주면 된다.
		0,//인덱스버퍼의 시작인덱스 오프셋. 만약 1일 경우 1번 인덱스버퍼부터 그린다.
		iTriangleCount//그려질 도형(삼각형)의 개수
	);

	//Light Off
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//컬링을 다시 켜준다
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CAppTerrain::OnRelease() {
	if (vTerrainVertices != nullptr) {
		delete[] vTerrainVertices;
	}
	if (vTerrainIndices != nullptr) {
		delete[] vTerrainIndices;
	}
	if (pVB != nullptr) {
		pVB->Release();
		pVB = nullptr;
	}
	if (pIB != nullptr) {
		pIB->Release();
		pIB = nullptr;
	}
}
