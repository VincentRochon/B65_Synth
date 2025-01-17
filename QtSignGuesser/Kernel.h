#ifndef KERNEL_H
#define KERNEL_H


#include "UnaryProcess.h"

class Kernel : public UnaryProcess
{
public:
	Kernel() = default;
	virtual ~Kernel() = default;




private:
	virtual std::vector<float> getKernel() = 0;

};


#endif // KERNEL