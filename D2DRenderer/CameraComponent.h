#pragma once

#include "SceneComponent.h"

/*
	카메라는 게임에 따라 카메라의 위치 업데이트방법이 다를수 있으므로 
	상속 재활용할수 있도록 컴포넌트로 만들었다.
*/
class CameraComponent : public SceneComponent
{
public:
	CameraComponent(GameObject* pOwner, const std::string& Name);
	virtual ~CameraComponent();

public:
	int		m_CameraID;
	void SetCameraID(int id) { m_CameraID = id;  }
	int	GetCameraID() { return m_CameraID;  }
	virtual void Update(float DeltaTime) override;
	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};

