#include <iostream>
#include <pbc/pbc.h>
#include <string>

using namespace std;

class ABEContext {
public:
    pairing_t pairing;
    element_t g, master_secret;

    ABEContext() {
        // Type A pairing parameters (symmetric curve, good for basic tests)
        char param[1024];
        FILE* fp = fopen("a.param", "r");
        size_t count = fread(param, 1, 1024, fp);
        fclose(fp);

        if (pairing_init_set_buf(pairing, param, count)) {
            throw runtime_error("Pairing init failed.");
        }

        element_init_G1(g, pairing);
        element_init_Zr(master_secret, pairing);

        element_random(g);
        element_random(master_secret);
    }

    void keygen(const string& attr, element_t& pubKey, element_t& privKey) {
        element_init_G1(pubKey, pairing);
        element_init_G1(privKey, pairing);
        element_pow_zn(pubKey, g, master_secret);
        element_pow_zn(privKey, g, master_secret);  // Normally hashed with attr
    }

    void encrypt(const string& policy, const string& message, element_t& c1, element_t& c2) {
        element_t r;
        element_init_Zr(r, pairing);
        element_random(r);

        element_init_G1(c1, pairing);
        element_init_GT(c2, pairing);

        element_pow_zn(c1, g, r);
        element_t temp;
        element_init_GT(temp, pairing);
        pairing_apply(temp, g, g, pairing);
        element_pow_zn(c2, temp, r);
        // For full CP-ABE: embed the message using c2 * M
    }

    void decrypt(const element_t& c1, const element_t& c2, const element_t& privKey, string& out) {
        element_t result;
        element_init_GT(result, pairing);
        pairing_apply(result, c1, privKey, pairing);
        // Normally compare result to c2 or use to recover message
        cout << "[Mock Decryption] Pairing result: ";
        element_printf("%B\n", result);
        out = "[Decrypted] (mock)";
    }
};
