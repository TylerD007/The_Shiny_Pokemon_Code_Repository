/*
 * Pokémon Generation 4 RNG Repository
 * Written in C++

 * Copyright (C) 2023 Ciro Bogea Fernandes.

 * This library is free software. You can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation;

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

 * Permission to use this software and its documentation *AS IT IS* for any purpose
 * is hereby granted without fee, provided that the above copyright notice appear 
 * in all copies and that both that copyright notice and this permission notice appear
 * in supporting documentation.  It is provided "as is" without express or implied warranty. 
*/

#ifndef ARM_CONSOLE_H
#define ARM_CONSOLE_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

#include <windows.h>
#include <stdio.h>

#define VALTOHEX(buf, i)	sprintf(buf,"%08X",i)

#define add_n(x,y) (x+y<0)
#define add_z(x,y) (x+y==0)
#define add_c(x,y) (((DWORD64)(DWORD)(x)+(DWORD64)(DWORD)(y))>UINT_MAX)
#define cmp_n(x,y) (x-y<0)
#define cmp_z(x,y) (x-y==0)
#define cmp_c(x,y) (!add_c((~x),y))
#define cmp_cc(x,y) (!cmp_c(x,y))
#define cmp_hi(x,y) ((!cmp_z(x,y)) && cmp_c(x,y))
#define cmp_ls(x,y)	(cmp_z(x,y) || (!cmp_c(x,y)))

	
class ARM_CONSOLE
{
	protected:
	LONG r[16];
	bool FLAG_N, FLAG_Z, FLAG_C, FLAG_V;
	
	char buffer0[20];
	char buffer1[20];
	char buffer2[20];
	char buffer3[20];	
	
	public:		
	inline void cmp(LONG x, LONG y)
	{
		FLAG_N=cmp_n(x,y);
		FLAG_Z=cmp_z(x,y);
		FLAG_C=cmp_c(x,y);
		//FLAG_V1=((x>0) && (y>0) && (x+y)<0);
	}
	
	LONG adds(LONG x, LONG y)
	{
		FLAG_N=add_n(x,y);
		FLAG_Z=add_z(x,y);
		FLAG_C=add_c(x,y);
		return x+y;
	}
	LONG adcs(LONG x, LONG y)
	{
		return adds(x,y+FLAG_C);
	}
	
	LONG adc(LONG x, LONG y)
	{
		return x+y+FLAG_C;
	}
};


#endif //ARM_CONSOLE_H
