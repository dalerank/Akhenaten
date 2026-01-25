#pragma once

#ifndef TRACY_ENABLE

#define OZZY_PROFILER_BEGIN
#define OZZY_PROFILER_FRAME(x)
#define OZZY_PROFILER_SECTION(x)
#define OZZY_PROFILER_TAG(y, x)
#define OZZY_PROFILER_LOG(text, size)
#define OZZY_PROFILER_VALUE(text, value)

#else

#if defined( __clang__ ) || defined( __GNUC___ )
#define TracyFunction __PRETTY_FUNCTION__
#elif defined( _MSC_VER )
#define TracyFunction __FUNCSIG__
#endif

#undef TRACY_CALLSTACK 


#ifdef TRACY_MEMORY_ENABLE
#define TRACY_CALLSTACK 20
#endif

#include <cstdint>
#include <cinttypes>

#include "tracy/Tracy.hpp"
#include "tracy/TracyC.h"

#define TRACY_SCOPE_IMPLEMENT_TAG_FUNC( ValueType, ValueName, ValueFormatSpecifier, ... )                                                                      \
	void Tag( const char* pTag, ValueType ValueName )                                                                                                          \
	{                                                                                                                                                          \
		int WantedToWrite = std::snprintf( _TagBuffer.data(),                                                                                                  \
										   TagBufferSize,                                                                                                      \
										   "%s: " ValueFormatSpecifier,                                                                                        \
										   pTag,                                                                                                               \
										   __VA_ARGS__ );                                                                                                      \
		std::size_t StrLen = std::min( static_cast<std::size_t>( WantedToWrite ), TagBufferSize - 1 );                                                         \
		TracyCZoneText( _TracyContext, _TagBuffer.data(), StrLen );                                                                                            \
	}

namespace Profiler {
	class TracyScope;
	inline thread_local TracyScope *pTracyCurrentScope = nullptr;

	enum class ECategory : uint64_t {
		None = 0,
		Rendering = tracy::Color::Burlywood,
		Animation = tracy::Color::LightSkyBlue,
		Audio = tracy::Color::HotPink,
		AI = tracy::Color::Purple,
		UI = tracy::Color::PaleTurquoise,
		Input = tracy::Color::Ivory,
		IO = tracy::Color::Khaki,
		Script = tracy::Color::Plum,
		GameLogic = tracy::Color::RoyalBlue,
		Wait = tracy::Color::Tomato,
		WaitEmpty = tracy::Color::White,
		Debug = tracy::Color::Black,
		Loading = tracy::Color::LightSteelBlue,
		Saving = tracy::Color::Thistle,
		HotReload = tracy::Color::LightBlue,
		FastTick = tracy::Color::Gold,
		SlowTick = tracy::Color::Goldenrod,
		Task = tracy::Color::Chocolate,
		Graphics = tracy::Color::Wheat,
		Particles = tracy::Color::LightPink,
		Other = tracy::Color::GreenYellow,
	};

	using EPlotFormat = tracy::PlotFormatType;

	class TracyScope {
	public:
		static constexpr std::size_t TagBufferSize = 1024u;
		static_assert(TagBufferSize >= 1u); // NOTE: a buffer size of 1 can only hold the null terminator

		TracyScope(const TracyScope &) = delete;
		TracyScope(TracyScope &&) = delete;
		TracyScope &operator=(const TracyScope &) = delete;
		TracyScope &operator=(TracyScope &&) = delete;

		explicit TracyScope(TracyCZoneCtx Ctx)
			: _TracyContext{ Ctx }
			, _pPreviousScope{ pTracyCurrentScope } {
			pTracyCurrentScope = this;
		}

		void Pop() {
			if (_Popped) {
				return;
			}

			TracyCZoneEnd(_TracyContext);
			pTracyCurrentScope = _pPreviousScope;
			_Popped = true;
		}

		~TracyScope() { Pop(); }

		TRACY_SCOPE_IMPLEMENT_TAG_FUNC(float, Value, "%f", Value);
		TRACY_SCOPE_IMPLEMENT_TAG_FUNC(int32_t, Value, "%d", Value);
		TRACY_SCOPE_IMPLEMENT_TAG_FUNC(uint32_t, Value, "%u", Value);
		TRACY_SCOPE_IMPLEMENT_TAG_FUNC(uint64_t, Value, "%" PRIu64, Value);
		TRACY_SCOPE_IMPLEMENT_TAG_FUNC(const char *, pValue, "%s", pValue);
		TRACY_SCOPE_IMPLEMENT_TAG_FUNC(const std::string_view&, Value, "%.*s", static_cast<int>(Value.size()), Value.data());

	private:
		TracyScope *_pPreviousScope;
		TracyCZoneCtx _TracyContext;
		std::array<char, TagBufferSize> _TagBuffer;
		bool _Popped = false;
	};

	template <typename T>
	void Tag(const char *pTag, T &&Value) {
		if (!pTracyCurrentScope) {
			assert("Can't tag: not in a profiled scope.");
			return;
		}

		pTracyCurrentScope->Tag(pTag, std::forward<T>(Value));
	}

