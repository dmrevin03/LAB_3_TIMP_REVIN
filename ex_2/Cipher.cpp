#include  "Cipher.h"
Cipher::Cipher(int key)
{
    this-> k=key;
}
wstring Cipher::CoderCipher(Cipher w, wstring& s)
{
    wstring code;
    s=getValidOpenText(s);
    w.k=getValidKey(w.k,s);
    int h;
    if (s.size()%w.k!=0) {
        h=s.size()/w.k+1;
    } else {
        h=s.size()/w.k;
    }
    wchar_t a[h][w.k];
    int k=0;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w.k; j++) {
            if (k<s.size()) {
                a[i][j]=s[k];
                k++;
            } else a[i][j]=' ';
        }
    }
    for (int i=0; i<w.k; i++) {
        for (int j=0; j<h; j++) {
            code+=a[j][i];
        }
    }
    return code;
}
wstring Cipher::DecoderCipher(Cipher w, wstring& s)
{
    s=getValidOpenText(s);
    w=getValidKey(w.k,s);
    int h;
    if (s.size()%w.k!=0) {
        h=s.size()/w.k+1;
    } else {
        h=s.size()/w.k;
    }
    wchar_t a[h][w.k];
    int k=0;
    for (int i=0; i<w.k; i++) {
        for (int j=0; j<h; j++) {
            a[j][i]=s[k];
            k++;
        }
    }
    wstring decode;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w.k; j++) {
            decode+=a[i][j];
        }
    }
    return decode;
}
inline int Cipher::getValidKey(const int k, const std::wstring & s)
{
    if (k<=0)
        throw cipher_error("Wrong key");
    else if (k>(s.size()/2))
        throw cipher_error("The key is longer than the text length");
    else
        return k;
}
inline std::wstring Cipher::getValidOpenText(const std::wstring & s)
{
    std::wstring tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))                {
                tmp.push_back(toupper(c));
            } else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("The input text is missing");
    return tmp;
}

inline std::wstring Cipher::getValidCipherText(const std::wstring & s)
{
    std::wstring tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c)) {
                tmp.push_back(toupper(c));
            } else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("The output text is missing");
    return tmp;
}
