/*************************************************************************
	> File Name: DBG.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Mon 29 Jul 2024 07:23:41 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _DBG_H__
#define _DBG_H__

namespace SH {
#include "./color.h"
#ifdef _D

#define DBG(fmt, arg...) printf(L_BLUE("[===DBG===]: ") fmt, ##arg )

#else

#define DBG(fmt, arg...)

#endif
}

#endif

