// base64-test.cpp -- Base64 encoder/decoder test
// Copyright (C) 2019 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
////////////////////////////////////////////////////////////////////////////

#define _RWSTD_COMPILE_INSTANTIATE
#include "base64.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

////////////////////////////////////////////////////////////////////////////

bool do_test(const std::string& original, size_t line_len = 76)
{
    std::string encoded = base64_encode(original, line_len);
    std::string decoded = base64_decode(encoded);
    if (original == decoded)
        return true;

    std::cout << "FAILURE!" << std::endl;
    std::cout << "  original: '" << original << "'" << std::endl;
    std::cout << "  encoded: '" << encoded << "'" << std::endl;
    std::cout << "  decoded: '" << decoded << "'" << std::endl;
    std::cout << "  line_len: " << line_len << std::endl;
    return false;
}

bool do_test_file(const char *inp_file, const char *out_file)
{
    std::ifstream fin;
    fin.open(inp_file, std::ios::in | std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "fin open error: '" << inp_file << "'" << std::endl;
        return false;
    }

    std::istreambuf_iterator<char> begin(fin), end;
    std::string original(begin, end);
    fin.close();

    std::string encoded = base64_encode(original);
    std::string decoded = base64_decode(encoded);

    std::ofstream fout;
    fout.open(out_file, std::ios::out | std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "fout open error: '" << out_file << "'" << std::endl;
        return false;
    }
    fout << encoded;
    fout.close();

    if (original == decoded)
        return true;

    std::cout << "FAILURE!" << std::endl;
    std::cout << "  original file: '" << inp_file << "'" << std::endl;
    std::cout << "  encoded file: '" << out_file << "'" << std::endl;
    return false;
}

int main(int argc, char **argv)
{
    if (std::strlen(base64_table()) != 64)
    {
        std::cout << "ERROR: The length of base64_table() is not 64." << std::endl;
        return -1;
    }

    if (argc != 2)
    {
        std::cout << "ERROR: Invalid argument." << std::endl;
        return -3;
    }

    std::string exe = argv[1];
    std::string exe_enc = exe + ".enc";

    if (do_test_file(exe.c_str(), exe_enc.c_str()) &&
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
        do_test("\x12") &&
        do_test("\x12\x34") &&
        do_test("\x12\x34\x56") &&
        do_test("\x12\x34\x56\x78") &&
        do_test("\xAB") &&
        do_test("\xAB\xCD") &&
        do_test("\xAB\xCD\xEF") &&
        do_test("d") &&
        do_test("de") &&
        do_test("dea") &&
        do_test("dead") &&
        do_test("deadb") &&
        do_test("deadbe") &&
        do_test("deadbee") &&
        do_test("deadbeef") &&
        do_test("D") &&
        do_test("DE") &&
        do_test("DEA") &&
        do_test("DEAD") &&
        do_test("DEADB") &&
        do_test("DEADBE") &&
        do_test("DEADBEE") &&
        do_test("DEADBEEF") &&
        do_test("!#$%&") &&
        do_test("!#$%&()=~'^|?_\"") &&
        do_test(std::string("A\0" "A\0", 4)) &&
        do_test("0123456789") &&
        do_test("0123456789" "0123456789") &&
        do_test("0123456789" "0123456789" "0123456789") &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789") &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789") &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789") &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789" "0123456789") &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789" "0123456789" "0123456789") &&
        do_test("0123456789", 0) &&
        do_test("0123456789" "0123456789", 0) &&
        do_test("0123456789" "0123456789" "0123456789", 0) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789", 0) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789", 0) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789", 0) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789" "0123456789", 0) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789" "0123456789" "0123456789", 0) &&
        do_test("0123456789", 10) &&
        do_test("0123456789" "0123456789", 10) &&
        do_test("0123456789" "0123456789" "0123456789", 10) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789", 10) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789", 10) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789", 10) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789" "0123456789", 10) &&
        do_test("0123456789" "0123456789" "0123456789" "0123456789"
                "0123456789" "0123456789" "0123456789" "0123456789", 10))
    {
        std::cout << "success" << std::endl << std::flush;
        return 0;
    }
    else
    {
        std::cout << "failure" << std::endl << std::flush;
        return -2;
    }
}

////////////////////////////////////////////////////////////////////////////
