// base64.cpp -- Base64 encoder/decoder test
// Copyright (C) 2019 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
////////////////////////////////////////////////////////////////////////////

#define _RWSTD_COMPILE_INSTANTIATE
#include "base64.hpp"
#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////////////////

bool do_test(const std::string& original)
{
    std::string encoded = base64_encode(original);
    std::string decoded = base64_decode(encoded);
    if (original == decoded)
        return true;

    std::cout << "FAILURE!" << std::endl;
    std::cout << "  original: '" << original << "'" << std::endl;
    std::cout << "  encoded: '" << encoded << "'" << std::endl;
    std::cout << "  decoded: '" << decoded << "'" << std::endl;
    return false;
}

int main(void)
{
    std::ifstream fin;
    fin.open("base64.hpp", std::ios::in | std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "fin open error" << std::endl;
        return -1;
    }

    std::istreambuf_iterator<char> begin(fin), end;
    std::string str(begin, end);
    fin.close();

    std::string encoded = base64_encode(str);
    std::string decoded = base64_decode(encoded);

    std::ofstream fout;
    fout.open("base64.dat", std::ios::out | std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "fout open error" << std::endl;
        return -2;
    }

    fout << encoded;
    fout.close();

    if (decoded != str)
    {
        std::cout << "mismatch!" << std::endl;
    }

    if (decoded == str &&
        do_test("") &&
        do_test("T") &&
        do_test("TE") &&
        do_test("TES") &&
        do_test("TEST") &&
        do_test("TEST1") &&
        do_test("TEST12") &&
        do_test("TEST123") &&
        do_test("0") &&
        do_test("01") &&
        do_test("012") &&
        do_test("0123") &&
        do_test("01234") &&
        do_test("012345") &&
        do_test("0123456") &&
        do_test("d") &&
        do_test("de") &&
        do_test("dea") &&
        do_test("dead") &&
        do_test("deadb") &&
        do_test("deadbe") &&
        do_test("deadbee") &&
        do_test("deadbeef"))
    {
        std::cout << "success" << std::endl;
    }
    else
    {
        std::cout << "failure" << std::endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////
