/*
 * finder.cpp
 *
 *  Created on: 2018年1月24日
 *      Author: wen
 *
 *  1.遍历当前文件夹下的文件
 *  2.对于每一个文件：
 *  	查找是否查找到文件
 *  3.遍历下一层目录
 */
#include <iostream>
#include <io.h>
#include <string.h>
#include <errno.h>

using namespace std;


void loopFind(const char* path,const char* key);	//对文件夹进行递归查找
void findInFile(const char* key,const char* file);	//查找指定的字符串是否在文件中出现

int main(){
	loopFind("D:\\重要数据\\Desktop\\gpdb-master\\gpdb-master\\src","nodeWindowAgg");
	cout << "look up files done";
	return 0;
}

void loopFind(const char* path,const char* key){
	long h_file = 0;
	struct _finddata_t fileInfo;
	string p;

	if((h_file =_findfirst(p.assign(path).append("\\*").c_str(),&fileInfo)) !=-1){
		do{
			const char* currentFile = p.assign(path).append("\\").append(fileInfo.name).c_str();

			//如果是文件夹
			if((fileInfo.attrib  & _A_SUBDIR)){
				if(strcmp(fileInfo.name,".")!=0 && strcmp(fileInfo.name,"..")!=0){
					loopFind(currentFile,key);
				}
			}
			//否则
			else
				findInFile(key,currentFile);
		}while(_findnext(h_file,&fileInfo)==0);
	}
}
void findInFile(const char* key,const char* name){
	FILE* pFile;
	long l_size;
	char* buffer;

	//打开文件
	pFile = fopen(name, "rb");
	if(pFile==NULL){
		string msg = "open "+(string)name+" failed\n";
		fputs(msg.c_str(),stderr);
	}

	//分配buffer内存
	fseek(pFile,0,SEEK_END);
	l_size = ftell(pFile);
	rewind(pFile);

	buffer = (char*)malloc(sizeof(char*)*l_size);
	if(buffer==NULL){
		fputs("memory error\n",stderr);
	}

	//读取文件内容到buffer
	if(fread(buffer,1,l_size,pFile)!=(size_t)l_size){
		fputs("Reading error\n",stderr);
	}
	fclose(pFile);

	if (strstr(buffer, key))
		cout << name << endl;
}

