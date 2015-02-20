// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReplaceMachine.h"

void DoReplace(const char * const inputFileName, const char * const outputFileName,
	const char * const searchString, const char * const replaceString)
{
	if (searchString[0] != '\0')
	{
		FILE * inputFile;

		if (fopen_s(&inputFile, inputFileName, "r") == 0)
		{
			FILE * outputFile;

			if (fopen_s(&outputFile, outputFileName, "w") == 0)
			{
				CReplaceMachine replaceMachine(searchString, replaceString, outputFile);

				int tmpChar;
				while ((tmpChar = fgetc(inputFile)) != EOF)
				{
					replaceMachine.SendChar(tmpChar);
				}

				replaceMachine.WriteAbsorbedData();
				fclose(outputFile);
			}
			else
			{
				puts("Output file open error");
			}

			fclose(inputFile);
		}
		else
		{
			puts("Input file open error");
		}
	}
	else
	{
		CopyFile(inputFileName, outputFileName,	false);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 5)
	{
		DoReplace(argv[1], argv[2], argv[3], argv[4]);
	}
	else
	{
		assert(argc > 0);
		printf("Usage: %s <input file> <output file> <search string> <replace string>\n", argv[0]);
	}

	return 0;
}
