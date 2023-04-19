#include <iostream>
#include <stdio.h>
#include <string.h>
#include "curl/curl.h"
#include <unistd.h> //延时函数
#include <time.h>


#ifndef __APPLE__
#  include "HalconCpp.h"
#  include "HDevThread.h"
#  if defined(__linux__) && (defined(__i386__) || defined(__x86_64__)) \
                         && !defined(NO_EXPORT_APP_MAIN)
#    include <X11/Xlib.h>
#  endif
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCONCpp/HalconCpp.h>
#    include <HALCONCpp/HDevThread.h>
#    include <HALCON/HpThread.h>
#  else
#    include <HALCONCppxl/HalconCpp.h>
#    include <HALCONCppxl/HDevThread.h>
#    include <HALCONxl/HpThread.h>
#  endif
#  include <stdio.h>
#  include <CoreFoundation/CFRunLoop.h>
#endif



using namespace HalconCpp;

using namespace std;
void function(void);
void motion_method(int method);
CURL* curl;
CURLcode res;

//直走
const char* zhanli1=(char*)"{\"runtime\":600,\"angles\":{   \"RightHipLR\":90,\"RightHipFB\":85,\"RightKneeFlex\":120,\"RightAnkleFB\":90,\"RightAnkleUD\":94,\"LeftHipLR\":90,\"LeftHipFB\":95,\"LeftKneeFlex\":60,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 

const char* taizuojiao1=(char*)"{\"runtime\":500,\"angles\":{   \"RightHipLR\":90,\"RightHipFB\":100,\"RightKneeFlex\":130,\"RightAnkleFB\":95,\"RightAnkleUD\":78,\"LeftHipLR\":98,\"LeftHipFB\":80,\"LeftKneeFlex\":65,\"LeftAnkleFB\":78,\"LeftAnkleUD\":72,\"RightShoulderRoll\":80,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* taizuojiao2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":90,\"RightHipFB\":93,\"RightKneeFlex\":130,\"RightAnkleFB\":88,\"RightAnkleUD\":80,\"LeftHipLR\":99,\"LeftHipFB\":120,\"LeftKneeFlex\":60,\"LeftAnkleFB\":113,\"LeftAnkleUD\":75,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* taizuojiao3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":100,\"RightHipFB\":120,\"RightKneeFlex\":110,\"RightAnkleFB\":115,\"RightAnkleUD\":80,\"LeftHipLR\":102,\"LeftHipFB\":120,\"LeftKneeFlex\":70,\"LeftAnkleFB\":123,\"LeftAnkleUD\":82,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 

