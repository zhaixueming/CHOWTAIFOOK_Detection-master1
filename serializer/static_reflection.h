// Static Reflection by BOT Man, 2018

#ifndef STATIC_REFLECTION_H_
#define STATIC_REFLECTION_H_

#include <tuple>
#include <type_traits>

namespace detail1
{

    template <typename Fn, typename Tuple, std::size_t... I>
    inline constexpr void ForEachTuple(Tuple &&tuple,
                                       Fn &&fn,
                                       std::index_sequence<I...>)
    {
        using Expander = int[];
        (void)Expander{0, ((void)fn(std::get<I>(std::forward<Tuple>(tuple))), 0)...};
    }

    template <typename Fn, typename Tuple>
    inline constexpr void ForEachTuple(Tuple &&tuple, Fn &&fn)
    {
        ForEachTuple(
            std::forward<Tuple>(tuple), std::forward<Fn>(fn),
            std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
    }

    template <typename T>
    struct is_field_pointer : std::false_type
    {
    };

    template <typename C, typename T>
    struct is_field_pointer<T C::*> : std::true_type
    {
    };

    template <typename T>
    constexpr auto is_field_pointer_v = is_field_pointer<T>::value;

} // namespace detail1

#endif // STATIC_REFLECTION_H_
