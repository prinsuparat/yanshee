#include <iostream>
#include<stdio.h>
#include<string.h>
#include"curl/curl.h"
#include <unistd.h> //延时函数



using namespace std;
void function(void);
void motion_method(int method);
CURL* curl;
CURLcode res;

//直走
const char* zhanli1=(char*)"{\"runtime\":600,\"angles\":{   \"RightHipLR\":90,\"RightHipFB\":85,\"RightKneeFlex\":120,\"RightAnkleFB\":90,\"RightAnkleUD\":94,\"LeftHipLR\":90,\"LeftHipFB\":95,\"LeftKneeFlex\":60,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 

const char* taizuojiao1=(char*)"{\"runtime\":300,\"angles\":{   \"RightHipLR\":90,\"RightHipFB\":100,\"RightKneeFlex\":130,\"RightAnkleFB\":95,\"RightAnkleUD\":78,\"LeftHipLR\":98,\"LeftHipFB\":80,\"LeftKneeFlex\":65,\"LeftAnkleFB\":78,\"LeftAnkleUD\":72,\"RightShoulderRoll\":80,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* taizuojiao2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":90,\"RightHipFB\":93,\"RightKneeFlex\":130,\"RightAnkleFB\":88,\"RightAnkleUD\":80,\"LeftHipLR\":99,\"LeftHipFB\":120,\"LeftKneeFlex\":60,\"LeftAnkleFB\":113,\"LeftAnkleUD\":75,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* taizuojiao3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":100,\"RightHipFB\":120,\"RightKneeFlex\":110,\"RightAnkleFB\":115,\"RightAnkleUD\":80,\"LeftHipLR\":102,\"LeftHipFB\":120,\"LeftKneeFlex\":70,\"LeftAnkleFB\":123,\"LeftAnkleUD\":82,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 

