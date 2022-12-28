#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <locale>
#include <iostream>
class Cipher
{
private:
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
	int columns, rows, len_text;
public:
	Cipher()=delete;
	Cipher(const std::wstring & ws_key);
	std::wstring encrypt(const std::wstring& ws_open_text);
	std::wstring decrypt(const std::wstring& ws_cipher_text);
	void set_tableform(const std::wstring& ws_text);
	void set_key(std::wstring & ws_key);
	int getValidKey(std::wstring& ws_key);
	std::wstring getValidOpenText(const std::wstring & ws_open_text);
	std::wstring getValidCipherText(const std::wstring & ws_cipher_text);
};

class cipher_error: public std::invalid_argument
{
public:
	explicit cipher_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};
