/*
 * @Author: your name
 * @Date: 2021-08-02 16:03:54
 * @LastEditTime: 2021-08-03 16:42:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \8266IrRemote\8266_ir\src\StringManage\StringManage.cpp
 */
#include "StringManage.h"

STRINGMANAGE::STRINGMANAGE(){

}

void STRINGMANAGE::stringToRaw(String s,uint16 * data)
{
  String message = s;
  Serial.print("MESSAGE");
  Serial.print(message);
  int begin,pos,i = 0;
  begin = message.indexOf('{');
  while((message.indexOf(',')) != -1){
    pos = message.indexOf(',');
    if(i == 0)
      *(data + i) = message.substring(begin+1,pos).toInt();
    else
      *(data + i) = message.substring(0,pos).toInt();
    // Serial.print("begin:");
    // Serial.println(begin);
    // Serial.print("pos:");
    // Serial.println(pos);
    // Serial.print("value:");
    // Serial.println(message.substring(0,pos).toInt());
    begin = pos;
    i++;
    message = message.substring(begin+1);
    // Serial.print("i:");
    // Serial.println(i);
    //寻找到最后一个了
    if((message.indexOf(',')) == -1){
      // Serial.print("final message:");
      // Serial.println(message);
      *(data + i) = message.substring(0,message.indexOf('}')).toInt();
    }
  }
}

int STRINGMANAGE::countsize(String str,char a){
    int n=0;
    int i = 0;
    while(str[i]!='\0'){
        if(str[i] == a)
            n++;
        i++;
    }
    return n;
}