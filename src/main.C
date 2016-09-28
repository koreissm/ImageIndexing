#include <dirent.h>
#include <regex>

#include "../libs/ImageProcessingTools.h"

char *substr(char *src,int pos,int len) { 
  char *dest=NULL;                        
  if (len>0) {                         
    dest = (char *) calloc(len+1, 1);
    if(NULL != dest) {
        strncat(dest,src+pos,len);            
    }
  }                                       
  return dest;                            
}

int main(int argc, char* argv[]){

	char* directory_path = argv[1];
	char* output_path = argv[2];
	DIR* dir = opendir(directory_path);
	struct dirent* dp;

	char* buffer = new char[80];

	while ((dp = readdir(dir)) != NULL){
		if(regex_match (dp->d_name, regex(".*jpg$") )){
			cout << "Processing: " << dp->d_name  << endl;
			sprintf(buffer, "%s%s", directory_path, dp->d_name);
			processImage(buffer, substr(dp->d_name, 0, strlen(dp->d_name)-4), output_path);
		}
    }

    (void)closedir(dir);
}