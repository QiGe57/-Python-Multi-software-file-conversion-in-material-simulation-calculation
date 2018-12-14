# -*- coding=utf-8 -*-
# author : wangfan    2018-11-08
#计算计算弹性常数时，从将第一步的结构弛豫中的INCAR复制的相应的文件夹并修改相应的参数
import os
import shutil

#复制文件
def mycopyfile(srcfile, dstfile):
    if not os.path.isfile(srcfile):
        print("%s not exist!" % (srcfile))
    else:
        fpath, fname = os.path.split(dstfile)  # 分离文件名和路径
        if not os.path.exists(fpath):
            os.makedirs(fpath)  # 创建路径
        shutil.copyfile(srcfile, dstfile)  # 复制文件
        print("copy %s -> %s" % (srcfile, dstfile))

#修改INCAR文件的内容以满足弹性常数的计算的需求
def change_incar(filepath):
    INCAR_text=open(filepath,encoding='utf-8').read().split("\n")
    NSWindex = ''
    NSWstr=''
    NFREEinsertIndex=''
    for line in INCAR_text:
        #print(line)
        lineList = line.split(" ")
        #print(lineList)
        if lineList[0] == 'NSW':
            changValue('NSW', '100', lineList)
            print(INCAR_text.index(line))
            NSWstr=' '.join(lineList)
            NSWindex=INCAR_text.index(line)
        elif lineList[0] == 'IBRION':
            changValue('IBRION', '6', lineList)
            IBRIONstr=' '.join(lineList)
            INCAR_text[INCAR_text.index(line)] = IBRIONstr;
        elif lineList[0] == 'POTIM':
            NFREEinsertIndex = INCAR_text.index(line);
            changValue('POTIM', '0.01', lineList)
            POTIMstr=' '.join(lineList)
            INCAR_text[INCAR_text.index(line)] = POTIMstr;
        elif lineList[0] == 'ISIF':
            changValue('ISIF', '3', lineList)
            ISIFstr=' '.join(lineList)
            INCAR_text[INCAR_text.index(line)] = ISIFstr;

    INCAR_text[NSWindex+1] = NSWstr;
    INCAR_text[NSWindex] = "";
    NFREEInsertStr="NFREE= 4";
    INCAR_text.insert(NFREEinsertIndex+1,NFREEInsertStr);
    return INCAR_text

#替换行中的值
def changValue(name, value,lineList):
    for linecontent in lineList:
        if (linecontent != '' and linecontent != name and linecontent != '='):
            lineList[lineList.index(linecontent)] = value


# 修改INCAR文件的内容以满足弹性常数的计算的需求
def change_kpoints(filepath):

    KPOINTS_text = open(filepath, encoding='utf-8').read().split("\n")
    KPOINTS_text[3]="21 21 21"
    return KPOINTS_text

#保存文件
def save2file(textList, filename):
    print('Save to',filename)
    file = open(filename, "w")
    for index,line in enumerate(textList):
        if(index != len(textList)-1):
            line = line+"\n"
        file.write(line)
    file.close()
    print('Done!')
#修改
if __name__ == "__main__":
    #修改INCAR的内容
    srcfile_INCAR = 'VASP/first-step/INCAR'
    dstfile_INCAR = 'VASP/second/INCAR'
    INCAR_text=change_incar(srcfile_INCAR)
    save2file(INCAR_text, dstfile_INCAR)
    # 修改KPOINTS的内容
    srcfile_KPOINTS = 'VASP/first-step/KPOINTS'
    dstfile_KPOINTS = 'VASP/second/KPOINTS'
    KPOINTS_text = change_kpoints(srcfile_KPOINTS)
    save2file(KPOINTS_text, dstfile_KPOINTS)
    #将VASP第一步计算的结构弛豫中的CONTCAR文件复制到第二步的弹性常数计算的文件夹下，并改名为POSCAR
    srcfile_CONTCAR = 'VASP/first-step/CONTCAR'
    dstfile_POSCAR = 'VASP/second/POSCAR'
    mycopyfile(srcfile_CONTCAR, dstfile_POSCAR)
    # 将VASP第一步计算的结构弛豫中的POTCAR文件复制到第二步的弹性常数计算的文件夹下
    srcfile_POTCAR = 'VASP/first-step/POTCAR'
    dstfile_POTCAR = 'VASP/second/POTCAR'
    mycopyfile(srcfile_POTCAR, dstfile_POTCAR)