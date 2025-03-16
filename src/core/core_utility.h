#pragma once

namespace type_traits {
	template <typename T>
	struct first_func_argument;

	template <typename FirstArg>
	struct first_func_argument<void(*)(FirstArg)> {
		using type = FirstArg;
	};

	template <typename FirstArg>
	struct first_func_argument<std::function<void(FirstArg)>> {
		using type = FirstArg;
	};

	template <typename Class, typename FirstArg>
	struct first_func_argument<void(Class:: *)(FirstArg)> {
		using type = FirstArg;
	};

	template <typename Class, typename FirstArg> // for class and lamdas
	struct first_func_argument<void(Class:: *)(FirstArg) const> {
		using type = FirstArg;
	};

} // namespace type_traits