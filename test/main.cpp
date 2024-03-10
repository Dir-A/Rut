#include <iostream>
#include "Rut/RxMem.h"
#include "Rut/RxCmd.h"


struct MyStruct
{
	uint32_t xx;
};

static void TestView()
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

	uint32_t xxe2[3] = { 31,31,4 };
	view.Write(xxe2);
	view.Rewind();

	uint32_t xxe22[3] = { 0 };
	view >> xxe22;
	view.Rewind();

	Rut::RxMem::Auto memx;
	view.Write(memx);

	int a = 0;
}

static void TestCmd()
{
	const wchar_t* argv[] = { L"1.exe", L"-mode", L"batch", L"-name",L"\"[061215][EX12] 雛鳥の堕ちる音\""};
	Rut::RxCmd::Arg arg;

	arg.AddCmd(L"-name", L"game name in filter json file");
	arg.AddCmd(L"-mode", L"mode: [batch]");

	arg.Load(5, (wchar_t**)argv);
}

int main(int argc, char* argv[])
{
	TestCmd();
}