const char* fangzuojiao=(char*)"{\"runtime\":600,\"angles\":{    \"RightHipLR\":100,\"RightHipFB\":105,\"RightKneeFlex\":110,\"RightAnkleFB\":123,\"RightAnkleUD\":88,\"LeftHipLR\":95,\"LeftHipFB\":130,\"LeftKneeFlex\":60,\"LeftAnkleFB\":125,\"LeftAnkleUD\":88,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* huanzhongxin1=(char*)"{\"runtime\":600,\"angles\":{ \"RightHipLR\":100,\"RightHipFB\":105,\"RightKneeFlex\":110,\"RightAnkleFB\":120,\"RightAnkleUD\":95,\"LeftHipLR\":97,\"LeftHipFB\":130,\"LeftKneeFlex\":60,\"LeftAnkleFB\":125,\"LeftAnkleUD\":95,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";
const char* zuojiaozhunbei1=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":98,\"RightHipFB\":105,\"RightKneeFlex\":125,\"RightAnkleFB\":120,\"RightAnkleUD\":95,\"LeftHipLR\":97,\"LeftHipFB\":160,\"LeftKneeFlex\":100,\"LeftAnkleFB\":98,\"LeftAnkleUD\":95,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           
const char* zuojiaozhunbei2=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":82,\"RightHipFB\":105,\"RightKneeFlex\":130,\"RightAnkleFB\":110,\"RightAnkleUD\":102,\"LeftHipLR\":90,\"LeftHipFB\":115,\"LeftKneeFlex\":60,\"LeftAnkleFB\":98,\"LeftAnkleUD\":102,\"RightShoulderRoll\":70,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":79,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           

const char* taiyoujiao1=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":82,\"RightHipFB\":50,\"RightKneeFlex\":90,\"RightAnkleFB\":90,\"RightAnkleUD\":105,\"LeftHipLR\":90,\"LeftHipFB\":105,\"LeftKneeFlex\":60,\"LeftAnkleFB\":98,\"LeftAnkleUD\":103,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":95,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* taiyoujiao2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":84,\"RightHipFB\":70,\"RightKneeFlex\":125,\"RightAnkleFB\":60,\"RightAnkleUD\":105,\"LeftHipLR\":90,\"LeftHipFB\":80,\"LeftKneeFlex\":90,\"LeftAnkleFB\":62,\"LeftAnkleUD\":100,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":109,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* taiyoujiao3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":84,\"RightHipFB\":72,\"RightKneeFlex\":145,\"RightAnkleFB\":42,\"RightAnkleUD\":102,\"LeftHipLR\":86,\"LeftHipFB\":70,\"LeftKneeFlex\":85,\"LeftAnkleFB\":58,\"LeftAnkleUD\":102,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":99,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         

const char* fangyoujiao=(char*)"{\"runtime\":600,\"angles\":{    \"RightHipLR\":90,\"RightHipFB\":70,\"RightKneeFlex\":155,\"RightAnkleFB\":44,\"RightAnkleUD\":93,\"LeftHipLR\":88,\"LeftHipFB\":65,\"LeftKneeFlex\":70,\"LeftAnkleFB\":48,\"LeftAnkleUD\":93,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":99,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* huanzhongxin2=(char*)"{\"runtime\":600,\"angles\":{ \"RightHipLR\":92,\"RightHipFB\":70,\"RightKneeFlex\":155,\"RightAnkleFB\":44,\"RightAnkleUD\":85,\"LeftHipLR\":88,\"LeftHipFB\":65,\"LeftKneeFlex\":70,\"LeftAnkleFB\":48,\"LeftAnkleUD\":87,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":99,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";          
const char* youjiaozhunbei=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":90,\"RightHipFB\":55,\"RightKneeFlex\":135,\"RightAnkleFB\":65,\"RightAnkleUD\":80,\"LeftHipLR\":97,\"LeftHipFB\":60,\"LeftKneeFlex\":30,\"LeftAnkleFB\":75,\"LeftAnkleUD\":75,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";

//左右转

const char* xiangyouzhuan1=(char*)"{\"runtime\":600,\"angles\":{ \"RightHipLR\":88,\"RightHipFB\":80,\"RightKneeFlex\":105,\"RightAnkleFB\":103,\"RightAnkleUD\":100,\"LeftHipLR\":94,\"LeftHipFB\":100,\"LeftKneeFlex\":55,\"LeftAnkleFB\":94,\"LeftAnkleUD\":99,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* xiangyouzhuan2=(char*)"{\"runtime\":300,\"angles\":{ \"RightHipLR\":88,\"RightHipFB\":80,\"RightKneeFlex\":105,\"RightAnkleFB\":98,\"RightAnkleUD\":97,\"LeftHipLR\":94,\"LeftHipFB\":100,\"LeftKneeFlex\":55,\"LeftAnkleFB\":94,\"LeftAnkleUD\":99,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";
const char* xiangyouzhuan3=(char*)"{\"runtime\":800,\"angles\":{\"RightHipLR\":90,\"RightHipFB\":85,\"RightKneeFlex\":120,\"RightAnkleFB\":90,\"RightAnkleUD\":94,\"LeftHipLR\":90,\"LeftHipFB\":95,\"LeftKneeFlex\":60,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           
const char* xiangyouzhuan4=(char*)"{\"runtime\":600,\"angles\":{\"RightHipLR\":90,\"RightHipFB\":85,\"RightKneeFlex\":120,\"RightAnkleFB\":90,\"RightAnkleUD\":94,\"LeftHipLR\":90,\"LeftHipFB\":95,\"LeftKneeFlex\":60,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           

/*
const char* xiangzuozhuan1=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":94,\"RightAnkleUD\":81,\"LeftHipLR\":92,\"LeftHipFB\":76,\"LeftKneeFlex\":58,\"LeftAnkleFB\":83,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":93,\"RightAnkleUD\":81,\"LeftHipLR\":92,\"LeftHipFB\":89,\"LeftKneeFlex\":70,\"LeftAnkleFB\":90,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":93,\"RightAnkleUD\":85,\"LeftHipLR\":91,\"LeftHipFB\":89,\"LeftKneeFlex\":70,\"LeftAnkleFB\":94,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan4=(char*)"{\"runtime\":700,\"angles\":{    \"RightHipLR\":89,\"RightHipFB\":84,\"RightKneeFlex\":120,\"RightAnkleFB\":91,\"RightAnkleUD\":94,\"LeftHipLR\":91,\"LeftHipFB\":94,\"LeftKneeFlex\":58,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
//const char* xiangzuozhuan4=(char*)"{\"runtime\":600,\"angles\":{   \"RightHipLR\":90,\"RightHipFB\":85,\"RightKneeFlex\":120,\"RightAnkleFB\":90,\"RightAnkleUD\":94,\"LeftHipLR\":90,\"LeftHipFB\":95,\"LeftKneeFlex\":60,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
*/
const char* xiangzuozhuan1=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":94,\"RightAnkleUD\":81,\"LeftHipLR\":92,\"LeftHipFB\":76,\"LeftKneeFlex\":58,\"LeftAnkleFB\":83,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":93,\"RightAnkleUD\":81,\"LeftHipLR\":92,\"LeftHipFB\":89,\"LeftKneeFlex\":70,\"LeftAnkleFB\":90,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":75,\"RightKneeFlex\":110,\"RightAnkleFB\":93,\"RightAnkleUD\":85,\"LeftHipLR\":91,\"LeftHipFB\":89,\"LeftKneeFlex\":70,\"LeftAnkleFB\":97,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan4=(char*)"{\"runtime\":500,\"angles\":{    \"RightHipLR\":92,\"RightHipFB\":92,\"RightKneeFlex\":120,\"RightAnkleFB\":91,\"RightAnkleUD\":94,\"LeftHipLR\":91,\"LeftHipFB\":86,\"LeftKneeFlex\":58,\"LeftAnkleFB\":90,\"LeftAnkleUD\":88,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         


int bushu=1;

void Sleep(int ms)
{
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = ms * 1000; // 20 ms
    select(0, NULL, NULL, NULL, &delay);
}

#ifndef NO_EXPORT_MAIN
// Main procedure 
void action()
{
  // Local iconic variables
  HObject  ho_Image, ho_Regions, ho_RegionErosion;
  HObject  ho_RegionLines, ho_RegionIntersection;

  // Local control variables
  HTuple  hv_AcqHandle, hv_Width, hv_Height, hv_WindowHandle;
  HTuple  hv_Area, hv_Row, hv_Column, hv_Distance;

  //Image Acquisition 01: Code generated by Image Acquisition 01
  OpenFramegrabber("Video4Linux2", 4, 4, 0, 0, 0, 0, "progressive", 8, "default", 
      -1, "false", "auto", "video0", 0, -1, &hv_AcqHandle);
  GrabImage(&ho_Image, hv_AcqHandle);
  GetImageSize(ho_Image, &hv_Width, &hv_Height);
  SetWindowAttr("background_color","black");
  OpenWindow(0,0,hv_Width,hv_Height,0,"visible","",&hv_WindowHandle);
  HDevWindowStack::Push(hv_WindowHandle);
  while (0 != 1)
  {
    GrabImage(&ho_Image, hv_AcqHandle);
    //Image Acquisition 01: Do something
    Threshold(ho_Image, &ho_Regions, 0, 40);
    ErosionCircle(ho_Regions, &ho_RegionErosion, 5);
    GenRegionLine(&ho_RegionLines, 150, 300, 150, 720);
    Intersection(ho_RegionErosion, ho_RegionLines, &ho_RegionIntersection);
    AreaCenter(ho_RegionIntersection, &hv_Area, &hv_Row, &hv_Column);
    DistancePp(150, hv_Column, 150, 0, &hv_Distance);
    if (HDevWindowStack::IsOpen())
      ClearWindow(HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      DispObj(ho_RegionLines, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      DispObj(ho_RegionErosion, HDevWindowStack::GetActive());
      
    double juli=hv_Distance.D();
    std::cout << "Distance:" << juli << std::endl;

    if(juli>440&&juli<650)
    {
      curl=curl_easy_init();
      motion_method(1);
      curl_easy_cleanup(curl); 
    }
    
    else if(juli<=440)
    {
      curl=curl_easy_init();
      motion_method(2);
      curl_easy_cleanup(curl); 
    }
    
    else if(juli>=650)
    {
      curl=curl_easy_init();
      motion_method(3);
      curl_easy_cleanup(curl); 
    }
  }
  CloseFramegrabber(hv_AcqHandle); 
}


#ifndef NO_EXPORT_APP_MAIN

#ifdef __APPLE__
// On OS X systems, we must have a CFRunLoop running on the main thread in
// order for the HALCON graphics operators to work correctly, and run the
// action function in a separate thread. A CFRunLoopTimer is used to make sure
// the action function is not called before the CFRunLoop is running.
// Note that starting with macOS 10.12, the run loop may be stopped when a
// window is closed, so we need to put the call to CFRunLoopRun() into a loop
// of its own.
HTuple      gStartMutex;
H_pthread_t gActionThread;
HBOOL       gTerminate = FALSE;

static void timer_callback(CFRunLoopTimerRef timer, void *info)
{
  UnlockMutex(gStartMutex);
}

static Herror apple_action(void **parameters)
{
  // Wait until the timer has fired to start processing.
  LockMutex(gStartMutex);
  UnlockMutex(gStartMutex);

  try
  {
    action();
  }
  catch (HException &exception)
  {
    fprintf(stderr,"  Error #%u in %s: %s\n", exception.ErrorCode(),
            exception.ProcName().TextA(),
            exception.ErrorMessage().TextA());
  }

  // Tell the main thread to terminate itself.
  LockMutex(gStartMutex);
  gTerminate = TRUE;
  UnlockMutex(gStartMutex);
  CFRunLoopStop(CFRunLoopGetMain());
  return H_MSG_OK;
}

static int apple_main(int argc, char *argv[])
{
  Herror                error;
  CFRunLoopTimerRef     Timer;
  CFRunLoopTimerContext TimerContext = { 0, 0, 0, 0, 0 };

  CreateMutex("type","sleep",&gStartMutex);
  LockMutex(gStartMutex);

  error = HpThreadHandleAlloc(&gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleAlloc failed: %d\n", error);
    exit(1);
  }

  error = HpThreadCreate(gActionThread,0,apple_action);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadCreate failed: %d\n", error);
    exit(1);
  }

  Timer = CFRunLoopTimerCreate(kCFAllocatorDefault,
                               CFAbsoluteTimeGetCurrent(),0,0,0,
                               timer_callback,&TimerContext);
  if (!Timer)
  {
    fprintf(stderr,"CFRunLoopTimerCreate failed\n");
    exit(1);
  }
  CFRunLoopAddTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);

  for (;;)
  {
    HBOOL terminate;

    CFRunLoopRun();

    LockMutex(gStartMutex);
    terminate = gTerminate;
    UnlockMutex(gStartMutex);

    if (terminate)
      break;
  }

  CFRunLoopRemoveTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);
  CFRelease(Timer);

  error = HpThreadHandleFree(gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleFree failed: %d\n", error);
    exit(1);
  }

  ClearMutex(gStartMutex);
  return 0;
}
#endif


void function(void)
{
		curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);//print debug info 
		struct curl_slist * slist=0;
		slist=curl_slist_append(slist,"content-Type: application/json"); 
		slist=curl_slist_append(slist,"Accept: application/json"); 
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);//set httpheader 
		res=curl_easy_perform(curl);//do put request 
}



