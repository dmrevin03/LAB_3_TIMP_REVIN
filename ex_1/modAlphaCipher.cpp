#include  "modAlphaCipher.h"

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(skey));
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for(auto c:s) {
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
inline std::wstring modAlphaCipher::getValidKey(const std::wstring & s)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    if (s.size()==0)
        throw cipher_error(string("Вы ввели пустой текст"));
    wstring wst = s;
    for (size_t i = 0; i < wst.size(); i++) {
        if (iswalpha(wst[i])==0) {
            throw cipher_error(string("В вашем тексте присутствуют недопустимые символы"));
            break;
        }
        if (iswlower(wst[i]))
            wst[i] = towupper(wst[i]);
    }
    return wst;
}


inline wstring modAlphaCipher::getValidText(const wstring & s)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    if (s.size()==0)
        throw cipher_error(string("Вы ввели пустой текст"));
    wstring wst = s;
    for (size_t i = 0; i < wst.size(); i++) {
        if (iswalpha(wst[i])==0) {
            throw cipher_error(string("В вашем тексте присутствуют недопустимые символы"));
            break;
        }
        if (iswlower(wst[i]))
            wst[i] = towupper(wst[i]);
    }
    return wst;
}
