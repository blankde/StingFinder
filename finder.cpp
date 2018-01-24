/*
 * finder.cpp
 *
 *  Created on: 2018��1��24��
 *      Author: wen
 *
 *  1.������ǰ�ļ����µ��ļ�
 *  2.����ÿһ���ļ���
 *  	�����Ƿ���ҵ��ļ�
 *  3.������һ��Ŀ¼
 */
#include <iostream>
#include <io.h>
#include <string.h>
#include <errno.h>

using namespace std;


void loopFind(const char* path,const char* key);	//���ļ��н��еݹ����
void findInFile(const char* key,const char* file);	//����ָ�����ַ����Ƿ����ļ��г���

int main(){
	loopFind("D:\\��Ҫ����\\Desktop\\gpdb-master\\gpdb-master\\src","nodeWindowAgg");
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

			//������ļ���
			if((fileInfo.attrib  & _A_SUBDIR)){
				if(strcmp(fileInfo.name,".")!=0 && strcmp(fileInfo.name,"..")!=0){
					loopFind(currentFile,key);
				}
			}
			//����
			else
				findInFile(key,currentFile);
		}while(_findnext(h_file,&fileInfo)==0);
	}
}
void findInFile(const char* key,const char* name){
	FILE* pFile;
	long l_size;
	char* buffer;

	//���ļ�
	pFile = fopen(name, "rb");
	if(pFile==NULL){
		string msg = "open "+(string)name+" failed\n";
		fputs(msg.c_str(),stderr);
	}

	//����buffer�ڴ�
	fseek(pFile,0,SEEK_END);
	l_size = ftell(pFile);
	rewind(pFile);

	buffer = (char*)malloc(sizeof(char*)*l_size);
	if(buffer==NULL){
		fputs("memory error\n",stderr);
	}

	//��ȡ�ļ����ݵ�buffer
	if(fread(buffer,1,l_size,pFile)!=(size_t)l_size){
		fputs("Reading error\n",stderr);
	}
	fclose(pFile);

	if (strstr(buffer, key))
		cout << name << endl;
}

