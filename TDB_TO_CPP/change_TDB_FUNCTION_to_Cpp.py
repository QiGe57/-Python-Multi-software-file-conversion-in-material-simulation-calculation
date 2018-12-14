# -*- coding=utf-8 -*-
# author : wangfan    2018-11-20
#function 转换

import re
#生成 .h文件中的头文件
def creat_head(cppfilepath):
    head_str='''#include <vector>
void printerror(double T)
{
    exit(0);
}
const double precision = 1E-6;
const double R = 8.3144521;
double dummy(std::vector<double>& a, double b, double c)
{
    return 0.0;
}'''
    print('Creating head to', cppfilepath)
    file = open(cppfilepath, "w")
    file.write(head_str)
    file.close()
    print('Creating head finished!')



#转化将TDB中的ELEMENT转化为CPP中element
def change_element(TDBfilepath, cppfilepath):
    illustrate_str='''
/**************************************************************************
***************************************************************************
A) Definition of elements
From A. T. Dinsdale, SGTE data for pure elements (REF 0)

***************************************************************************
'''
    file_text = open(TDBfilepath, encoding='utf-8').read().split('\n')
    Elements_Str = ''
    Elements=[]
    haveElement=False
    for line in file_text:
        words = line.split(' ')
        words = list(filter(None, words))
        #print(words)
        if (len(words) > 0 and words[0] == 'ELEMENT' and len(words)==6):
            haveElement = True
            Element=[]
            for i in range (0,6):
                Element.append(words[i])
            Elements.append(Element)
    if(haveElement == True):
        Elements_Str += illustrate_str
        Elements_head='Element        \tStandard     \tstate          \tmass [g/mol]   \tenthalpy_298   \tentropy_298    '
        Elements_Str +=Elements_head
        for Element in Elements:
            Element_str='\n'
            for word in Element:
                if(len(word)<15):
                    for j in range(0,15-len(word)):
                        word+=' '
                Element_str += word+"\t"
            Elements_Str +=Element_str

        Elements_foot ='\n***************************************************************************' \
                       '\nC) Gibbs energy functions' \
                       '\n***************************************************************************' \
                       '\n###########################################################' \
                       '\nSER (Standard elements references)' \
                       '\n###########################################################*/'
        Elements_Str += Elements_foot
        file = open(cppfilepath, "a+")
        file.write(Elements_Str)
        file.close()
        print('Element finished!')


#处理文本文档，以空格和\n将文本文档分割并且去除空格
def preprocess_text(TDBfilepath):
    file_text = open(TDBfilepath, encoding='utf-8').read()
    file_text = re.split('[ \n]', file_text)
    file_text = list(filter(None, file_text))
    return file_text

#找到每个function的起始和终止的位置
def search_function_index(file_text):
    #Fun_index为函数的起始和终止的索引位置，形式为[[Fun1起始位置，Fun1终止位置],[Fun2起始位置，Fun2终止位置],……]
    Fun_indexs=[]
    Fun_num=0
    lastIndex=0
    Fun_index=[]
    #print(file_text)
    for word in file_text:
        if (word == 'FUNCTION'):
            now_index = file_text.index(word,lastIndex,len(file_text))
            Fun_index=[now_index]
        elif(word == '!'):
            Fun_endsign_index= file_text.index(word,lastIndex,len(file_text))
            lastword=file_text[Fun_endsign_index-1]
            if(lastword=='N' and len(Fun_index)==1):
                Fun_index.append(Fun_endsign_index)
                lastIndex=Fun_endsign_index+1
        if(len(Fun_index)==2 and Fun_num==len(Fun_indexs)):
            Fun_indexs.append(Fun_index)
            Fun_index=[]
            Fun_num+=1
    return Fun_indexs
#找到每个function中的Y位置
def findY(function_str):
    Y_index=[]
    star_index = 0
    while star_index<len(function_str):
        if('Y' in function_str[star_index:len(function_str)]):
            now_index = function_str.index('Y', star_index, len(function_str))
            Y_index.append(now_index)
            star_index = now_index+1
        else:
            break
    return Y_index
#将TDB中的Function转化为Cpp中的function
def change_fun_TDB_CPP(function_str):
    length = len(function_str)
    Y_index = findY(function_str)
    #获取相应的分段的坐标
    for i in range(0,len(Y_index)):
        Y_index[i]-=1
    exp_num=[2]+Y_index+[length-2]
    #print(Y_index)
    expindex=0
    if(length<6):
        print("The function is not normative")
    cpp_function_str = '\n\ndouble '+function_str[1]+' (double T) {\n' \
                       '    double val = 0.0;\n' \
                       '    if(T < '+function_str[2]+' or T > '+function_str[length-2]+') { printerror(T); }\n'
    #分段次数
    fenduan_num =len(exp_num)
    for i in range(0,fenduan_num-1):
        cpp_function_str += '    else if(T >= ' + function_str[exp_num[i]] + ' and T < ' + function_str[exp_num[i+1]] + ') {\n'
        cpp_function_str += '        val = '
        for i in range(exp_num[i]+1, exp_num[i+1]):
            cpp_function_str += function_str[i]
        cpp_function_str += ' }\n'

    cpp_function_str +='    return val; }'
    return cpp_function_str

#将TDB中的Function GHSER转化为cpp中的函数
def change_function(TDBfilepath,cppfilepath):
    file_text=preprocess_text(TDBfilepath)
    function_indexs=search_function_index(file_text)
    #print(function_indexs)
    for function_index in function_indexs:
        function_str=file_text[function_index[0]:function_index[1]]
        #print(function_str)
        if(function_str[1][0:5]=='GHSER'):
            cpp_function_str=change_fun_TDB_CPP(function_str)
            file = open(cppfilepath, "a+")
            file.write(cpp_function_str)
            file.close()
    str='\n\n/*******************************************************\n' \
        '                        FUNCTIONS\n' \
        '********************************************************/'
    file = open(cppfilepath, "a+")
    file.write(str)
    file.close()
    for function_index in function_indexs:
        function_str = file_text[function_index[0]:function_index[1]]
        #print(function_str)
        if (function_str[1][0:5] != 'GHSER'):
            cpp_function_str = change_fun_TDB_CPP(function_str)
            file = open(cppfilepath, "a+")
            file.write(cpp_function_str)
            file.close()
    print('Function is transformed')


#读取AL-NI-Thermo-data(TDB).txt文件转化为AL-NI(h).cpp
def functionToCpp(TDBfilepath, cppfilepath):
    creat_head(cppfilepath)
    change_element(TDBfilepath, cppfilepath)
    change_function(TDBfilepath, cppfilepath)







# if __name__ == "__main__":
#     TDBfilepath='XTPowerAndHeating/AL-NI-Thermo-data(TDB).txt'
#     cppfilepath='XTPowerAndHeating/AL-NI(h).cpp'
#     change_TDB_to_cpp(TDBfilepath, cppfilepath)
#     change_function(TDBfilepath, cppfilepath)