#ifndef CONFIG_H
#define CONFIG_H

#include "serializer/cppserializer.hpp"
#include <fstream>
#include <iomanip>

//首页配置
struct SystemParam
{
	//plc
	std::string plc_ipadd = "192.168.250.1";
	std::string plc_port = "9600";

	std::string plc_update = "W0.0";
	std::string plc_updateUid = "W0.0";
	std::string plc_updatematerial = "W0.1";

	std::string plc_start = "W0.2";
	std::string plc_lose = "W0.3";

	std::string plc_lcode = "W0.3";
	std::string plc_lok = "W0.3";
	std::string plc_lng = "W0.3";
	std::string plc_lcodeback = "W0.3";
	std::string plc_lcodestart = "W0.3";

	std::string plc_rcode = "W0.3";
	std::string plc_rok = "W0.3";
	std::string plc_rng = "W0.3";
	std::string plc_rcodeback = "W0.3";
	std::string plc_rcodestart = "W0.3";
	
	std::string LeftFront = "D:/1.ccf";
	std::string LeftContrary = "D:/2.ccf";
	std::string RightFront = "D:/3.ccf";
	std::string RightContrary = "D:/4.ccf";

	std::string LeftFront_Save_Dir = "E:/";
	std::string LeftContrary_Save_Dir = "E:/";
	std::string RightFront_Save_Dir = "E:/";
	std::string RightContrary_Save_Dir = "E:/";

	std::string honeywelipl1 = "192.168.250.1";
	std::string honeywelipr1 = "192.168.250.1";
	std::string honeywelipl2 = "192.168.250.1";
	std::string honeywelipr2 = "192.168.250.1";
	std::string honeywelportl1 = "9600";
	std::string honeywelportl2 = "9600";
	std::string honeywelportr1 = "9600";
	std::string honeywelportr2 = "9600";

	std::string Rect = "90";
	std::string Unit = "90";
	std::string NG = "90";
};

DEFINE_STRUCT_SCHEMA(SystemParam,
	DEFINE_STRUCT_FIELD(plc_ipadd, "plc_ipadd"),
	DEFINE_STRUCT_FIELD(plc_port, "plc_port"),

	DEFINE_STRUCT_FIELD(plc_update, "plc_update"),
	DEFINE_STRUCT_FIELD(plc_updateUid, "plc_updateUid"),
	DEFINE_STRUCT_FIELD(plc_updatematerial, "plc_updatematerial"),

	DEFINE_STRUCT_FIELD(plc_start, "plc_start"),
	DEFINE_STRUCT_FIELD(plc_lose, "plc_lose"),

	DEFINE_STRUCT_FIELD(plc_lcode, "plc_lcode"),
	DEFINE_STRUCT_FIELD(plc_lok, "plc_lok"),
	DEFINE_STRUCT_FIELD(plc_lng, "plc_lng"),
	DEFINE_STRUCT_FIELD(plc_lcodeback, "plc_lcodeback"),
	DEFINE_STRUCT_FIELD(plc_lcodestart, "plc_lcodestart"),

	DEFINE_STRUCT_FIELD(plc_rcode, "plc_rcode"),
	DEFINE_STRUCT_FIELD(plc_rok, "plc_rok"),
	DEFINE_STRUCT_FIELD(plc_rng, "plc_rng"),
	DEFINE_STRUCT_FIELD(plc_rcodeback, "plc_rcodeback"),
	DEFINE_STRUCT_FIELD(plc_rcodestart, "plc_rcodestart"),
	
	DEFINE_STRUCT_FIELD(LeftFront_Save_Dir, "LeftFront_Save_Dir"),
	DEFINE_STRUCT_FIELD(LeftContrary_Save_Dir, "LeftContrary_Save_Dir"),
	DEFINE_STRUCT_FIELD(RightFront_Save_Dir, "RightFront_Save_Dir"),
	DEFINE_STRUCT_FIELD(RightContrary_Save_Dir, "RightContrary_Save_Dir"),

	DEFINE_STRUCT_FIELD(LeftFront, "LeftFront"),
	DEFINE_STRUCT_FIELD(LeftContrary, "LeftContrary"),
	DEFINE_STRUCT_FIELD(RightFront, "RightFront"),
	DEFINE_STRUCT_FIELD(RightContrary, "RightContrary"),

	DEFINE_STRUCT_FIELD(honeywelipl1, "honeywelipl1"),
	DEFINE_STRUCT_FIELD(honeywelipr1, "honeywelipr1"),
	DEFINE_STRUCT_FIELD(honeywelipl2, "honeywelipl2"),
	DEFINE_STRUCT_FIELD(honeywelipr2, "honeywelipr2"),
	DEFINE_STRUCT_FIELD(honeywelportl1, "honeywelportl1"),
	DEFINE_STRUCT_FIELD(honeywelportl2, "honeywelportl2"),
	DEFINE_STRUCT_FIELD(honeywelportr1, "honeywelportr1"),
	DEFINE_STRUCT_FIELD(honeywelportr2, "honeywelportr2"),

	DEFINE_STRUCT_FIELD(Rect, "Rect"),
	DEFINE_STRUCT_FIELD(Unit, "Unit"),
	DEFINE_STRUCT_FIELD(NG, "NG")
)
#endif // !CONFIG_H