void motion_method(int method)
{
	void function(void);
	if(curl)
	{  
		//确保网络传输对象正常返回一个句柄
		curl_easy_setopt(curl, CURLOPT_URL,"http://127.0.0.1:9090/v1/servos/angles");//set url 
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST,"PUT");
		
		if(bushu)
		{
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zhanli1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zhanli1)); 
		function();
		Sleep(1000);
                //姿态1
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		Sleep(200);
		//姿态2
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao2)); 
		function();
		//姿态3
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao3)); 
		function();
		Sleep(200);
		//姿态4
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fangzuojiao);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fangzuojiao)); 
		function();
		Sleep(200);
		//姿态5
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, huanzhongxin1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(huanzhongxin1)); 
		function();
		Sleep(100);
		//姿态6
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zuojiaozhunbei1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zuojiaozhunbei1)); 
		function();
		Sleep(200);
		//姿态7
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zuojiaozhunbei2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zuojiaozhunbei2)); 
		function();
		Sleep(200);
		//姿态8
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao1));
		function();
		Sleep(200);
		//姿态9
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao2));
		function();
		Sleep(100);
		//姿态10
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao3));
		function();
		Sleep(100);
		//姿态11
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fangyoujiao);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fangyoujiao)); 
		function();
		Sleep(200);
		//姿态12
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, huanzhongxin2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(huanzhongxin2)); 
		function();
		Sleep(200);
		//姿态13
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, youjiaozhunbei);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(youjiaozhunbei));
		function();
		Sleep(300);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		Sleep(300);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan1)); 
		function();
		Sleep(100);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan2)); 
		function();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan3)); 
		function();
		Sleep(400);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan4)); 
		function();
		Sleep(300);
		
		bushu--;
		}
	      
		if(method==1)//执行直走的代码
		{
		//姿态1
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		Sleep(200);
		//姿态2
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao2)); 
		function();
		//姿态3
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao3)); 
		function();
		Sleep(200);
		//姿态4
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fangzuojiao);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fangzuojiao)); 
		function();
		Sleep(200);
		//姿态5
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, huanzhongxin1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(huanzhongxin1)); 
		function();
		Sleep(100);
		//姿态6
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zuojiaozhunbei1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zuojiaozhunbei1)); 
		function();
		Sleep(200);
		//姿态7
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zuojiaozhunbei2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zuojiaozhunbei2)); 
		function();
		Sleep(200);
		//姿态8
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao1));
		function();
		Sleep(200);
		//姿态9
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao2));
		function();
		Sleep(100);
		//姿态10
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao3));
		function();
		Sleep(100);
		//姿态11
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fangyoujiao);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fangyoujiao)); 
		function();
		Sleep(200);
		//姿态12
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, huanzhongxin2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(huanzhongxin2)); 
		function();
		Sleep(200);
		//姿态13
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, youjiaozhunbei);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(youjiaozhunbei));
		function();
		Sleep(300);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		}
		
		else if(method==2)//左转
		{
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		Sleep(300);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan1)); 
		function();
		Sleep(100);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan2)); 
		function();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan3)); 
		function();
		Sleep(200);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan4)); 
		function();
		Sleep(300);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zhanli1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zhanli1)); 
		function();
		}
		else if(method==3)//右转
		{
		Sleep(200);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan3)); 
		function();
		Sleep(200);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan1)); 
		function();
		Sleep(200);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan2)); 
		function();
		Sleep(200);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan4)); 
		function();
		Sleep(300);
		}
	  }
}



int main(int argc, char *argv[])
{
  curl=curl_easy_init();
  
  int ret = 0;

  try
  {
#if defined(_WIN32)
    SetSystem("use_window_thread", "true");
#elif defined(__linux__) && (defined(__i386__) || defined(__x86_64__))
    XInitThreads();
#endif

    // file was stored with local-8-bit encoding
    //   -> set the interface encoding accordingly
    SetHcppInterfaceStringEncodingIsUtf8(false);

    // Default settings used in HDevelop (can be omitted)
    SetSystem("width", 512);
    SetSystem("height", 512);

#ifndef __APPLE__
    action();
#else
    ret = apple_main(argc,argv);
#endif
  }
  catch (HException &exception)
  {
    fprintf(stderr,"  Error #%u in %s: %s\n", exception.ErrorCode(),
            exception.ProcName().TextA(),
            exception.ErrorMessage().TextA());
    ret = 1;
  }
  return ret;
}

#endif


#endif


