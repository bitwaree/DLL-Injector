//This file contains all the structs that is needed to import/export the files
//Written by @YT/bitware32

#pragma once

#include <stdint.h>

struct FileData
{
	uint32_t magic;
	uint16_t strTitle_len;
	uint16_t DllFile_len;
	//unsigned char sp1 = 0;
	char strTitle[2048];
	//unsigned char sp2 = 0;
	char DllFile[2048];
	//unsigned char sp3 = 0;
};

#define MagicData 0x494E4A43
