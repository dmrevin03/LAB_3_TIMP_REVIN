#include <Cipher.h>
Cipher::Cipher(const std::wstring & ws_key)
{
	std::wstring tmp(ws_key);
	columns = getValidKey(tmp);
}
void Cipher::set_key(std::wstring & ws_key)
{
	columns = getValidKey(ws_key);
}
void Cipher::set_tableform(const std::wstring& open_text)
{
	len_text = open_text.size();
	if (len_text>columns) {
		rows = len_text/columns;
		if (len_text%columns >0) rows+=1;
	} else {
		rows = 1;
	}
}
std::wstring Cipher::encrypt(const std::wstring& open_text)
{
	std::wstring tmp(open_text);
	tmp = getValidOpenText(tmp);
	set_tableform(tmp);
	std::wstring table_chiper[rows][columns];
	int nums_text = 0;
	for (int y=0; y<rows; y++) {
		for (int x=0; x<columns; x++) {
			if (nums_text < len_text) {
				table_chiper[y][x] = tmp[nums_text];
			} else {
				table_chiper[y][x] = L"-";
			}
			nums_text++;
		}
	}
	std::wstring encrypt_text;
	for (int x=columns-1; x>=0; x--) {
		for (int y=0; y<rows; y++) {
			encrypt_text+=table_chiper[y][x];
		}
	}
	return encrypt_text;
}
std::wstring Cipher::decrypt(const std::wstring& cipher_text)
{
	set_tableform(getValidCipherText(cipher_text));
	std::wstring table_chiper[rows][columns];
	int nums_text = 0;
	for (int x=columns-1; x>=0; x--) {
		for (int y=0; y<rows; y++) {
			table_chiper[y][x] = cipher_text[nums_text];
			nums_text++;
		}
	}
	std::wstring decrypt_text;
	for (int y=0; y<rows; y++) {
		for (int x=0; x<columns; x++) {
			if (table_chiper[y][x] != L"-")
				decrypt_text+=table_chiper[y][x];
		}
	}
	return decrypt_text;
}
inline int Cipher::getValidKey(std::wstring & ws_key)
{
	if (ws_key.empty())
		throw cipher_error("Empty key");
	std::string s_key = codec.to_bytes(ws_key);
	for (auto & c:ws_key) {
		if (!iswdigit(c)) {
			throw cipher_error(std::string("Invalid key: ") + s_key);
		}
	}
	int key = std::stoi(ws_key);
	if (key<=0) {
		throw cipher_error(std::string("Key must be greater than 0"));
	}
	return key;
}
inline std::wstring Cipher::getValidOpenText(const std::wstring & ws_open_text)
{
	std::wstring tmp;
	for (auto c:ws_open_text) {
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
inline std::wstring Cipher::getValidCipherText(const std::wstring & ws_cipher_text)
{
	if (ws_cipher_text.empty())
		throw cipher_error("Empty cipher text");

	for (auto c:ws_cipher_text) {
		if (!iswupper(c)) {
			if (c!=L'-') {
				throw cipher_error(std::string("Invalid cipher text"));
			}
		}
	}
	return ws_cipher_text;
}
