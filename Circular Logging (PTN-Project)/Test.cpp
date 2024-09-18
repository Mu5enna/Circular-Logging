#include "Circular_Logging.h"

using namespace std;

int main() {
	Circular_Logging cl("a.exe");
	cl.startLogCreation();
	return 0;
}