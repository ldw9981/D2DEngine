
#include "TestCode.h"


#include "Deligate.h"
#include "MyComponent3.h"
#include "MyComponent4.h"
#include "GameObject.h"

int main() 
{
	GameObject go;

	go.Update();

	MyComponent3 com3;
	MyComponent4 com4;

	Deligate1<int> delegate;

	delegate.AddCallback(&com3,&MyComponent3::CallbackFunction);


	// Invoke the callbacks
	delegate.InvokeCallbacks(42);


	// Invoke the callbacks again
	delegate.InvokeCallbacks(42);

	return 0;
}
