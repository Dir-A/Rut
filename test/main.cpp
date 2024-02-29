#include <iostream>
#include "Rut/RxMem.h"


struct MyStruct
{
	uint32_t xx;
};

void ViewTest(const Rut::RxMem::View& rfView)
{
	rfView.Write<uint32_t>(10);
	rfView.Write<uint32_t>(11);
	rfView.Write<uint32_t>(13);
	rfView.Rewind();

	auto x0 = rfView.Read<uint32_t>();
	auto x1 = rfView.Read<uint32_t>();
	auto x3 = rfView.Read< uint32_t>();
	rfView.Rewind();
}

int main(int argc, char* argv[])
{
	uint32_t buffer[3] = { 0 };
	Rut::RxMem::View view{ buffer };

	view.Write<uint32_t>(10);
	view.Write<uint32_t>(11);
	view.Write<uint32_t>(13);
	view.Rewind();

	auto x0 = view.Read<uint32_t>();
	auto x1 = view.Read<uint32_t>();
	auto x3 = view.Read< uint32_t>();
	view.Rewind();

	view << 11 << 12 << 13;
	view.Rewind();

	auto t0 = 0;
	auto t1 = 0;
	auto t2 = 0;
	view >> t0 >> t1 >> t2;
	view.Rewind();

	std::string stx = "123";
	MyStruct my = { 102 };
	uint32_t xxe2[3] = { 31,31,4 };
	view.Write(xxe2);
	view.Rewind();

	Rut::RxMem::Auto memx;
	view.Write(memx);

	int a = 0;
}