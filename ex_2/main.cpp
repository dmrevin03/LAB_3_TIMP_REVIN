#include <UnitTest++/UnitTest++.h>
#include <Cipher.h>
#include <iostream>
#include <locale>
#include <codecvt>



using namespace std;
string wst (int k, wstring s1)
{
    Cipher w(k);
    wstring s=w.CoderCipher(w, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
string wst1 (int k, wstring s1)
{
    Cipher w(k);
    wstring s=w.DecoderCipher(k, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
SUITE (KeyTest)
{
    wstring test = L"INFORMATION";
    int k;
    TEST (ValidKey) {
        CHECK_EQUAL(wst(k=3,test),"IOAONRTNFMI");
    }
    TEST(EmptyKey) {
        CHECK_THROW(wst(k=0,test), cipher_error);
    }
    TEST(NegativeKey) {
        CHECK_THROW(wst(k=-5,test), cipher_error);
    }
    TEST(LargeKey) {
        CHECK_THROW(wst(k=12,test), cipher_error);
    }
    TEST(A_characters_in_the_key_instead_of_numbers) {
        CHECK_THROW(wst(k=12,test), cipher_error);
    }
}
SUITE(EncryptTest)
{
    TEST(ValidText) {
        CHECK_EQUAL(wst(3,L"INFORMATION"),"IOAONRTNFMI");
    }
    TEST(LowText) {
        CHECK_EQUAL(wst(3,L"InFORmatIoN"),"IOAONRTNFMI");
    }
    TEST(SpaceText) {
        CHECK_EQUAL(wst(3,L"INFORM ATION"),"IOAONRTNFMI");
    }
    TEST(EmptyText) {
        CHECK_THROW(wst(3,L" "),cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(wst(3,L"!*>:@<?/,.332"),cipher_error);
    }
    TEST(TextWithNumber) {
        CHECK_EQUAL(wst(3,L"InFOR322matIoN"),"IOAONRTNFMI");
    }
    TEST(TextWithSpaceAndPunct) {
        CHECK_EQUAL(wst(5,L"Good grade for the exam!"),"GROEOARXODTADEHMGFE");
    }
}
SUITE(DecryptText)
{
    TEST(ValidTEXT) {
        CHECK_EQUAL(wst1(3,L"IOAONRTNFMI"),"INFORMATION");
    }
    TEST(LowTEXT) {
        CHECK_EQUAL(wst1(3,L"IoAONrtnFmI"),"INFORMATION");
    }
    TEST(SpaceTEXT) {
        CHECK_EQUAL(wst1(3,L"IOAONR TNFMI"),"INFORMATION");
    }
    TEST(EmptyTEXT) {
        CHECK_THROW(wst1(3,L" "),cipher_error);
    }
    TEST(TextNumberText) {
        CHECK_EQUAL(wst1(3,L"IOAON322RTNFMI"),"INFORMATION");
    }
    TEST(TextSymbolText) {
        CHECK_EQUAL(wst1(3,L"IOAONR?TNFMI"),"INFORMATION");
    }

}

int main()
{
    return UnitTest::RunAllTests();
}
