
#include "TestCode.h"


#include "Deligate.h"
#include "MyComponent3.h"
#include "MyComponent4.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "TestFileIO.h"

int main()
{
	PlayerCharacter go;
	//Test_C_FileIO_Text();

	go.Update();
	go.Render();
		

	return 0;
}
