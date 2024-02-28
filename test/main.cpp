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
	auto x3 = viewer.Read< uint32_t>();
	viewer.Rewind();

	viewer << 11 << 12 << 13;
	viewer.Rewind();

	auto t0 = 0;
	auto t1 = 0;
	auto t2 = 0;
	viewer >> t0 >> t1 >> t2;
	viewer.Rewind();

	std::string stx = "123";
	viewer.Write(stx.data(),stx.size() + 1);

	int a = 0;
}