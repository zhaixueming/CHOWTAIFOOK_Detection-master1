#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "serializer/cppserializer.hpp"
#include <fstream>
#include <iomanip>

//首页配置
struct ThresholdParam
{
    //thresholdparam
    std::string pressedA = "S≤0.10 mm²";
    std::string pressedB = "S≤0.2 mm²";
    std::string pressedC = "S≤0.4 mm²";

	std::string bumpsA = "S≤0.08mm², N≤1";
    std::string bumpsB = "S≤0.1 mm²";
    std::string bumpsC = "S≤0.4 mm²";

    std::string scratchHardA = "不允许";
    std::string scratchHardB = "L≤1.00mm,W≤0.05mm，N≤1";
    std::string scratchHardC = "在不影响功能的情况下不管控";
    std::string scratchSmallA = "L≤2.5mm,W≤0.05mm, DS≥10mm  N≤2";
    std::string scratchSmallB = "L≤4.00mm,W≤0.10mm，N≤2";
    std::string scratchSmallC = "L≤6.00mm,W≤0.10mm，N≤3";
    
    std::string brushA = "S≤0.10 mm²,N≤2";
    std::string brushB = "S≤0.2 mm²,N≤2";
    std::string brushC = "在不影响功能的情况下不管控";
    
	std::string baomoTP = "仅允许S≤0.03且N≤2";
    std::string baomoBP = "仅允许S≤0.05且N≤2";
    
	std::string pockA = "反光才可见,L≤4mm,且W≤0.08mm,N≤1";
    std::string pockB = "L≤5.00mm,N≤4";
    std::string pockC = "不做管控";

    std::string dirty = "脏污";

	std::string mirageA = " 幻影1 ";
    std::string mirageB = " 幻影2 ";
    std::string mirageC = " ";
    
};

DEFINE_STRUCT_SCHEMA(ThresholdParam,
                     DEFINE_STRUCT_FIELD(pressedA, "pressedA"),
                     DEFINE_STRUCT_FIELD(pressedB, "pressedB"),
                     DEFINE_STRUCT_FIELD(pressedC, "pressedC"),
                     
					 DEFINE_STRUCT_FIELD(bumpsA, "bumpsA"),
                     DEFINE_STRUCT_FIELD(bumpsB, "bumpsB"),
                     DEFINE_STRUCT_FIELD(bumpsC, "bumpsC"),

                     DEFINE_STRUCT_FIELD(scratchHardA, "scratchHardA"),
                     DEFINE_STRUCT_FIELD(scratchHardB, "scratchHardB"),
                     DEFINE_STRUCT_FIELD(scratchHardC, "scratchHardC"),
					
                     DEFINE_STRUCT_FIELD(scratchSmallA, "scratchSmallA"),
                     DEFINE_STRUCT_FIELD(scratchSmallB, "scratchSmallB"),
                     DEFINE_STRUCT_FIELD(scratchSmallC, "scratchSmallC"),

                     DEFINE_STRUCT_FIELD(brushA, "brushA"),
                     DEFINE_STRUCT_FIELD(brushB, "brushB"),
                     DEFINE_STRUCT_FIELD(brushC, "brushC"),

                     DEFINE_STRUCT_FIELD(baomoTP, "baomoTP"),
                     DEFINE_STRUCT_FIELD(baomoBP, "baomoBP"),

                     DEFINE_STRUCT_FIELD(pockA, "pockA"),
                     DEFINE_STRUCT_FIELD(pockB, "pockB"),
                     DEFINE_STRUCT_FIELD(pockC, "pockC"),

                     DEFINE_STRUCT_FIELD(dirty, "dirty"),

                     DEFINE_STRUCT_FIELD(mirageA, "mirageA"),
                     DEFINE_STRUCT_FIELD(mirageB, "mirageB"),
                     DEFINE_STRUCT_FIELD(mirageC, "mirageC")

					 )
#endif // !THRESHOLD_H