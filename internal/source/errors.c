#include <interface.h>

void Handle_Exceptions() {
	int Yield = setjmp();
	if (Yield != 0) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "fatal error %d: %s", Yield, Exception_Text);
		//handle uwu
	}
}