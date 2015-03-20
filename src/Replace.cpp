// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReplaceMachine.h"

int DoReplace(const char inputFileName[], const char outputFileName[],
	const char searchString[], const char replaceString[])
{
	int result = 0;

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

				replaceMachine.EndDataStream();
				fclose(outputFile);
			}
			else
			{
				puts("Output file open error");
				result = 2;
			}

			fclose(inputFile);
		}
		else
		{
			puts("Input file open error");
			result = 1;
		}
	}
	else
	{
		if (CopyFile(inputFileName, outputFileName, false) == 0)
		{
			puts("Copy file error");
			result = 3;
		}
	}

	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 5)
	{
		return DoReplace(argv[1], argv[2], argv[3], argv[4]);
	}
	else
	{
		assert(argc > 0);
		printf("Usage: %s <input file> <output file> <search string> <replace string>\n", argv[0]);
		return 4;
	}
}
