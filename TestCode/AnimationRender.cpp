#include "AnimationRender.h"
#include <iostream>

void AnimationRender::Render()
{	
	int a = GetWorldTransform();
	std::cout << "AnimRenderer Render\n";
}

void AnimationRender::Update(float DeltaTime)
{
	std::cout << "AnimRenderer Update\n";
}
