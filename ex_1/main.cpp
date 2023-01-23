#include <UnitTest++/UnitTest++.h>
#include <modAlphaCipher.h>
#include <iostream>
#include <locale>
#include <codecvt>


using namespace std;
SUITE(KeyTest)
{

    TEST(LargeLetters) {
        modAlphaCipher test(L"СТУДЕНТПГУ");
        CHECK (true);
    }
    TEST(LargeAndSmallLetters) {
        modAlphaCipher test (L"СТУДЕНТпгу");
        CHECK (true);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher test(L""), cipher_error);
    }
    TEST(Key_with_a_space) {
        CHECK_THROW(modAlphaCipher test(L"студент пгу"), cipher_error);
    }
    TEST(Key_with_invalid_characters_number) {
        CHECK_THROW(modAlphaCipher test(L"студент4пгу"), cipher_error);
    }
    TEST(Key_with_invalid_characters_special_character) {
        CHECK_THROW(modAlphaCipher test(L"СТУДЕНТ,пгу"), cipher_error);
    }
}

struct KeyAB_fixture {
    modAlphaCipher * pointer;
    KeyAB_fixture()
    {
        pointer = new modAlphaCipher(L"АВ");
    }
    ~KeyAB_fixture()
    {
        delete pointer;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring open_text = L"ИНСТИТУТ";
        wstring result_correct = L"ИПСФИФУФ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture, SmallLetters) {
        wstring open_text = L"институт";
        wstring result_correct = L"ИПСФИФУФ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture,NumberInText ) {
        wstring open_text = L"УЧИТЕЛЬ11УЧЕНИК";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSpecialSymbol) {
        wstring open_text = L"УЧИТЕЛЬ|УЧЕНИК";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring open_text = L"УЧИТЕЛЬ УЧЕНИК";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }

}
SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring cipher_text = L"ИПСФИФУФ";
        wstring result_correct = L"ИНСТИТУТ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Smallletters) {
        wstring cipher_text = L"ипсфифуф";
        wstring result_correct = L"ИНСТИТУТ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture,LargeAndSmallLetters ) {
        wstring cipher_text = L"ЭкЗАмЕН";
        wstring result_correct = L"ЭИЗЮМГН";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }

    TEST_FIXTURE(KeyAB_fixture, EmptyText) {
        wstring cipher_text = L"";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithNumber) {
        wstring cipher_text = L"УЧИТЕЛЬ11УЧЕНИК";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSymbol) {
        wstring cipher_text = L"ЖЕНА=СУПРУГА";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring cipher_text = L"Хорошая Оценка";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
