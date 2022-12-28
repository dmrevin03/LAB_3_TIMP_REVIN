#include <modAlphaCipher.h>
modAlphaCipher::modAlphaCipher(
    const std::wstring& wskey)
{
	for (unsigned i=0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	key = convert(getValidKey(wskey));
	int n = 0;
	for (auto e:key) {
		if (e==0)
			n++;
	}
	if (2*n > key.size())
		throw cipher_error("WeakKey");
}
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
	std::vector<int> work = convert(getValidOpenText(open_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
	std::vector<int> work = convert(getValidCipherText(cipher_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const std::wstring& ws)
{
	std::vector<int> result;
	for(auto c:ws) {
		result.push_back(alphaNum[c]);
	}
	return result;
}
inline std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
	std::wstring result;
	for(auto i:v) {
		result.push_back(numAlpha[i]);
	}
	return result;
}
inline std::wstring modAlphaCipher::getValidKey(const std::wstring & ws)
{
	if (ws.empty())
		throw cipher_error("Empty key");
	std::wstring tmp(ws);
	std::string s = codec.to_bytes(ws);
	int num = 0;
	for (auto & c:tmp) {
		if (!iswalpha(c)) {
			throw cipher_error(std::string("Invalid key ") + s);
		}
		if (iswlower(c))
			c = towupper(c);
	}

	return tmp;
}
inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring & ws)
{
	std::wstring tmp;
	for (auto c:ws) {
		if (iswalpha(c)) {
			if (iswlower(c))
				tmp.push_back(towupper(c));
			else
				tmp.push_back(c);
		}
	}
	if (tmp.empty())
		throw cipher_error("Empty open text");
	return tmp;
}
inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring & ws)
{
	if (ws.empty())
		throw cipher_error("Empty cipher text");
	for (auto c:ws) {
		std::string s = codec.to_bytes(ws);
		if (!iswupper(c))
			throw cipher_error(std::string("Invalid cipher text ")+s);
	}
	return ws;
}
