#include <iostream>
#include "Rut/RxMem.h"

int main(int argc, char* argv[])
{
	uint32_t buffer[3] = { 0 };
	Rut::RxMem::Viewer viewer{ buffer };
	viewer.Write<uint32_t>(10);
	viewer.Write<uint32_t>(11);
	viewer.Write<uint32_t>(13);

	viewer.Rewind();

	auto x0 = viewer.Read<uint32_t>();
	auto x1 = viewer.Read<uint32_t>();
	auto x2 = viewer.Read<uint32_t>();

	int a = 0;
}