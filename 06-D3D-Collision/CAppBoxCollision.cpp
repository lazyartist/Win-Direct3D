#include "stdafx.h"
#include "CAppBoxCollision.h"

CAppBoxCollision::CAppBoxCollision() {
}
CAppBoxCollision::~CAppBoxCollision() {
}
void CAppBoxCollision::OnInit() {
	//camera
	pD3DFramework->vCameraEye = { 0.0, 5, -10 };
	//mesh
	D3DXCreateTeapot(pD3DFramework->pD3DDevice, &m_pMesh, nullptr);
	//bounding box
	D3DXVECTOR3 *pVertices;
	//버텍스 버퍼에 접근하기 위해 락을 건다.
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVertices);
	D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), 
		m_pMesh->GetNumBytesPerVertex(), &m_vBoundingBoxMin, &m_vBoundingBoxMax);
	D3DXCreateBox(pD3DFramework->pD3DDevice, 
		m_vBoundingBoxMax.x - m_vBoundingBoxMin.x,
		m_vBoundingBoxMax.y - m_vBoundingBoxMin.y,
		m_vBoundingBoxMax.z - m_vBoundingBoxMin.z,
		&m_pBoundingBoxMesh, nullptr);
}
void CAppBoxCollision::OnUpdate(DWORD fDeltaTime) {
	float fSpeed = GetAsyncKeyState(VK_CONTROL) < 0 ? 0.01f : 0.1f;
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		m_vPos1.x -= fSpeed;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		m_vPos1.x += fSpeed;
	}
	if (GetAsyncKeyState(VK_UP) < 0) {
		m_vPos1.y += fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN) < 0) {
		m_vPos1.y -= fSpeed;
	}
}
//bool CheckPointInBox(const D3DXVECTOR3 &vPoint, D3DXVECTOR3 &vBoxMin, D3DXVECTOR3 &vBoxMax) {
bool CheckPointInBox(D3DXVECTOR3 &vPoint, const D3DXVECTOR3 &vBoxMin, D3DXVECTOR3 &vBoxMax) {
	bool bColided = vBoxMin.x <= vPoint.x && vBoxMax.x >= vPoint.x &&
		vBoxMin.y <= vPoint.y && vBoxMax.y >= vPoint.y &&
		vBoxMin.z <= vPoint.z && vBoxMax.z >= vPoint.z;
	return bColided;
}
bool CheckCollision0(const D3DXVECTOR3 &vMin0, D3DXVECTOR3 &vMax0, D3DXVECTOR3 &vMin1, D3DXVECTOR3 &vMax1) {
	//박스의 꼭지점이 다른 박스에 있는지 확인
	D3DXVECTOR3 vDistance = vMax0 - vMin0;
	bool bColided = false;
	D3DXVECTOR3 vPoint = {};
	//min
	vPoint = vMin0;//left down
	bColided = CheckPointInBox(vPoint, vMin1, vMax1);
	vPoint = { vMin0.x, vMin0.y + vDistance.y, vMin0.z };//left up
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);
	vPoint = { vMin0.x + vDistance.x, vMin0.y + vDistance.y, vMin0.z };//right up 
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);
	vPoint = { vMin0.x + vDistance.x, vMin0.y, vMin0.z };//right down
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);
	//max
	vPoint = vMax0;//right up
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);
	vPoint = { vMax0.x, vMax0.y - vDistance.y, vMax0.z };//right down
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);
	vPoint = { vMax0.x - vDistance.x, vMax0.y - vDistance.y, vMax0.z };//left down
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);
	vPoint = { vMax0.x - vDistance.x, vMax0.y, vMax0.z };//left up
	bColided = bColided || CheckPointInBox(vPoint, vMin1, vMax1);

	return bColided;
}
bool CheckCollision1(const D3DXVECTOR3 &vMin0, D3DXVECTOR3 &vMax0, D3DXVECTOR3 &vMin1, D3DXVECTOR3 &vMax1) {
	return vMin0.x <= vMax1.x && vMax0.x >= vMin1.x &&
		vMin0.y <= vMax1.y && vMax0.y >= vMin1.y && 
		vMin0.z <= vMax1.z && vMax0.z >= vMin1.z;
}
void CAppBoxCollision::OnRender(DWORD fDeltaTime) {
	//collision check
	bool bColided = false;
	D3DXVECTOR3 vMin0 = m_vPos0 + m_vBoundingBoxMin * m_vScale0;
	D3DXVECTOR3 vMax0 = m_vPos0 + m_vBoundingBoxMax * m_vScale0;
	D3DXVECTOR3 vMin1 = m_vPos1 + m_vBoundingBoxMin * m_vScale1;
	D3DXVECTOR3 vMax1 = m_vPos1 + m_vBoundingBoxMax * m_vScale1;
	//check collision
	//bColided = CheckCollision0(vMin0, vMax0, vMin1, vMax1);
	//bColided = bColided || CheckCollision0(vMin1, vMax1, vMin0, vMax0);
	bColided = CheckCollision1(vMin0, vMax0, vMin1, vMax1);
	//render setting
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, !bColided);//라이팅 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//채우기모드 와이어프레임
	//transformation matrix
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	//object0 =====
	//world transformation
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_vRotation.x, m_vRotation.y, m_vRotation.z);
	//draw mesh
	D3DXMatrixScaling(&matScale, m_vScale0, m_vScale0, m_vScale0);
	D3DXMatrixTranslation(&matTranslation, m_vPos0.x, m_vPos0.y, m_vPos0.z);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation*matTranslation));
	m_pMesh->DrawSubset(0);
	//draw bounding box
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pBoundingBoxMesh->DrawSubset(0);
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//object1 ====
	//draw mesh
	D3DXMatrixScaling(&matScale, m_vScale1, m_vScale1, m_vScale1);
	D3DXMatrixTranslation(&matTranslation, m_vPos1.x, m_vPos1.y, m_vPos1.z);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation*matTranslation));
	m_pMesh->DrawSubset(0);
	//draw bounding box
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pBoundingBoxMesh->DrawSubset(0);
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
void CAppBoxCollision::OnRelease() {
	if (m_pMesh) {
		m_pMesh->Release();
	}
	if (m_pBoundingBoxMesh) {
		m_pBoundingBoxMesh->Release();
	}
}