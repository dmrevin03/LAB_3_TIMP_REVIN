#include <UnitTest++/UnitTest++.h>
#include <Cipher.h>
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;
struct KeyB_fixture {
	Cipher * p;
	KeyB_fixture()
	{
		p = new Cipher(L"4");
	}
	~KeyB_fixture()
	{
		delete p;
	}
};
wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
SUITE(KeyTest)
{
	TEST(ValidKey) {
		CHECK_EQUAL("Б-О-Б-АА", codec.to_bytes(Cipher(L"4").encrypt(L"АБОБА")));
	}
	TEST(LongKey) {
		CHECK_EQUAL("-АБОБА",codec.to_bytes(Cipher(L"6").encrypt(L"АБОБА")));
	}
	TEST(NegativeKey) {
		CHECK_THROW(Cipher cp(L"-4"),cipher_error);
	}
	TEST(PunctuationInKey) {
		CHECK_THROW(Cipher cp(L"Б,В"),cipher_error);
	}
	TEST(WhitespaceInKey) {
		CHECK_THROW(Cipher cp(L"1 1"),cipher_error);
	}
	TEST(EmptyKey) {
		CHECK_THROW(Cipher cp(L""),cipher_error);
	}
	TEST(AlphaAndPunctuationInKey) {
		CHECK_THROW(Cipher cp(L"ДЭБ4!!!"),cipher_error);
	}
}
SUITE(EncryptTest)
{
	TEST_FIXTURE(KeyB_fixture, UpCaseString) {
		CHECK_EQUAL("Б-О-Б-АА",
		            codec.to_bytes(p->encrypt(L"АБОБА")));
	}
	TEST_FIXTURE(KeyB_fixture, LowCaseString) {
		CHECK_EQUAL("Б-О-Б-АА",
		            codec.to_bytes(p->encrypt(L"абоба")));
	}
	TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
		CHECK_EQUAL("Б-О-Б-АА",
		            codec.to_bytes(p->encrypt(L"А!Б О Б,А")));
	}
	TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
		CHECK_EQUAL("Б-О-Б-АА", codec.to_bytes(p->encrypt(L"АБ11О3БА")));
	}
	TEST_FIXTURE(KeyB_fixture, EmptyString) {
		CHECK_THROW(p->encrypt(L""),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
		CHECK_THROW(p->encrypt(L"1234+8765=9999"),cipher_error);
	}
}
SUITE(DecryptText)
{
	TEST_FIXTURE(KeyB_fixture, UpCaseString) {
		CHECK_EQUAL("АБОБА",
		            codec.to_bytes(p->decrypt(L"Б-О-Б-АА")));
	}
	TEST_FIXTURE(KeyB_fixture, LowCaseString) {
		CHECK_THROW(p->decrypt(L"Б-О-б-АА"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
		CHECK_THROW(p->decrypt(L"Б-О-Б -АА"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, DigitsString) {
		CHECK_THROW(p->decrypt(L"Б-23О-Б-АА"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, PunctString) {
		CHECK_THROW(p->decrypt(L"Б-О,-Б-А,А"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, EmptyString) {
		CHECK_THROW(p->decrypt(L""),cipher_error);
	}
}
int main(int argc, char **argv)
{
	locale loc("ru_RU.UTF-8");
	locale::global(loc);
	return UnitTest::RunAllTests();
}
