#pragma once

//�ܵ������
template <typename Arg, typename Func>
auto operator|(Arg&& arg, Func&& f) -> decltype(f(std::forward<Arg>(arg)))
{
	return f(std::forward<Arg>(arg));
}

template <typename ...Args, class Func>
auto operator|(std::tuple<Args...>&& args, Func&& f)
{
	return std::apply(std::forward<Func>(f), std::forward<std::tuple<Args...>>(args));
}

namespace exfp 
{
	//Y�����
	template<typename Func>
	class LambdaHelper {
	private:
		Func _f;
	public:
		LambdaHelper(Func f) : _f(f) { }
		template<typename ...Args>
		auto operator()(Args&&... args) const
		{
			return _f(*this, std::forward<Args>(args)...);
		}
	};

	template<typename Func>
	LambdaHelper<Func> Y(Func&& _f)
	{
		return LambdaHelper<Func>(std::forward<Func>(_f));
	}

}

