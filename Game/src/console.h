#ifndef _CONSOLE_H_
#define _CONSOLE_H_


// Public member functions
void     CONSOLE_Init();
void     CONSOLE_Reset();
void     CONSOLE_Term();
void     CONSOLE_ParseStartupScript();
void     CONSOLE_HandleInput();
void     CONSOLE_Render();
void     CONSOLE_ParseCommand(uint8_t * command);
void     CONSOLE_Printf(const uint8_t  *newmsg, ...);
int      CONSOLE_GetArgc();
uint8_t *    CONSOLE_GetArgv(unsigned int var);
int      CONSOLE_IsActive();
void     CONSOLE_SetActive(int i); 

#endif
