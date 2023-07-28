
#include "TestCode.h"


#include "Deligate.h"
#include "MyComponent3.h"
#include "MyComponent4.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "TestFileIO.h"
#include "TestFactory.h"
#include "TestEnumToString.h"

int main()
{
	PlayerCharacter go;
	//Test_CPP_writeBinaryFile();

	//go.Update();
	//go.Render();
		
	const std::type_info& self = typeid(go);
	std::string str = self.name();

	return 0;
}
