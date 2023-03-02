#include <UnitTest++/UnitTest++.h>
#include <PerestanCipher.h>
#include <iostream>
#include <locale>
#include <codecvt>



using namespace std;
string wst (int k, wstring s1)
{
    PerestanCipher w(k);
    wstring s=w.CoderCipher(w, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
string wst1 (int k, wstring s1)
{
    PerestanCipher w(k);
    wstring s=w.DecoderCipher(k, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
SUITE (KeyTest)
{
    wstring test = L"PROGRAMMIROVANIE";
    int k;
    TEST (ValidKey) {
        CHECK_EQUAL(wst(k=4,test),"PRIARARNOMOIGMVE");
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
        CHECK_EQUAL(wst(4,L"PROGRAMMIROVANIE"),"PRIARARNOMOIGMVE");
    }
    TEST(LowText) {
        CHECK_EQUAL(wst(4,L"PRograMmiroVANie"),"PRIARARNOMOIGMVE");
    }
    TEST(SpaceText) {
        CHECK_EQUAL(wst(4,L"PROGRAM MIROVANIE"),"PRIARARNOMOIGMVE");
    }
    TEST(EmptyText) {
        CHECK_THROW(wst(4,L" "),cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(wst(4,L"!*><?/,.123"),cipher_error);
    }
    TEST(TextWithNumber) {
        CHECK_EQUAL(wst(4,L"PRograM123miroVANie"),"PRIARARNOMOIGMVE");
    }
    TEST(TextWithSpaceAndPunct) {
        CHECK_EQUAL(wst(6,L"The programmer walks!"),"TGRHRWEAAPMLRMKOES");
    }
}
SUITE(DecryptText)
{
    TEST(ValidTEXT) {
        CHECK_EQUAL(wst1(4,L"PRIARARNOMOIGMVE"),"PROGRAMMIROVANIE");
    }
    TEST(LowTEXT) {
        CHECK_EQUAL(wst1(4,L"PriaRARNomoIGMve"),"PROGRAMMIROVANIE");
    }
    TEST(SpaceTEXT) {
        CHECK_EQUAL(wst1(4,L"PRIARARN OMOIGMVE"),"PROGRAMMIROVANIE");
    }
    TEST(EmptyTEXT) {
        CHECK_THROW(wst1(4,L" "),cipher_error);
    }
    TEST(TextNumberText) {
        CHECK_EQUAL(wst1(4,L"PRIARARN123OMOIGMVE"),"PROGRAMMIROVANIE");
    }
    TEST(TextSymbolText) {
        CHECK_EQUAL(wst1(4,L"PRIARARN!!!OMOIGMVE"),"PROGRAMMIROVANIE");
    }

}

int main()
{
    return UnitTest::RunAllTests();
}
