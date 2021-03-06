#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <netdb.h>
#include "download.h"

using namespace std;

Result networkInit(){
	httpcInit();
	return 0;
}
char* downloadFile(char* url){
	Result r;
	httpcContext c;
	u8 *b; //buffer
	u32 statuscode=0;
	u32 contentsize=0;
	char* file;
	
	r = httpcOpenContext(&c, url, 0);
	if(r != 0){
		return "error: httpcOpenContext";
	}
	
	r = httpcBeginRequest(&c);
	if(r != 0){
		return "error: httpcBeginRequest";
	}
	
	r = httpcGetResponseStatusCode(&c, &statuscode, 0);
	if((r != 0) || statuscode != 200){
		return "error: httpcGetResponseStatusCode";
	}
	
	r = httpcGetDownloadSizeState(&c, NULL, &contentsize);
	if(r != 0){
		return "error: httpcGetDownloadSizeState";
	}
	
	b = (u8*)malloc(contentsize);
	if(b==NULL)return "error: (u8*)malloc(contentsize)";
	memset(b, 0, contentsize);
	
	r = httpcDownloadData(&c, b, contentsize, NULL);
	if(r != 0)
	{
		free(b);
		return "error: httpcDownloadData";
	}
	file = (char*)b;
	httpcCloseContext(&c);
	return file;
}
