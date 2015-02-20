#include "stdafx.h"
#include "ReplaceMachine.h"

CReplaceMachine::CReplaceMachine(const char * findString, const char * replaceString, FILE * outputFile)
{
	m_findString = findString;
	m_findStringLength = strlen(findString);
	assert(m_findStringLength > 0);

	m_replaceString = replaceString;
	m_replaceStringLength = strlen(replaceString);

	m_outputFile = outputFile;
	m_absorbedAmount = 0;
}

void CReplaceMachine::SendChar(char c)
{
	assert(m_absorbedAmount < m_findStringLength);

	if (c != m_findString[m_absorbedAmount])
	{
		WriteAbsorbedData();
	}

	if (c == m_findString[m_absorbedAmount])
	{
		if (m_absorbedAmount == m_findStringLength - 1)
		{
			fwrite(m_replaceString, sizeof(char), m_replaceStringLength, m_outputFile);
			m_absorbedAmount = 0;
		}
		else
		{
			m_absorbedAmount++;
		}
	}
	else
	{
		fputc(c, m_outputFile);
	}
}

void CReplaceMachine::WriteAbsorbedData()
{
	fwrite(m_findString, sizeof(char), m_absorbedAmount, m_outputFile);
	m_absorbedAmount = 0;
}
