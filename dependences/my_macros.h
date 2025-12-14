#pragma once

#define autodel(type) __attribute__((cleanup(del_##type))) type

#define anon_lamb ,l##__COUNTER__,
#define _lambda(base, name, body...) ({base name body;name;})
#define lambda(base_name_body...) _lambda(base_name_body)

#define PREMAIN __attribute__ ((constructor))

#define UNUSED_ARG __attribute__((unused))

#define SECOND_ARG(a, b, ...) b
#define DEFAULT_IF_NONE(def_val, arg...) SECOND_ARG(_, ##arg, def_val)

#define _G_TYPE(type) *(type*)0