const char* fangzuojiao=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":100,\"RightHipFB\":105,\"RightKneeFlex\":110,\"RightAnkleFB\":123,\"RightAnkleUD\":88,\"LeftHipLR\":95,\"LeftHipFB\":130,\"LeftKneeFlex\":60,\"LeftAnkleFB\":125,\"LeftAnkleUD\":88,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* huanzhongxin1=(char*)"{\"runtime\":300,\"angles\":{ \"RightHipLR\":100,\"RightHipFB\":105,\"RightKneeFlex\":110,\"RightAnkleFB\":120,\"RightAnkleUD\":95,\"LeftHipLR\":97,\"LeftHipFB\":130,\"LeftKneeFlex\":60,\"LeftAnkleFB\":125,\"LeftAnkleUD\":95,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";
const char* zuojiaozhunbei1=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":98,\"RightHipFB\":105,\"RightKneeFlex\":125,\"RightAnkleFB\":120,\"RightAnkleUD\":95,\"LeftHipLR\":97,\"LeftHipFB\":160,\"LeftKneeFlex\":100,\"LeftAnkleFB\":98,\"LeftAnkleUD\":95,\"RightShoulderRoll\":60,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":59,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           
const char* zuojiaozhunbei2=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":82,\"RightHipFB\":105,\"RightKneeFlex\":130,\"RightAnkleFB\":110,\"RightAnkleUD\":102,\"LeftHipLR\":90,\"LeftHipFB\":115,\"LeftKneeFlex\":60,\"LeftAnkleFB\":98,\"LeftAnkleUD\":102,\"RightShoulderRoll\":70,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":79,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           

const char* taiyoujiao1=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":82,\"RightHipFB\":50,\"RightKneeFlex\":90,\"RightAnkleFB\":90,\"RightAnkleUD\":105,\"LeftHipLR\":90,\"LeftHipFB\":105,\"LeftKneeFlex\":60,\"LeftAnkleFB\":98,\"LeftAnkleUD\":103,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":95,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* taiyoujiao2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":84,\"RightHipFB\":70,\"RightKneeFlex\":125,\"RightAnkleFB\":60,\"RightAnkleUD\":105,\"LeftHipLR\":90,\"LeftHipFB\":80,\"LeftKneeFlex\":90,\"LeftAnkleFB\":62,\"LeftAnkleUD\":100,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":109,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* taiyoujiao3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":84,\"RightHipFB\":72,\"RightKneeFlex\":145,\"RightAnkleFB\":42,\"RightAnkleUD\":102,\"LeftHipLR\":86,\"LeftHipFB\":70,\"LeftKneeFlex\":85,\"LeftAnkleFB\":58,\"LeftAnkleUD\":102,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":99,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         

const char* fangyoujiao=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":90,\"RightHipFB\":70,\"RightKneeFlex\":155,\"RightAnkleFB\":44,\"RightAnkleUD\":93,\"LeftHipLR\":88,\"LeftHipFB\":65,\"LeftKneeFlex\":70,\"LeftAnkleFB\":48,\"LeftAnkleUD\":93,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":99,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* huanzhongxin2=(char*)"{\"runtime\":300,\"angles\":{ \"RightHipLR\":92,\"RightHipFB\":70,\"RightKneeFlex\":155,\"RightAnkleFB\":44,\"RightAnkleUD\":85,\"LeftHipLR\":88,\"LeftHipFB\":65,\"LeftKneeFlex\":70,\"LeftAnkleFB\":48,\"LeftAnkleUD\":87,\"RightShoulderRoll\":110,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":99,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";          
const char* youjiaozhunbei=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":90,\"RightHipFB\":55,\"RightKneeFlex\":135,\"RightAnkleFB\":65,\"RightAnkleUD\":80,\"LeftHipLR\":97,\"LeftHipFB\":60,\"LeftKneeFlex\":30,\"LeftAnkleFB\":75,\"LeftAnkleUD\":75,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";

//左右转

const char* xiangyouzhuan1=(char*)"{\"runtime\":300,\"angles\":{ \"RightHipLR\":85,\"RightHipFB\":108,\"RightKneeFlex\":130,\"RightAnkleFB\":100,\"RightAnkleUD\":97,\"LeftHipLR\":94,\"LeftHipFB\":110,\"LeftKneeFlex\":55,\"LeftAnkleFB\":94,\"LeftAnkleUD\":101,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}"; 
const char* xiangyouzhuan2=(char*)"{\"runtime\":300,\"angles\":{ \"RightHipLR\":85,\"RightHipFB\":108,\"RightKneeFlex\":130,\"RightAnkleFB\":95,\"RightAnkleUD\":97,\"LeftHipLR\":94,\"LeftHipFB\":100,\"LeftKneeFlex\":55,\"LeftAnkleFB\":94,\"LeftAnkleUD\":101,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";
const char* xiangyouzhuan3=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":85,\"RightHipFB\":80,\"RightKneeFlex\":102,\"RightAnkleFB\":89,\"RightAnkleUD\":97,\"LeftHipLR\":94,\"LeftHipFB\":97,\"LeftKneeFlex\":55,\"LeftAnkleFB\":94,\"LeftAnkleUD\":90，\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           
const char* xiangyouzhuan4=(char*)"{\"runtime\":500,\"angles\":{\"RightHipLR\":89,\"RightHipFB\":84,\"RightKneeFlex\":120,\"RightAnkleFB\":91,\"RightAnkleUD\":92,\"LeftHipLR\":91,\"LeftHipFB\":94,\"LeftKneeFlex\":58,\"LeftAnkleFB\":90,\"LeftAnkleUD\":88,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";           

const char* xiangzuozhuan1=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":94,\"RightAnkleUD\":81,\"LeftHipLR\":92,\"LeftHipFB\":76,\"LeftKneeFlex\":58,\"LeftAnkleFB\":83,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan2=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":93,\"RightAnkleUD\":81,\"LeftHipLR\":92,\"LeftHipFB\":89,\"LeftKneeFlex\":70,\"LeftAnkleFB\":90,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan3=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":85,\"RightHipFB\":74,\"RightKneeFlex\":110,\"RightAnkleFB\":93,\"RightAnkleUD\":84,\"LeftHipLR\":91,\"LeftHipFB\":89,\"LeftKneeFlex\":70,\"LeftAnkleFB\":97,\"LeftAnkleUD\":83,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         
const char* xiangzuozhuan4=(char*)"{\"runtime\":300,\"angles\":{    \"RightHipLR\":89,\"RightHipFB\":84,\"RightKneeFlex\":120,\"RightAnkleFB\":91,\"RightAnkleUD\":92,\"LeftHipLR\":91,\"LeftHipFB\":94,\"LeftKneeFlex\":58,\"LeftAnkleFB\":90,\"LeftAnkleUD\":90,\"RightShoulderRoll\":90,\"RightShoulderFlex\":170,\"RightElbowFlex\":104,\"LeftShoulderRoll\":89,\"LeftShoulderFlex\":17,\"LeftElbowFlex\":70}}";         


//void action()
//{
	double juli=hv_Distance.D();
    std::cout << "Distance:" << juli << std::endl;
    
    
    if(juli>30&&juli<250)
   {
      curl=curl_easy_init();
      motion_method(1);
      curl_easy_cleanup(curl); 
      
   }
    
    else if(juli<30)
   {
      curl=curl_easy_init();
      motion_method(2);
      curl_easy_cleanup(curl); 
   }
   
    else if(juli>250)
   {
      curl=curl_easy_init();
      motion_method(3);
      curl_easy_cleanup(curl); 
   }
   
   
   
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
		if(method==1)//执行直走的代码
		{
		//zhanli
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zhanli1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zhanli1)); 
		function();
		sleep(2);

		//姿态1
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		sleep(1);
		//姿态2
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao2)); 
		function();
		sleep(0);
		//姿态3
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao3)); 
		function();
		sleep(1);
		
		//姿态4
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fangzuojiao);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fangzuojiao)); 
		function();
		sleep(1);
		//姿态5
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, huanzhongxin1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(huanzhongxin1)); 
		function();
		sleep(1);
		//姿态6
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zuojiaozhunbei1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zuojiaozhunbei1)); 
		function();
		sleep(1);
		//姿态7
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, zuojiaozhunbei2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(zuojiaozhunbei2)); 
		function();
		sleep(1);
		//姿态8
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao1));
		function();
		sleep(1);
		//姿态9
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao2));
		function();
		sleep(0);
		//姿态10
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taiyoujiao3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taiyoujiao3));
		function();
		sleep(1);
		//姿态11
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fangyoujiao);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fangyoujiao)); 
		function();
		sleep(1);
		//姿态12
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, huanzhongxin2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(huanzhongxin2)); 
		function();
		sleep(1);
		//姿态13
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, youjiaozhunbei);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(youjiaozhunbei));
		function();
		sleep(1);
		//姿态14
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, taizuojiao1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(taizuojiao1)); 
		function();
		sleep(1);
		}
		
		else if(method==2)//xiangzuozhuan
		{
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan4)); 
		function();
		sleep(1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan1)); 
		function();
		sleep(1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan2)); 
		function();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan3)); 
		function();
		sleep(1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangzuozhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangzuozhuan4)); 
		function();
		sleep(1);
		}
		else if(method==3)//xiangyouzhuan
		{
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan4)); 
		function();
		sleep(1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan1);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan1)); 
		function();
		sleep(1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan2);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan2)); 
		function();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan3);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan3)); 
		function();
		sleep(1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xiangyouzhuan4);//data need to send 
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(xiangyouzhuan4)); 
		function();
		sleep(1);
		}
		
	}
}



//int main(int argc, char *argv[])
//{
  curl=curl_easy_init();
