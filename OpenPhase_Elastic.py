# -*- coding=utf-8 -*-
# author : gq    2018-11-08

OUTCAR_path = 'VASP/OUTCAR'
ElasticInput_path = 'MultigrainPlasticity/ProjectInput/ElasticInput.opi'
# ElasticInput_path = 'test_gq'
print('Loading data ...')
# 加载文件
OUTCAR_texts = open(OUTCAR_path,encoding='utf-8').read().split('\n')
ElasticInput_texts = open(ElasticInput_path,encoding='utf-8').read().split('\n')

# 数据处理
def data_process():
    tag = 'SYMMETRIZED ELASTIC MODULI (kBar)'
    symModuli = []
    for index,line in enumerate(OUTCAR_texts):  # 1.txt是需要分词统计的文档
        # item = line.strip('\n\r').split('\t')  # 制表格切分
        if(line.find(tag) != -1):
            symModuli=OUTCAR_texts[index+3:index+9]

    # 取出矩阵中的数字
    MODULI_mat = []
    for line in  symModuli:
        tmpList = []
        tmp = ''
        for index,word in enumerate(line):
            if(word != ' '):
               tmp = tmp+word
            if (tmp != '' and ( index == len(line) - 1 or word == ' ')):
                tmpList.append(tmp)
                tmp = ''
        if(len(tmpList)!=0):
            tmpList = [round(float(x)*0.1,2) for x in tmpList[1:]]
            print(tmpList)
            MODULI_mat.append(tmpList)

    phase_mat = []
    for index,num in enumerate(MODULI_mat):
        tmp = '$C'+str(index+1)+str(index+1)+" "+str(MODULI_mat[index][index])+"e9"
        phase_mat.append(tmp)
        if(index==2):
            tmp = '$C12'+" "+ str(MODULI_mat[0][1]) + "e9"
            tmp = tmp+'\n'+'$C13'+ " " + str(MODULI_mat[0][2]) + "e9"
            tmp = tmp + '\n' + '$C23'+ " " + str(MODULI_mat[1][2]) + "e9"
            phase_mat.append(tmp)
    # print(phase_mat)

    Elastic_output = []
    isSavaTag=0
    for line in ElasticInput_texts:
        if(line.find('$C') != -1):
            if(isSavaTag == 0):
                Elastic_output = Elastic_output+phase_mat
                isSavaTag = 1
        else:
            isSavaTag = 0
            Elastic_output.append(line)
    return  Elastic_output

# 保存
def save2file(textList, filename):
    print('Save to ElasticInput.opi ...')
    file = open(filename, "w")
    for index,line in enumerate(textList):
        if(index != len(textList)-1):
            line = line+"\n"
        file.write(line)
    file.close()
    print('Done!')


if __name__ == "__main__":
    Elastic_output = data_process()
    save2file(Elastic_output, ElasticInput_path)
