#include "abe.h"
#include <unordered_set>
#include <sstream>
#include <openabe/openabe.h>

using namespace oabe;

namespace abe {
  OpenABECtx* ctx;

  void setup() {
      // In a real implementation, generate master keys
      ctx = OpenABECtx::Init();
      return ctx;
  }

  std::string encrypt(const std::string& policy, const std::string& plaintext) {
      // Just concatenate for illustration: [policy]::[plaintext]
      return policy + "::" + plaintext;
  }

  std::string decrypt(const std::string& attributes, const std::string& ciphertext) {
      auto sep = ciphertext.find("::");
      if (sep == std::string::npos) return "";

      std::string policy = ciphertext.substr(0, sep);
      std::string plaintext = ciphertext.substr(sep + 2);

      // Split attributes and policy to compare
      std::istringstream attrStream(attributes), policyStream(policy);
      std::unordered_set<std::string> attrSet;
      std::string token;

      while (std::getline(attrStream, token, ',')) attrSet.insert(token);

      while (std::getline(policyStream, token, ',')) {
          if (attrSet.find(token) == attrSet.end()) return "";
      }

      return plaintext;
  }
}

