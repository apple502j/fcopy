#include <stdio.h>

int main(int argc,char *argv[]){

	FILE *f1,*f2;
	if(argc!=3){
		fputs("Usage:fcopy file1 file2\n",stderr);
		return 1;
	}
	f1=fopen(argv[1],"rb");
	if(f1==NULL){
		perror(argv[1]);
		return 2;
	}
	f2=fopen(argv[2],"wb");
	if(f2==NULL){
		fclose(f1);
		perror(argv[2]);
		return 2;
	}
	while(1){
		int data,info;
		info=fread(&data,sizeof(int),1,f1);
		if(info==0){
			if(ferror(f1)){
				fclose(f1);
				fclose(f2);
				perror(argv[1]);
				return 2;
			}else{
				break;
			}
		}
		info=fwrite(&data,sizeof(int),1,f2);
		if(ferror(f2)){
			fclose(f1);
			fclose(f2);
			perror(argv[2]);
			return 2;
		}
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
