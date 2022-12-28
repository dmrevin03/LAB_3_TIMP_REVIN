#include <UnitTest++/UnitTest++.h>
#include <modAlphaCipher.h>
#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;
struct KeyB_fixture {
	modAlphaCipher * p;
	KeyB_fixture()
	{
		p = new modAlphaCipher(L"Б");
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
		CHECK_EQUAL("АБВАБ", codec.to_bytes(modAlphaCipher(L"АБВ").encrypt(L"ААААА")));
	}
	TEST(LongKey) {
		CHECK_EQUAL("БВГДЕ",codec.to_bytes(modAlphaCipher(L"БВГДЕЁЖЗИЙ").encrypt(L"ААААА")));
	}
	TEST(LowCaseKey) {
		CHECK_EQUAL("БВГБВ",codec.to_bytes(modAlphaCipher(L"бвг").encrypt(L"AAAAA")));
	}
	TEST(DigitsInKey) {
		CHECK_THROW(modAlphaCipher cp(L"Б1"),cipher_error);
	}
	TEST(PunctuationInKey) {
		CHECK_THROW(modAlphaCipher cp(L"Б,В"),cipher_error);
	}
	TEST(WhitespaceInKey) {
		CHECK_THROW(modAlphaCipher cp(L"Б В"),cipher_error);
	}
	TEST(EmptyKey) {
		CHECK_THROW(modAlphaCipher cp(L""),cipher_error);
	}
	TEST(WeakKey) {
		CHECK_THROW(modAlphaCipher cp(L"ААА"),cipher_error);
	}
}
SUITE(EncryptTest)
{
	TEST_FIXTURE(KeyB_fixture, UpCaseString) {
		CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ",
		            codec.to_bytes(p->encrypt(L"БЫСТРАЯБУРАЯЛИСАПЕРЕПРЫГИВАЕТЧЕРЕЗЛЕНИВУЮСОБАКУ")));
	}
	TEST_FIXTURE(KeyB_fixture, LowCaseString) {
		CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ",
		            codec.to_bytes(p->encrypt(L"быстраябураялисаперепрыгиваетчерезленивуюсобаку")));
	}
	TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
		CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ",
		            codec.to_bytes(p->encrypt(L"БЫСТРАЯ БУРАЯ ЛИСА ПЕРЕПРЫГИВАЕТ ЧЕРЕЗ ЛЕНИВУЮ СОБАКУ")));
	}
	TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
		CHECK_EQUAL("ТОПГЬНДПЕПН", codec.to_bytes(p->encrypt(L"С Новым 2077 годом!!!")));
	}
	TEST_FIXTURE(KeyB_fixture, EmptyString) {
		CHECK_THROW(p->encrypt(L""),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
		CHECK_THROW(p->encrypt(L"1234+8765=9999"),cipher_error);
	}
	TEST(MaxShiftKey) {
		CHECK_EQUAL("БЫСТРАЯБУРАЯЛИСАПЕРЕПРЫГИВАЕТЧЕРЕЗЛЕНИВУЮСОБАКУ",
		            codec.to_bytes(modAlphaCipher(L"Я").encrypt(L"ВЬТУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ")));
	}
}
SUITE(DecryptText)
{
	TEST_FIXTURE(KeyB_fixture, UpCaseString) {
		CHECK_EQUAL("БЫСТРАЯБУРАЯЛИСАПЕРЕПРЫГИВАЕТЧЕРЕЗЛЕНИВУЮСОБАКУ",
		codec.to_bytes(p->decrypt(L"ВЬТУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ")));
	}
	TEST_FIXTURE(KeyB_fixture, LowCaseString) {
		CHECK_THROW(p->decrypt(L"вьтУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
		CHECK_THROW(p->decrypt(L"ВЬТУСБА ВФСБА МЙТБ РЁСЁРСЬДЙГБЁУ ШЁСЁИ МЁОЙГФЯ ТПВБЛФ"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, DigitsString) {
		CHECK_THROW(p->decrypt(L"ТОПГЬН2077ДПЕПН"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, PunctString) {
		CHECK_THROW(p->decrypt(L"ШАЬЬЗб,ЧЗЫЬУ"),cipher_error);
	}
	TEST_FIXTURE(KeyB_fixture, EmptyString) {
		CHECK_THROW(p->decrypt(L""),cipher_error);
	}
	TEST(MaxShiftKey) {
		CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБРЁСЁРСЬДЙГБЁУШЁСЁИМЁОЙГФЯТПВБЛФ",
		            codec.to_bytes(modAlphaCipher(L"Я").decrypt(L"БЫСТРАЯБУРАЯЛИСАПЕРЕПРЫГИВАЕТЧЕРЕЗЛЕНИВУЮСОБАКУ")));
	}
}
int main(int argc, char **argv)
{
	locale loc("ru_RU.UTF-8");
	locale::global(loc);
	return UnitTest::RunAllTests();
}
