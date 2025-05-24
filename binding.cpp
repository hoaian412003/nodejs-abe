#include <napi.h>
#include "abe.h"

Napi::String Encrypt(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string policy = info[0].As<Napi::String>().Utf8Value();
    std::string plaintext = info[1].As<Napi::String>().Utf8Value();
    std::string ciphertext = abe::encrypt(policy, plaintext);
    return Napi::String::New(env, ciphertext);
}

Napi::String Decrypt(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string attributes = info[0].As<Napi::String>().Utf8Value();
    std::string ciphertext = info[1].As<Napi::String>().Utf8Value();
    std::string plaintext = abe::decrypt(attributes, ciphertext);
    return Napi::String::New(env, plaintext);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("encrypt", Napi::Function::New(env, Encrypt));
    exports.Set("decrypt", Napi::Function::New(env, Decrypt));
    return exports;
}

NODE_API_MODULE(abe, Init)

