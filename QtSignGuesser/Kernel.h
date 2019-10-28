#ifndef KERNEL_H
#define KERNEL_H


#include "UnaryProcess.h"

class Kernel : public UnaryProcess
{
public:
	Kernel() = delete;
	Kernel(int windowSize);
	~Kernel() = default;


private:


};


#endif // KERNEL