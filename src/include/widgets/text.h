#ifndef _WIDGETS_TEXT_H_
#define _WIDGETS_TEXT_H_

//Are we are built for Windows or Linux
#ifdef _WIN32
//Built for windows, references windows text widget
#include <widgets/windows/text.h>
#elif linux
//Built for linux, references linux text widget
#include <widgets/linux/text.h>
#endif

#endif