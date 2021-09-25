
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern char __stdata__;
extern char __etdata__;
extern char __stbss__;
extern char __etbss__;

void *_Anvil_tls_tp = NULL;

void *__aeabi_read_tp()
{
	if (!_Anvil_tls_tp)
	{
		//printf("Allocating %x bytes\n", &__etbss__ - &__stdata__);
		void *new_p = malloc(&__etbss__ - &__stdata__);
		//printf("Copying %x bytes\n", &__etdata__ - &__stdata__);
		memcpy(new_p, &__stdata__, &__etdata__ - &__stdata__);
		//printf("Zeroing %x bytes\n", &__etbss__ - &__stbss__);
		memset((char *)new_p + (&__etdata__ - &__stdata__), 0, &__etbss__ - &__stbss__);
		_Anvil_tls_tp = new_p;
	}
	return _Anvil_tls_tp;
}
