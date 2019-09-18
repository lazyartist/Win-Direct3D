#pragma once

class CD3DFramework;
__interface IApp {
	void Init(CD3DFramework * pD3DFramework) = 0;
	void Update(unsigned long fDeltaTime) = 0;
	void Render(unsigned long fDeltaTime) = 0;
	void Release() = 0;
};