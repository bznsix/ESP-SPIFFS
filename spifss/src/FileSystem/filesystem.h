/*
 * @Author: your name
 * @Date: 2021-07-28 14:21:05
 * @LastEditTime: 2021-07-28 14:51:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \spifss\src\FileSystem\filesystem.h
 */
#pragma once
#include<FS.h>


class FILESYSTEM {
  private:
  void spiffsInit();
  public:
    FILESYSTEM();
    void spiffsInfo();
    int spiffsRemove(String filename);
    int spiffsWrite(String filename,String data);
    int spiffsAddWrite(String filename,String data);
    int spiffsConfirm(String filename);
    String spiffsRead(String filename);
    int spiffsFormat();
};