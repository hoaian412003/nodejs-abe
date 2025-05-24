// abe.h
#pragma once
#include <string>

namespace abe {
    void setup();
    std::string encrypt(const std::string& policy, const std::string& plaintext);
    std::string decrypt(const std::string& attributes, const std::string& ciphertext);
}

