#pragma once

class CReplaceMachine
{
public:
	CReplaceMachine(const char * findString, const char * replaceString, FILE * outputFile);
	void SendChar(char c);
	void WriteAbsorbedData();

protected:
	const char * m_findString;
	size_t m_findStringLength;

	const char * m_replaceString;
	size_t m_replaceStringLength;

	FILE * m_outputFile;
	uint32_t m_absorbedAmount;

	void PushBuffer();
};
