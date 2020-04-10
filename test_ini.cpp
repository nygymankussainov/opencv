#include <vlc.h>
#pragma hdrstop
#include <stdio.h>

int		main(void) {

	char takenstring[100];
	GetPrivateProfileString("testing","CONFIG_NAME","fail while retrieving",takenstring,100,"options-configure.ini");
	printf("%s\n", takenstring);

}