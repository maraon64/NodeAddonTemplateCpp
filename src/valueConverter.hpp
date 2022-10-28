#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>

#include <napi.h>

namespace valueConverter {

inline Napi::Object valueAsObject(const Napi::Value& value) {
    return value.As<Napi::Object>();
}

inline Napi::Array valueAsArray(const Napi::Value& value) {
    return value.As<Napi::Array>();
}

inline Napi::Function valueAsFunction(const Napi::Value& v) {
    return v.As<Napi::Function>();
}

inline Napi::Number valueAsNumber(const Napi::Value& value) {
    return value.As<Napi::Number>();
}

inline Napi::Boolean valueAsBool(const Napi::Value& value) {
    return value.As<Napi::Boolean>();
}

inline Napi::String valueAsString(const Napi::Value& value) {
    return value.As<Napi::String>();
}

inline Napi::BigInt valueAsBigInt(const Napi::Value& value) {
    return value.As<Napi::BigInt>();
}

inline uint8_t asU8(const Napi::Value& value) {
    return static_cast<uint8_t>(valueAsNumber(value).Uint32Value());
}

inline uint8_t asU8Or(const Napi::Value& value, uint8_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asU8(value);
}

inline uint16_t asU16(const Napi::Value& value) {
    return static_cast<uint16_t>(valueAsNumber(value).Uint32Value());
}

inline uint16_t asU16Or(const Napi::Value& value, uint16_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asU16(value);
}

inline uint32_t asU32(const Napi::Value& value) {
    return valueAsNumber(value).Uint32Value();
}

inline uint32_t asU32Or(const Napi::Value& value, uint32_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asU32(value);
}

inline uint64_t asU64_n(const Napi::Value& value) {
    bool lossless;
    const auto v = valueAsBigInt(value).Uint64Value(&lossless);
    if (!lossless) throw Napi::Error::New(value.Env(), "couldn't convert bigint to uint64 losslessly");
    return v;
}

inline uint64_t asU64Or_n(const Napi::Value& value, uint64_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asU64_n(value);
}

inline uint64_t asU64(const Napi::Value& value) {
    return value.IsNumber() ? static_cast<uint64_t>(valueAsNumber(value).Int64Value()) : asU64_n(value);
}

inline uint64_t asU64Or(const Napi::Value& value, uint64_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asU64(value);
}

inline int8_t asS8(const Napi::Value& value) {
    return static_cast<int8_t>(valueAsNumber(value).Int32Value());
}

inline int8_t asS8Or(const Napi::Value& value, int8_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asS8(value);
}

inline int16_t asS16(const Napi::Value& value) {
    return static_cast<int16_t>(valueAsNumber(value).Int32Value());
}

inline int16_t asS16Or(const Napi::Value& value, int16_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asS16(value);
}

inline int32_t asS32(const Napi::Value& value) {
    return valueAsNumber(value).Int32Value();
}

inline int32_t asS32Or(const Napi::Value& value, int32_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asS32(value);
}

inline int64_t asS64_n(const Napi::Value& value) {
    bool lossless;
    const auto v = valueAsBigInt(value).Int64Value(&lossless);
    if (!lossless) throw Napi::Error::New(value.Env(), "couldn't convert bigint to int64 losslessly");
    return v;
}

inline int64_t asS64Or_n(const Napi::Value& value, int64_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asS64_n(value);
}

inline int64_t asS64(const Napi::Value& value) {
    return value.IsNumber() ? valueAsNumber(value).Int64Value() : asS64_n(value);
}

inline int64_t asS64Or(const Napi::Value& value, int64_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asS64(value);
}

inline float asF32(const Napi::Value& value) {
    return valueAsNumber(value).FloatValue();
}

inline float asF32Or(const Napi::Value& value, float defaultValue) {
    return value.IsUndefined() ? defaultValue : asF32(value);
}

inline double asF64(const Napi::Value& value) {
    return valueAsNumber(value).DoubleValue();
}

inline double asF64Or(const Napi::Value& value, double defaultValue) {
    return value.IsUndefined() ? defaultValue : asF64(value);
}

inline bool asBool(const Napi::Value& value) {
    return valueAsBool(value).Value();
}

inline bool asBoolOr(const Napi::Value& value, bool defaultValue) {
    return value.IsUndefined() ? defaultValue : asBool(value);
}

inline bool toBool(const Napi::Value& value) {
    return value.ToBoolean().Value();
}

inline std::string asStrUtf8(const Napi::Value& value) {
    return valueAsString(value).Utf8Value();
}

inline std::string asStrUtf8Or(const Napi::Value& value, const std::string& defaultValue) {
    return value.IsUndefined() ? defaultValue : asStrUtf8(value);
}

inline std::u16string asStrUtf16(const Napi::Value& value) {
    return valueAsString(value).Utf16Value();
}

inline std::u16string asStrUtf16Or(const Napi::Value& value, const std::u16string& defaultValue) {
    return value.IsUndefined() ? defaultValue : asStrUtf16(value);
}

inline std::filesystem::path asPath(const Napi::Value& value) {
#ifdef _WIN32
    return asStrUtf16(value);
#else
    return asStrUtf8(value);
#endif
}

inline std::filesystem::path asPathOr(const Napi::Value& value, const std::filesystem::path& defaultValue) {
    return value.IsUndefined() ? defaultValue : asPath(value);
}

inline size_t asSize(const Napi::Value& value) {
    return static_cast<size_t>(asU64(value));
}

inline size_t asSizeOr(const Napi::Value& value, size_t defaultValue) {
    return value.IsUndefined() ? defaultValue : asSize(value);
}

inline Napi::Value fromU8(Napi::Env env, uint8_t value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromU16(Napi::Env env, uint16_t value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromU32(Napi::Env env, uint32_t value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromU64_n(Napi::Env env, uint64_t value) {
    return Napi::BigInt::New(env, value);
}

inline Napi::Value fromU64(Napi::Env env, uint64_t value) {
    return Napi::Number::New(env, static_cast<double>(value));
}

inline Napi::Value fromS8(Napi::Env env, int8_t value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromS16(Napi::Env env, int16_t value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromS32(Napi::Env env, int32_t value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromS64_n(Napi::Env env, int64_t value) {
    return Napi::BigInt::New(env, value);
}

inline Napi::Value fromS64(Napi::Env env, int64_t value) {
    return Napi::Number::New(env, static_cast<double>(value));
}

inline Napi::Value fromF32(Napi::Env env, float value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromF64(Napi::Env env, double value) {
    return Napi::Number::New(env, value);
}

inline Napi::Value fromBool(Napi::Env env, bool value) {
    return Napi::Boolean::New(env, value);
}

inline Napi::Value fromStrUtf8(Napi::Env env, const char* value) {
    return Napi::String::New(env, value);
}

inline Napi::Value fromStrUtf8(Napi::Env env, const char* value, size_t length) {
    return Napi::String::New(env, value, length);
}

inline Napi::Value fromStrUtf8(Napi::Env env, const std::string& value) {
    return Napi::String::New(env, value);
}

inline Napi::Value fromStrUtf8(Napi::Env env, std::string_view value) {
    return Napi::String::New(env, value.data(), value.size());
}

inline Napi::Value fromStrUtf16(Napi::Env env, const char16_t* value) {
    return Napi::String::New(env, value);
}

inline Napi::Value fromStrUtf16(Napi::Env env, const char16_t* value, size_t length) {
    return Napi::String::New(env, value, length);
}

inline Napi::Value fromStrUtf16(Napi::Env env, const std::u16string& value) {
    return Napi::String::New(env, value);
}

inline Napi::Value fromStrUtf16(Napi::Env env, std::u16string_view value) {
    return Napi::String::New(env, value.data(), value.size());
}

inline Napi::Value fromPath(Napi::Env env, const std::filesystem::path& value) {
    const auto str = value.generic_u8string();
    return Napi::String::New(env, reinterpret_cast<const char*>(str.data()), str.size());
}

inline Napi::Value fromSize(Napi::Env env, size_t value) {
    return fromU64_n(env, value);
}

}
