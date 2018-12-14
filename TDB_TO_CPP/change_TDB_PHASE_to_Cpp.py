# -*- coding=utf-8 -*-
# author : gq    2018-11-21
# phase 转换

def load_file(fileName):
    # 加载文件
    file_text = open(fileName, encoding='utf-8').read().split('\n')
    return  file_text

# 得到全部 PHASE
def find_PHASEs(TDBdata):
    all_PHASE,a_PHASE = [],[]
    PARAMETER_str = ''
    phase_begain,phase_end,PARAMETER_begin = False,False,False
    for index, line in enumerate(TDBdata):
         if(phase_begain==False and (line.find('PHASE')!=-1 or
                  (line.find('TYPE_DEFINITION') != -1 and TDBdata[index+1].find('PHASE') != -1))):
             # 判断一个phase的开始
             phase_begain = True
         if(phase_begain):
             if(line.find('PARAMETER') != -1 ):
                 PARAMETER_begin = True
             # PARAMETER_ 保存为一个string
             if(PARAMETER_begin):
                 PARAMETER_str += line
                 if(len(TDBdata[index+1].replace(' ','')) == 0):
                     phase_end = True
             else:
                a_PHASE.append(line)
             # 保存为一个phase
             if(phase_end):
                 a_PHASE.append(PARAMETER_str)
                 if(len(a_PHASE)>0):
                     all_PHASE.append(a_PHASE)
                     a_PHASE,PARAMETER_str,PARAMETER_begin,phase_begain,phase_end = [],'',False,False,False
    return all_PHASE

# Phase前的注释信息
def phase_note_start(pList,pName):
    note = '\n/*#######################################################################\n'
    for pStr in pList:
        if(len(pStr) != 0):
            note += pStr+'\n'
    note += '-------------------------------------------------------------------\n'
    note += pName+' endmember compounds with VA \n'
    note+= '-------------------------------------------------------------------*/'
    return note

# Phase 偏导函数前的注释信息
def phase_dg_note(pStr):
    return '\n//**************** Gibbs Energy of '+pStr+'  *********************\n'

# PHASE 名称
# 输入：一整个phase数组的信息
# 返回：这个phase的名称
def getPHASE_name(phaseData):
    for info in phaseData:
        info = str(info).strip()
        if(info[0:10].find('PHASE') != -1):
            f_name = info.split(' ')[1]
            return f_name
    return ''

# 函数名称转化
#  G(AL3NI,AL:NI;0)
#  G_AL3NI_AL_NI_0
def getFunction_name(parameterName):
    FLAGs = ['(',':',';']
    for flag in FLAGs:
        parameterName = parameterName.replace(flag,'_')
    return parameterName.replace(')','').replace(',','__')

# PARAMETER  函数 转化为 cpp函数
# 返回一个phase的全部parameter数组
# 如：['G(AL3NI,AL:NI;0)', '298.15', '-48483.73+12.29913*T', '+.75*GHSERAL#+.25*GHSERNI#;', '6000']
def getParamList(parameterData):
    pList = parameterData.strip().split('PARAMETER')
    allParamList = []
    # PARAMETER 列表
    for param in pList:
        if(len(param)==0):
            continue
        pItemList = [p for p in param.strip().split(' ') if len(p)>0]
        allParamList.append(pItemList[0:len(pItemList)-3])
        # print('pItemList',pItemList[0:len(pItemList)-3])
    return allParamList

# PARAMETER  函数 转化为 cpp函数
def paramToCppFunction(allParamList):
    # 循环把所有param转为函数
    funStr = ''
    for param in allParamList:
        pName = getFunction_name(param[0])
        funStr += '\ndouble  '+pName+' (double T) {  \n'
        funStr += '\t if ( T < '+ param[1]+' or T > '+ param[-1]+') { printerror(T); } \n'
        fun_num = ''
        for f in param[2:-1]:
            fun_num += f
        funStr += '\t return '+fun_num + '  } \n'
    return funStr


# phase  转化为 cpp函数
def phaseToCpp(TDBfilepath,cppfilepath):
    TDBdata = load_file(TDBfilepath) #　 全部数据
    all_PHASE = find_PHASEs(TDBdata)  #　全部 phase 已数组形式存储
    file = open(cppfilepath, "a+")
    print('Rewritting PHASE to Cpp funcitons ...')
    for phase in all_PHASE:
        p_name = getPHASE_name(phase)
        allParamList = getParamList(phase[-1])
        paramFunctions = paramToCppFunction(allParamList)  # 这个phase的全部parameter的CPP函数形式
        p_note_start = phase_note_start(phase[0:-1],p_name)
        p_dg_note = phase_dg_note(p_name)
        #  写入 cpp 文件
        file.write(p_note_start)
        file.write(paramFunctions)
        file.write(p_dg_note)
    print('Done !')
    file.close()


# if __name__ == "__main__":
    # TDBfilepath='XTPowerAndHeating/AL-NI-Thermo-data(TDB).txt'
    # cppfilepath='XTPowerAndHeating/AL-NI(h).cpp'

