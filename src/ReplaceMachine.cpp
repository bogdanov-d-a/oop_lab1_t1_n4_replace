#include "stdafx.h"
#include "ReplaceMachine.h"

using namespace std;

CReplaceMachine::CReplaceMachine(const char findString[], const char replaceString[], FILE *outputFile):
	m_findString(findString),
	m_findStringLength(strlen(findString)),
	m_replaceString(replaceString),
	m_replaceStringLength(strlen(replaceString)),
	m_outputFile(outputFile),
	m_workComplete(false),
	m_absorbedAmount(0)
{
	assert(m_findStringLength > 0);
}

CReplaceMachine::~CReplaceMachine()
{
	if (!m_workComplete)
	{
		EndDataStream();
	}
}

void CReplaceMachine::SendChar(char c)
{
	assert(!m_workComplete);
	assert(m_absorbedAmount < m_findStringLength);

	FlushUnneededBufferPart(c);

	if (FitsToBuffer(c))
	{
		const bool bufferWillNowMatchFindString = (m_absorbedAmount == m_findStringLength - 1);

		if (bufferWillNowMatchFindString)
		{
			fwrite(m_replaceString, sizeof(char), m_replaceStringLength, m_outputFile);
			m_absorbedAmount = 0;
		}
		else
		{
			++m_absorbedAmount;
		}
	}
	else
	{
		assert(m_absorbedAmount == 0);
		fputc(c, m_outputFile);
	}
}

void CReplaceMachine::EndDataStream()
{
	assert(!m_workComplete);
	fwrite(m_findString, sizeof(char), m_absorbedAmount, m_outputFile);
	m_workComplete = true;
}

void CReplaceMachine::FlushShortestBufferPrefix()
{
	assert(!BufferIsEmpty());
	const size_t longestSuffixPart = FindLongestSuffixPart(m_findString, m_absorbedAmount, m_findString, m_findStringLength);
	fwrite(m_findString, sizeof(char), m_absorbedAmount - longestSuffixPart, m_outputFile);
	m_absorbedAmount = longestSuffixPart;
}

size_t CReplaceMachine::FindLongestSuffixPart(const char str[], size_t strLength, const char suffix[], size_t suffixLength)
{
	assert(strLength > 0);
	assert(suffixLength > 0);

	for (size_t suffixPartLength = min(strLength, suffixLength) - 1; suffixPartLength > 0; --suffixPartLength)
	{
		if (IsSuffix(str, strLength, suffix, suffixPartLength))
		{
			return suffixPartLength;
		}
	}

	return 0;
}

bool CReplaceMachine::IsSuffix(const char str[], size_t strLength, const char suffix[], size_t suffixLength)
{
	if (suffixLength > strLength)
	{
		return false;
	}

	if (suffixLength == 0)
	{
		return true;
	}

	const size_t suffixStart = strLength - suffixLength;
	return (memcmp(str + sizeof(char) * suffixStart, suffix, suffixLength) == 0);
}

bool CReplaceMachine::FitsToBuffer(char c) const
{
	assert(m_absorbedAmount < m_findStringLength);
	return (c == m_findString[m_absorbedAmount]);
}

bool CReplaceMachine::BufferIsEmpty() const
{
	return (m_absorbedAmount == 0);
}

void CReplaceMachine::FlushUnneededBufferPart(char newChar)
{
	while (!BufferIsEmpty() && !FitsToBuffer(newChar))
	{
		FlushShortestBufferPrefix();
	}
}
