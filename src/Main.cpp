
#include "ALB.h"

int main(int argc, char** argv) {
	AudioLoopBack ALB_Obj;

	ALB_Obj.ALB_contextAndDeviceInit();
	ALB_Obj.ALB_run();

	return 0;
}