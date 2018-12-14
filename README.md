# 用python实现材料模拟计算中多软件间文件转换
**背景：**
材料模拟计算过程中涉及到多个仿真软件，但由于这多个软件是由不同软件开发商提供，软件的仿真输入与输出结果的文件格式不统一。
通常情况下，做一次材料性能模拟需要以手工的形式从前置软件的仿真结果中抽取所需要的数据，组装成后置软件仿真所需要的输入文件，耗费大量的人力物力。
材料模拟计算过程中，多软件间文件转换系统可以替代传统人工处理的工作，快速将软件之间的过程文件进行转换，极大提高了材料性能模拟的效率，并为实现基因材料模拟自动化流程提供了必要的条件。

## 1, VASP计算弹性常数

**输入**：VASP是第一步软件，所以它在两步骤中所需要的四个文件（都是INCAR、KPOINTS、POSCAR、POTCAR这四个文件，但是文件的具体内容不一样）都是用户的初始输入，不需要做处理。

**输出**：OUTCAR

**说明**计算计算弹性常数时，将结构弛豫中的INCAR复制的相应的文件夹并修改相应的参数

**运行程序** ```python  change_incar_JGtoTX.py  ```


## 2, OpenPhase 计算多晶应力应变曲线

**说明**：需要弹性常数，从VASP的弹性常数计算结果的输出文件OUTCAR 里，读出弹性常数的数值，写入到OpenPhase运算目录MultigrainPlasticity目录的子目录ProjectInput下的ElasticInput.opi文件中

**运行程序**  ```python  OpenPhase_Elastic.py  ```

## 3，TDB转换为h文件

  ``` XTPowerAndHeating ```  包含TDB文件，cpp文件的生成目录
    
   ```  change_TDB_FUNCTION_to_Cpp.py ```   生成 cpp 头文件，提取 function 到 cpp 文件中
   
   ```  change_TDB_PHASE_to_Cpp.py  ```        提取 phase 的信息到 cpp 文件中（导数及公式部分暂未完成）
   

**运行程序**  ```python  TDB_TO_CPP/TDB_to_Cpp.py  ```
