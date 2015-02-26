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

	while (m_absorbedAmount != 0 && c != m_findString[m_absorbedAmount])
	{
		PushBuffer();
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
		assert(m_absorbedAmount == 0);
		fputc(c, m_outputFile);
	}
}

void CReplaceMachine::WriteAbsorbedData()
{
	fwrite(m_findString, sizeof(char), m_absorbedAmount, m_outputFile);
	m_absorbedAmount = 0;
}

void CReplaceMachine::PushBuffer()
{
	assert(m_absorbedAmount != 0);

	for (uint32_t delAmount = 1; delAmount <= m_absorbedAmount; ++delAmount)
	{
		if
			(
				m_absorbedAmount == delAmount ||
				memcmp
				(
					m_findString,
					m_findString + sizeof(char) * delAmount,
					sizeof(char) * (m_absorbedAmount - delAmount)
				) == 0
			)
		{
			fwrite(m_findString, sizeof(char), delAmount, m_outputFile);
			m_absorbedAmount -= delAmount;
			return;
		}
	}
}
