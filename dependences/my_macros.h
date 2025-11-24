#pragma once

#define autodel(type) __attribute__((cleanup(del_##type))) type

#define anon_lamb ,l##__COUNTER__,
#define _lambda(base, name, body...) ({base name body;name;})
#define lambda(base_name_body...) _lambda(base_name_body)

#define PREMAIN __attribute__ ((constructor))

#define UNUSED_ARG __attribute__((unused))