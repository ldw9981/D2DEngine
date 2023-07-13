#include "AnimRenderer.h"
#include <iostream>

void AnimRenderer::Render()
{	
	int a = GetWorldTransform();
	std::cout << a << "\n";
}

void AnimRenderer::Update()
{
	std::cout << "AnimRenderer Update\n";
}
