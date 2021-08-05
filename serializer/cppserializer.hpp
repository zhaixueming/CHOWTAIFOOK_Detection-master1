#ifndef CPP_SERIALIZER_H
#define CPP_SERIALIZER_H

#include "static_reflection.h"
#include "optional_json.h"

template <typename T>
inline constexpr auto StructSchema()
{
    return std::make_tuple();
}

#define DEFINE_STRUCT_SCHEMA(Struct, ...)        \
    template <>                                  \
    inline constexpr auto StructSchema<Struct>() \
    {                                            \
        using _Struct = Struct;                  \
        return std::make_tuple(__VA_ARGS__);     \
    }

#define DEFINE_STRUCT_FIELD(StructField, FieldName) \
    std::make_tuple(&_Struct::StructField, FieldName)

template <typename T, typename Fn>
inline constexpr void ForEachField(T &&value, Fn &&fn)
{
    constexpr auto struct_schema = StructSchema<std::decay_t<T>>();
    static_assert(std::tuple_size<decltype(struct_schema)>::value != 0,
                  "StructSchema<T>() for type T should be specialized to return "
                  "FieldSchema tuples, like ((&T::field, field_name), ...)");

    detail1::ForEachTuple(struct_schema, [&value, &fn](auto &&field_schema) {
        using FieldSchema = std::decay_t<decltype(field_schema)>;
        static_assert(
            std::tuple_size<FieldSchema>::value >= 2 &&
                detail1::is_field_pointer_v<std::tuple_element_t<0, FieldSchema>>,
            "FieldSchema tuple should be (&T::field, field_name)");

        fn(value.*(std::get<0>(std::forward<decltype(field_schema)>(field_schema))),
           std::get<1>(std::forward<decltype(field_schema)>(field_schema)));
    });
}

namespace
{
    template <typename T>
    struct is_optional : std::false_type
    {
    };

    template <typename T>
    struct is_optional<std::unique_ptr<T>> : std::true_type
    {
    };

    template <typename T>
    constexpr bool is_optional_v = is_optional<std::decay_t<T>>::value;

    template <typename T>
    constexpr bool has_schema = std::tuple_size<decltype(StructSchema<T>())>::value;

} // namespace

namespace nlohmann
{

    template <typename T>
    struct adl_serializer<T, std::enable_if_t<::has_schema<T>>>
    {
        template <typename BasicJsonType>
        static void to_json(BasicJsonType &j, const T &value)
        {
            ForEachField(value, [&j](auto &&field, auto &&name) { j[name] = field; });
        }

        template <typename BasicJsonType>
        static void from_json(const BasicJsonType &j, T &value)
        {
            ForEachField(value, [&j](auto &&field, auto &&name) {
                // ignore missing field of optional
                if (::is_optional_v<decltype(field)> && j.find(name) == j.end())
                    return;

                j.at(name).get_to(field);
            });
        }
    };

} // namespace nlohmann

#endif