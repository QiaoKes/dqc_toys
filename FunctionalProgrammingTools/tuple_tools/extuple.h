#pragma once
#include <functional>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

namespace exfp
{

	template<typename ...Args>
	constexpr std::size_t tuple_length(const std::tuple<Args...>& _t)
	{
		return sizeof...(Args);
	}

	template<typename Func, typename Tuple, size_t N>
	struct tupleHelper {
		static void func(Func _f, const Tuple& _t)
		{
			tupleHelper<Func, Tuple, N - 1>::func(_f, _t);
			_f(std::get<N - 1>(_t), N - 1);
		}
	};

	template<typename Func, typename Tuple>
	struct tupleHelper<Func, Tuple, 1> {
		static void func(Func _f, const Tuple& _t)
		{
			_f(std::get<0>(_t), 0);
		}
	};

	/*处理方式不好，弃用
	template<typename Func, typename Tuple>
	struct tupleHelper<Func, Tuple, 0> {
		static void func(Func _f, const Tuple& _t)
		{
			_f("", -1);
		}
	};*/

	template<typename Func, typename ...Args>
	void control_tuple(Func _f, const std::tuple<Args...>& _t)
	{
		tupleHelper<Func, decltype(_t), sizeof...(Args)>::func(_f, _t);
	}

	// empty tuple
	template<typename Func>
	void control_tuple(Func _f, const std::tuple<>& _t)
	{
		std::cerr << "Warning! This is a empty tuple." << std::endl;
	}

	template<typename ...Args>
	void print_tuple(const std::tuple<Args...>& _t)
	{
		if (tuple_length(_t) == 0) {
			std::cout << "()";
			return ;
		}
		std::cout << "(";
		control_tuple(
			[](auto _t, std::size_t idx)
			{
				if (idx != 0) std::cout << ", ";
				std::cout << _t;
			}, _t);
	std::cout << ")";
	}

	template<typename T, typename ...Ts>
	T head(const std::tuple<T, Ts...>& _t)
	{
		return std::get<0>(_t);
	}

	template<typename ...Ts>
	auto last(const std::tuple<Ts...>& _t)
	{
		return std::get<sizeof...(Ts) - 1u>(_t);
	}


	template<size_t ...Is, typename ...Ts>
	auto tailBuilder(std::index_sequence<Is...>, const std::tuple<Ts...>& _t)
	{
		return std::make_tuple(std::get<Is + 1u>(_t)...);
	}

	template<typename T, typename ...Ts>
	auto tail(const std::tuple<T, Ts...>& _t)
	{
		return tailBuilder(std::make_index_sequence<sizeof...(Ts)>(), _t);
	}

	template<size_t ...Is, typename ...Ts>
	auto initBuilder(std::index_sequence<Is...>, const std::tuple<Ts...>& _t)
	{
		return std::make_tuple(std::get<Is>(_t)...);
	}

	template<typename T, typename ...Ts>
	auto init(const std::tuple<T, Ts...>& _t)
	{
		return initBuilder(std::make_index_sequence<sizeof...(Ts)>(), _t);
	}

}


