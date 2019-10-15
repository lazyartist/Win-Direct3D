#include "stdafx.h"
#include "CAppSphereCollision.h"

CAppSphereCollision::CAppSphereCollision() {
}
CAppSphereCollision::~CAppSphereCollision() {
}
void CAppSphereCollision::OnInit() {
	pD3DFramework->vCameraEye = { 0, 0, -10 };
	D3DXCreateSphere(pD3DFramework->pD3DDevice, 1, 10, 10, &pSphereMesh, nullptr);

	
}
void CAppSphereCollision::OnUpdate(DWORD fDeltaTime) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		sShpere0.vPosition.x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		sShpere0.vPosition.x += 0.1f;
	}
}
void CAppSphereCollision::OnRender(DWORD fDeltaTime) {
	//메시에서 경계구를 계산해낼 경우 D3DXComputeBoundingSphere()를 사용한다.
	D3DXVECTOR3 vCenter;
	float fRadius;
	D3DXVECTOR3 *pVertices;
	pSphereMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVertices);
	pSphereMesh->UnlockVertexBuffer();
	D3DXComputeBoundingSphere(pVertices, pSphereMesh->GetNumVertices(),
		pSphereMesh->GetNumBytesPerVertex()/*or D3DXGetFVFVertexSize()*/,
		&vCenter, &fRadius);

	//collision check
	bool bColided = false;
	float fDistance = D3DXVec3Length(&(sShpere0.vPosition - sShpere1.vPosition));
	bColided = fDistance <= (sShpere0.fRadius + sShpere1.fRadius);

	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_LIGHTING, bColided);//라이팅 설정
	pD3DFramework->pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//채우기모드 와이어프레임

	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	//draw mesh
	D3DXMatrixScaling(&matScale, fRadius, fRadius, fRadius);
	D3DXMatrixRotationYawPitchRoll(&matRotation, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matTranslation, vCenter.x, vCenter.y, vCenter.z);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation*matTranslation));
	pSphereMesh->DrawSubset(0);
	//draw sphere0
	D3DXMatrixScaling(&matScale, sShpere0.fRadius, sShpere0.fRadius, sShpere0.fRadius);
	D3DXMatrixTranslation(&matRotation, sShpere0.vPosition.x, sShpere0.vPosition.y, sShpere0.vPosition.z);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation));
	pSphereMesh->DrawSubset(0);
	//draw sphere1
	D3DXMatrixScaling(&matScale, sShpere1.fRadius, sShpere1.fRadius, sShpere1.fRadius);
	D3DXMatrixTranslation(&matRotation, sShpere1.vPosition.x, sShpere1.vPosition.y, sShpere1.vPosition.z);
	pD3DFramework->pD3DDevice->SetTransform(D3DTS_WORLD, &(matScale*matRotation));
	pSphereMesh->DrawSubset(0);
}
void CAppSphereCollision::OnRelease() {
	if (true) {
		pSphereMesh->Release();
	}
}