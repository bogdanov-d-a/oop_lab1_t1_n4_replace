#pragma once

class CReplaceMachine
{
public:
	CReplaceMachine(const char findString[], const char replaceString[], FILE *outputFile);
	~CReplaceMachine();
	void SendChar(char c);
	void EndDataStream();

private:
	const char *m_findString;
	size_t m_findStringLength;

	const char *m_replaceString;
	size_t m_replaceStringLength;

	FILE *m_outputFile;
	bool m_workComplete;
	size_t m_absorbedAmount;

	void FlushShortestBufferPrefix();
	void FlushUnneededBufferPart(char newChar);
	bool FitsToBuffer(char c) const;
	bool BufferIsEmpty() const;
	static size_t FindLongestSuffixPart(const char str[], size_t strLength, const char suffix[], size_t suffixLength);
	static bool IsSuffix(const char str[], size_t strLength, const char suffix[], size_t suffixLength);
};
