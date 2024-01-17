#pragma once

#include <memory>

#ifdef PN_PLATFORM_WINDOWS
	#ifdef DLL_BUILD
		#ifdef PN_BUILD_DLL
			#define PHOENIX_API __declspec(dllexport)
		#else
			#define PHOENIX_API __declspec(dllimport)
		#endif 
	#else 
		#define PHOENIX_API 
	#endif
#else
	#error Phoenix only supports Windows.
#endif

#ifdef PN_DEBUG
	#define PN_ENABLE_ASSERTS
#endif

#ifdef PN_ENABLE_ASSERTS
	#define PN_CLIENT_ASSERT(x, ...) { if (!(x)) { PN_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PN_CORE_ASSERT(x, ...) { if (!(x)) { PN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PN_CLIENT_ASSERT(x, ...)
	#define PN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

namespace Phoenix {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
