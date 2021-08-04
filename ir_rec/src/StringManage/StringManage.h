/*
 * @Author: your name
 * @Date: 2021-08-02 16:04:06
 * @LastEditTime: 2021-08-03 16:42:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \8266IrRemote\8266_ir\src\StringManage\StringManage.h
 */
#pragma once
#include <Arduino.h>

class STRINGMANAGE {
  private:
    String printresults(String s);
  public:
    STRINGMANAGE();
    void stringToRaw(String s,uint16 * data);
    String getRaw();
    void IRinit();
    int countsize(String s,char a);
};