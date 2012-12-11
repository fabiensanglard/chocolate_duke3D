#include "cvars.h"
#include "cvar_defs.h"
#include <stdlib.h>

#define MAX_CVARS 32

#pragma message ( "We probably want this to be some sort of dynamic list at some point" )
cvar_binding cvar_binding_list[MAX_CVARS];
int num_cvar_bindings = 0;

void CVAR_RegisterCvar(const char* varname, const char* varhelp, void* variable, function_t function)
{
    if(NULL == function)
    {
        return;
    }

    cvar_binding_list[num_cvar_bindings].variable = variable;
    cvar_binding_list[num_cvar_bindings].function = function;
    memset(cvar_binding_list[num_cvar_bindings].name, 0, 64);
    strncpy(cvar_binding_list[num_cvar_bindings].name, varname, 63);    
	memset(cvar_binding_list[num_cvar_bindings].help, 0, 64);
    strncpy(cvar_binding_list[num_cvar_bindings].help, varhelp, 63);
    num_cvar_bindings++;
}

int CVAR_GetNumCvarBindings()
{
    return num_cvar_bindings;
}

cvar_binding* CVAR_GetCvarBinding(unsigned int nBinding)
{
    if(nBinding > num_cvar_bindings -1)
    {
        return NULL;
    }

    return &cvar_binding_list[nBinding];
}

// Bind all standard CVars here
void CVAR_RegisterDefaultCvarBindings()
{
    CVARDEFS_Init();
}

void CVAR_Render()
{
    CVARDEFS_Render();
}

