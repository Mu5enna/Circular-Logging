#include "Circular_Logging.h"

using namespace std;

int main() {
	Circular_Logging cl("variables.json");
	cl.startLogCreation();
	return 0;
}