#pragma once

class CReplaceMachine
{
public:
	CReplaceMachine(const char *, const char *, FILE *);
	void SendChar(char);
	void WriteAbsorbedData();

protected:
	const char * m_findString;
	size_t m_findStringLength;

	const char * m_replaceString;
	size_t m_replaceStringLength;

	FILE * m_outputFile;
	uint32_t m_absorbedAmount;
};
