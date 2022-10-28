#include "valueConverter.hpp"

#include <iostream>

static Napi::Value helloWorld(const Napi::CallbackInfo& info) {
    std::cout << "hello, world!" << std::endl;
    return info.Env().Undefined();
}

static Napi::Object initModule(Napi::Env env, Napi::Object exports) {
    exports.Set("helloWorld", Napi::Function::New(env, helloWorld));
    return exports;
}

NODE_API_MODULE(addonModule, initModule)
