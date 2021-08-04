#include "filesystem.h"

FILESYSTEM::FILESYSTEM(){

}

void FILESYSTEM::spiffsInfo(){
  FSInfo fs_info;
  SPIFFS.begin();       //启动SPIFFS
  Serial.println("");
  Serial.println("SPIFFS Started.");
 
  // 闪存文件系统信息
  SPIFFS.info(fs_info);
 
  // 可用空间总和（单位：字节）
  Serial.print("totalBytes: ");     
  Serial.print(fs_info.totalBytes); 
  Serial.println(" Bytes"); 
 
  // 已用空间（单位：字节）
  Serial.print("usedBytes: "); 
  Serial.print(fs_info.usedBytes);
  Serial.println(" Bytes"); 
 
  // 最大文件名字符限制（含路径和'\0'）
  Serial.print("maxPathLength: "); 
  Serial.println(fs_info.maxPathLength);
 
  // 最多允许打开文件数量
  Serial.print("maxOpenFiles: "); 
  Serial.println(fs_info.maxOpenFiles);
 
  // 存储块大小
  Serial.print("blockSize: "); 
  Serial.println(fs_info.blockSize);
 
  // 存储页大小
  Serial.print("pageSize: ");
  Serial.println(fs_info.pageSize);
}

//删除文件，成功返回1，失败返回0
int FILESYSTEM::spiffsRemove(String filename){
  spiffsInit();
  if (SPIFFS.remove(filename)){
    Serial.print(filename);
    Serial.println(" remove sucess");
    return 1;
  } else {
    Serial.print(filename);
    Serial.println(" remove fail");
    return 0;
  }                       
}

//写入文件，成功返回1，失败返回0
int FILESYSTEM::spiffsWrite(String filename,String data){
  spiffsInit();
  if(SPIFFS.begin()){ // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }
  File dataFile = SPIFFS.open(filename, "w+"); // 建立File对象用于向SPIFFS中的file对象（即myFile.txt）写入信息
  dataFile.println(data);    // 向dataFile写入字符串信息
  dataFile.close();                           // 完成文件写入后关闭文件
  return 1;
}

//追加写入文件，成功返回1，失败返回0
int FILESYSTEM::spiffsAddWrite(String filename,String data){
  spiffsInit();
  if(SPIFFS.begin()){ // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  } else {
    Serial.println("SPIFFS Failed to Start.");
  }
  File dataFile = SPIFFS.open(filename, "a"); // 建立File对象用于向SPIFFS中的file对象（即myFile.txt）写入信息
  dataFile.println(data);    // 向dataFile写入字符串信息
  dataFile.close();                           // 完成文件写入后关闭文件
  return 1;
}

//确认是否有某个文件，成功返回1，失败返回0 
int FILESYSTEM::spiffsConfirm(String filename){
  spiffsInit();
  if (SPIFFS.exists(filename)){
    Serial.print(filename);
    Serial.println(" FOUND.");
    return 1;
  } else {
    Serial.print(filename);
    Serial.print(" NOT FOUND.");
    return 0;
  }
}

//只读形式打开文件，返回读取的内容
String FILESYSTEM::spiffsRead(String filename){
  File myFile;
  String data;
  spiffsInit();
  myFile = SPIFFS.open(filename,"r");
  if(myFile){
    Serial.println("Reading : "+filename);
  while(myFile.available()){
    //读取文件输出
  for(int i=0; i<myFile.size(); i++){
    data +=((char)myFile.read());       
  }
  }
  myFile.close();
  }else{
    Serial.println("Open File Failed.");
  }
  return data;
}

//格式化文件系统
int FILESYSTEM::spiffsFormat(){
  spiffsInit();
  if(SPIFFS.format()){
    return 1;
  }else{
    return 0;
  }
}

void FILESYSTEM::spiffsInit(){
    SPIFFS.begin();
}

