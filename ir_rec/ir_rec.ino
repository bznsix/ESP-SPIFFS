/*
 * @Author: your name
 * @Date: 2021-08-02 15:30:27
 * @LastEditTime: 2021-08-03 16:54:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ir_rec\ir_rec.ino
 */

#include <assert.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>
#include "src/StringManage/StringManage.h"
#include "src/FileSystem/filesystem.h"
STRINGMANAGE stringmanage;
const uint16_t kRecvPin = 14;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;  // kTolerance is normally 25%
#define LEGACY_TIMING_INFO false

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
String dumpCode(decode_results *results) {
  String s;
  s = "uint16_t rawData["\
  + String(results->rawlen - 1,DEC) \
  + "] = {";
  for (uint16_t i = 1; i < results->rawlen; i++) {
    s += String(results->rawbuf[i] * kRawTick, DEC);
    if (i < results->rawlen - 1)
      s += ",";  // ',' not needed on last one
  }
  s += "}";
  return s;
}

FILESYSTEM filesystem;
uint16_t *rawdata;
void setup(){
  Serial.begin(115200);
  irrecv.enableIRIn();
}
void loop(){
  decode_results  results;                                        // Somewhere to store the results

  if (irrecv.decode(&results)) {                  // Grab an IR code
    Serial.println("Signal received:");
    String s = dumpCode(&results);                                           // Output the results as source code
    filesystem.spiffsWrite("1",s);
    delay(10);
    String read = filesystem.spiffsRead("1");
    rawdata = (uint16_t *)malloc((stringmanage.countsize(read,',')+1)*2);
    stringmanage.stringToRaw(filesystem.spiffsRead("1"),rawdata);
    Serial.println(*(rawdata+stringmanage.countsize(read,',')));
    Serial.println("");                                           // Blank line between entries
    irrecv.resume();                                              // Prepare for the next value
  }
  delay(200);
}