#include <iostream>
#include "RxJson.h"

int main(int argc, char* argv[])
{
	Rut::RxJson::JValue json = Rut::RxJson::Parser{}.Load(L"1.json");
}