# -*- coding=utf-8 -*-
#  AL-NI-Thermo-data(TDB).txt 文件转化为 cpp 文件
from change_TDB_FUNCTION_to_Cpp import functionToCpp
from change_TDB_PHASE_to_Cpp import phaseToCpp

if __name__ == '__main__':
    TDBfilepath='XTPowerAndHeating/AL-NI-Thermo-data(TDB).txt'
    cppfilepath='XTPowerAndHeating/AL-NI(h).cpp'
    functionToCpp(TDBfilepath, cppfilepath)
    phaseToCpp(TDBfilepath, cppfilepath)