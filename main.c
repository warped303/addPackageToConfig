#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 1028

void copyFile(FILE* to, FILE* from)
{
	char buff[BUFF_SIZE];
	
	fseek(to, 0, SEEK_SET);
	fseek(from, 0, SEEK_SET);

	while(fgets(buff, BUFF_SIZE, from) != NULL)
	{
		fputs(buff, to);
	}
}

int main(int argc, char* argv[])
{
	char buff[BUFF_SIZE];

	FILE* configFile;
	if((configFile = fopen("/etc/nixos/configuration.nix", "r+")) == NULL)
	{
		printf("Error: Unable to open configuration.nix\n");
		return 1;
	}

	FILE* writeFile;
	if((writeFile = fopen("./write", "w+")) == NULL)
	{
		printf("Error: Unable to open write file\n");
		return 1;
	}

	char package[BUFF_SIZE];

	// copy config to write file until line with environment.systemPackage is found
	do
	{
		fgets(buff, BUFF_SIZE, configFile);
		fputs(buff, writeFile);
	} while (strstr(buff, "environment.systemPackage") == NULL);
	
	// append packages to write file
	for (int i = 1; i < argc; i++)
	{
		strcpy(package, "  ");
		strcat(package, argv[i]);
		strcat(package, "\n");
		fputs(package, writeFile);
	}

	// copy the rest of config file to write file
	while (fgets(buff, BUFF_SIZE, configFile) != NULL)
	{
		fputs(buff, writeFile);
	}

	// copy write file to config
	copyFile(configFile, writeFile);

	fclose(configFile);
	fclose(writeFile);

	return 0;
}

