#include <xinu.h>

void actuatoron(did32 descrp)
{
	char ch;
	ch = '1';
	putc(descrp,ch);
}

void actuatoroff(did32 descrp)
{
	char ch;
	ch = '0';
	putc(descrp,ch);
}
