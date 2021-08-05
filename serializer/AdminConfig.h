#ifndef ADMINCONFIG_H
#define ADMINCONFIG_H

#include <fstream>
#include <iomanip>
#include "serializer/cppserializer.hpp"

//首页配置
struct AdminParam
{
	std::string adminpassword = "1";
	std::string userpassword = "2";
};

DEFINE_STRUCT_SCHEMA(AdminParam,
	DEFINE_STRUCT_FIELD(adminpassword, "adminpassword"),
	DEFINE_STRUCT_FIELD(userpassword, "userpassword")
)
#endif // !CONFIG_H