#pragma once

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <iosfwd>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <ratio>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include <REL/Relocation.h>

#include <ShlObj_core.h>
#include <Windows.h>
#include <Psapi.h>
#undef cdecl // Workaround for Clang 14 CMake configure error.

//#include <spdlog/sinks/basic_file_sink.h>
//#include <spdlog/sinks/msvc_sink.h>

// Compatible declarations with other sample projects.
#define DLLEXPORT __declspec(dllexport)
#include <toml++/toml.h>
#include "include\AutoTOML.h"
using namespace std::literals;
using namespace REL::literals;



// This file is required.
#include "include\PerkEntryPointExtenderAPI.h"




namespace stl {
    using namespace SKSE::stl;
    template <std::integral T, std::size_t N>
    void safe_write(std::uintptr_t a_dst, const std::array<T, N>& a_data) {
        REL::safe_write(a_dst, a_data.data(), a_data.size() * sizeof(T));
    }

    template <class T>
    void write_call(std::uintptr_t a_source) {
        SKSE::AllocTrampoline(14);
        auto& trampoline = SKSE::GetTrampoline();
        trampoline.write_call<5>(a_source, T::Call);
    }
    template <class T>
    void write_thunk_call(std::uintptr_t a_src) {
        SKSE::AllocTrampoline(14);

        auto& trampoline = SKSE::GetTrampoline();
        T::func = trampoline.write_call<5>(a_src, T::thunk);
    }

    //template <class F, std::size_t idx, class T>
    //void write_vfunc() {
    //    REL::Relocation<std::uintptr_t> vtbl{F::VTABLE[0]};
    //    T::func = vtbl.write_vfunc(idx, T::thunk);
    //}
    template <class F, std::size_t idx, class T, std::size_t x = 0>
    void write_vfunc() {
        REL::Relocation<std::uintptr_t> vtbl{F::VTABLE[x]};
        T::func = vtbl.write_vfunc(idx, T::thunk);
    }
    template <std::size_t idx, class T>
    void write_vfunc(REL::VariantID id) {
        REL::Relocation<std::uintptr_t> vtbl{id};
        T::func = vtbl.write_vfunc(idx, T::thunk);
    }
}