	template <bool Bad>
	void Pop() {
		static_assert(Bad, "You must pass a parameter to PROFILE_SCOPE_END()");
	}

	template <>
	inline void Pop<true>() {
		if (!pTracyCurrentScope) {
			assert("Can't pop: not in a profiled scope.");
			return;
		}

		pTracyCurrentScope->Pop();
	}
}

inline const char* TracyGetStr(const char *pStr) {
	return pStr;
}

inline const char *TracyGetStr(const std::string_view &StringView) {
	return StringView.data();
}

inline uint64_t UnknownTracyAllocSrclocApi();

template <typename UNUSED = int>
inline uint64_t TracyAllocSrclocName(uint32_t Line,
	const char *Source,
	size_t SourceSz,
	const char *Function,
	size_t FunctionSz,
	const char *Name,
	size_t NameSz) {

	using TracyAllocT = decltype(&___tracy_alloc_srcloc_name);
	using TracyAlloc010T = uint64_t(*)(uint32_t, const char *, size_t, const char *, size_t, const char *, size_t);
	using TracyAlloc011T = uint64_t(*)(uint32_t,
		const char *,
		size_t,
		const char *,
		size_t,
		const char *,
		size_t,
		uint32_t);

	if constexpr (std::is_same_v<TracyAllocT, TracyAlloc010T>) {
		return reinterpret_cast<TracyAlloc010T>(
			&___tracy_alloc_srcloc_name)(Line, Source, SourceSz, Function, FunctionSz, Name, NameSz);
	} else if constexpr (std::is_same_v<TracyAllocT, TracyAlloc011T>) {
		return reinterpret_cast<TracyAlloc011T>(
			&___tracy_alloc_srcloc_name)(Line, Source, SourceSz, Function, FunctionSz, Name, NameSz, 0);
	} else {
		return UnknownTracyAllocSrclocApi(); // causes a linker error by design
	}
}

#define TracyCDynZoneN( ctx, name, active )                                                 \
	const auto TracyConcat( __tracy_source_location, TracyLine ) = TracyAllocSrclocName(    \
		static_cast<uint32_t>( TracyLine ),                                                 \
		TracyFile,                                                                          \
		strlen( TracyFile ),                                                           \
		__func__,                                                                           \
		strlen( __func__ ),                                                            \
		TracyGetStr( name ),                                                                \
		strlen( TracyGetStr( name ) ) );                                               \
	TracyCZoneCtx ctx = ___tracy_emit_zone_begin_alloc( TracyConcat( __tracy_source_location, TracyLine ), active );

#define OZZY_PROFILER_BEGIN_FRAME( ... ) FrameMark;

#define OZZY_PROFILER_FUNCTION( ... )																\
	TracyCZoneC( ___tracy_function_ctx, (uint32_t)__VA_ARGS__ + 0, true );					\
	Profiler::TracyScope ___TracyFunction { ___tracy_function_ctx };

#define OZZY_PROFILER_SECTION_DYNAMIC( name, ... )                                                           \
	TracyCDynZoneN( TracyConcat( ___tracy_scope_dyn_ctx, TracyLine ), name, true );                      \
	Profiler::TracyScope TracyConcat( ___TracyScopeDynamic, TracyLine ) { TracyConcat( ___tracy_scope_dyn_ctx, TracyLine ) }; \
	___tracy_emit_zone_color( TracyConcat( ___tracy_scope_dyn_ctx, TracyLine ), (uint32_t)__VA_ARGS__ + 0 );

#define OZZY_PROFILER_SECTION( id, name, ... ) OZZY_PROFILER_SECTION_DYNAMIC( name, __VA_ARGS__ )
#define OZZY_PROFILER_SECTION_END( id ) Profiler::Pop<std::string_view { #id } != "">();
#define OZZY_PROFILER_TAG( id, ... ) Profiler::Tag( id, __VA_ARGS__ );
#define OZZY_PROFILER_PLOT( name, value ) TracyPlot( name, value )

// name:  The identifier of the plot to set the format for
// format: (Profiler::EPlotFormats::) Number, Memory, Percentage. See Tracy documentation for details
// step: bool    Use staircase plot instead of line plot
// fill: bool	 Shade the area under the plot
// color: hex code color, e.g. 0xD70000. Note: 0 (and 0x000000) is a magic value that means "I don't care, pick a new color for me."
#define OZZY_PROFILER_PLOT_FORMAT( name, format, step, fill, color ) TracyPlotConfig( name, format, step, fill, color )

#if defined( TRACY_MEMORY_ENABLE )
#define OZZY_PROFILER_MEM_NEW( ptr, size ) TracyCAlloc( ptr, size )
#define OZZY_PROFILER_MEM_DELETE( ptr ) TracyCFree( ptr )
#else
#define OZZY_PROFILER_MEM_NEW( ptr, size )
#define OZZY_PROFILER_MEM_DELETE( ptr )
#endif

#endif
