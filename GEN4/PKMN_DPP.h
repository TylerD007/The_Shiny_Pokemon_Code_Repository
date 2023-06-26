/*
 * Pokémon RNG Repository
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

#ifndef PKMN_DPP_H
#define PKMN_DPP_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

#include <windows.h>
#include <stdio.h>

#include "PKMN_GEN4.h"

/*
POKEMON PLATINUM
rng: 			021BFB14
offset:			02101D40
TID/SID:		offset+0x8c
*/

class PKMN_DPP : public PKMN_GEN4
{
	protected:
	inline void function_0201d2e8() //sets the next rng
	{
		rng=((DWORD)rng*0x41c64e6d)+0x6073;
		r[0]=(DWORD)rng>>0x10;		
	}
	
	inline void reverse_function_0201d2e8() 
	{
		rng=(rng*0xeeb9eb65)+0xa3561a1;	
		r[0]=(DWORD)rng>>0x10;
	}
	
	void function_020e1f6c()//extracts the encounter slot or nature from the rng
	{
		r[12]= r[0] xor r[1];
		r[12]=r[12] & 0x80000000;
		if (r[0]<0){r[0]=-r[0];	r[12]++;}		
		if (r[1]<0){r[1]=-r[1];}		
		if (r[1]==0){goto instruction_020e2164;}
		if (cmp_cc(r[0],r[1])){r[1]=r[0]; r[0]=0;goto instruction_020e2164;}
		
		r[2]=0x1c;
		r[3]=(DWORD)r[0]>>0x4;
		
		if (r[1]<=((DWORD)r[3]>>0xc))
		{
			r[2]=r[2]-0x10;
			r[3]=(DWORD)r[3]>>0x10;	
		}
		if (r[1]<=((DWORD)r[3]>>0x4))
		{
			r[2]=r[2]-0x8;
			r[3]=(DWORD)r[3]>>0x8;
		}
		if (r[1]<=((DWORD)r[3]>>0x0))
		{
			r[2]=r[2]-0x4;
			r[3]=(DWORD)r[3]>>0x4;
		}

		//020f29f4
		r[0]=(DWORD)r[0]<<r[2];
		r[1]=-r[1];		
		r[0]=adds(r[0],r[0]);
		r[2]=r[2]+((DWORD)r[2]<<0x1);
		r[15]=(DWORD)r[2]<<0x2;
		
		while(r[15]<384)//020f2a0c
		{
			r[3]=adcs(r[1], ((DWORD)r[3]<<0x1));
			if (!FLAG_C) {r[3]=r[3]-r[1];}
			r[0]=adcs(r[0],r[0]);			
			r[15]+=12;
		}
		
		r[1]=r[3];//020f2b8c
		
		instruction_020e2164:	
		r[3]=r[12] & 0x80000000;
		if (r[3]!=0) {r[0]=-r[0];}
		r[3]=r[12] & 0x1;	
		if (r[3]!=0) r[1]=-r[1];		
	}
	
	void function_02241b1e()//sets the nature
	{
		function_0201d2e8();//sets the next rng
		r[1]=0xa3e;		
		function_020e1f6c();//extracts the encounter slot or nature from the rng
		r[4]=r[0] & 0xffff;	
		
		if (cmp_cc(r[4],0x19))
		{
			//function_02022974();
		}
		
		nature=r[0]=r[4] & 0xff;
	}
	
	void function_02074052()//sets the pid
	{
		r[4]=nature;
		
		do
		{
			function_0201d2e8();//sets the next rng
			r[5]=r[0];
			function_0201d2e8();//sets the next rng
			r[0]=(DWORD)r[0]<<0x10;
			r[0]=r[0] | r[5];
			function_02075bfc();//calls the function that extracts the nature from the pid
		} while(r[0]!=r[4]);
		
		pid=r[5];
	}
	
	inline void function_02075bfc()//calls function that extracts nature from pid
	{
		r[1]=0x19;
		function_020e2178();//extracts nature from pid
		r[0]=r[1] & 0xff;		
	}
	
	void function_020e2178()//sets nature from pid
	{
		if (r[1]==0) return;
				
		if (cmp_cc(r[0],r[1]))
		{
			r[1]=r[0];
			r[0]=0;	
			return;
		}
		
		r[2]=0x1c;
		r[3]=(DWORD)r[0]>>0x4;		
		
		if (r[1]<((DWORD)r[3]>>0xc))
		{
			r[2]=r[2]-0x10;
			r[3]=(DWORD)r[3]>>0x10;	
		}
		if (r[1]<((DWORD)r[3]>>0x4))
		{
			r[2]=r[2]-0x8;
			r[3]=(DWORD)r[3]>>0x8;	
		}
		if (r[1]<((DWORD)r[3]>>0x0))
		{
			r[2]=r[2]-0x4;
			r[3]=(DWORD)r[3]>>0x4;	
		}
		
		r[0]=(DWORD)r[0]<<r[2];
		r[1]=-r[1];
		r[0]=adds(r[0],r[0]);
		r[2]=r[2]+((DWORD)r[2]<<0x1);
		r[15]=(DWORD)r[2]<<0x2;
		
		while(r[15]<384)
		{
			r[3]=adcs(r[1],(DWORD)r[3]<<0x1);
			if (!FLAG_C) {r[3]=r[3]-r[1];}
			r[0]=adcs(r[0],r[0]);			
			r[15]+=12;
		}
		
		r[1]=r[3];	
	}		
};

class DPP_Method_J_Grass : public PKMN_DPP
{
	public:	
	void SetPKMN()
	{
		function_02241906();//sets the encounter slot
		function_02241b1e();//sets the nature
		function_02074052();//sets the pid
	}
	
	void function_02241906()//sets the encounter slot
	{
		function_0201d2e8();//sets the next rng
		r[1]=0x29;
		r[1]=(DWORD)r[1]<<0x4;
		function_020e1f6c();//extracts the encounter slot or nature from the rng
		r[4]=r[0] & 0xffff;
		
		if (cmp_cc(r[4],0x64))
		{
			//function_02022974();
		}
		
		r[0]=r[4] & 0xff;
		
		if (r[0]<0x14){encounter_slot=0x0;return;}
		else if (r[0]<0x28){encounter_slot=0x1;return;}
		else if (r[0]<0x32){encounter_slot=0x2;return;}
		else if (r[0]<0x3c){encounter_slot=0x3;return;}
		else if (r[0]<0x46){encounter_slot=0x4;return;}
		else if (r[0]<0x50){encounter_slot=0x5;return;}
		else if (r[0]<0x55){encounter_slot=0x6;return;}
		else if (r[0]<0x5a){encounter_slot=0x7;return;}
		else if (r[0]<0x5e){encounter_slot=0x8;return;}
		else if (r[0]<0x62){encounter_slot=0x9;return;}
		else if (r[0]==0x62){encounter_slot=0xa;}
		else {encounter_slot=0xb;return;}		
	}	
	
	void Set_Shiny_PKMN()
	{
		WORD tid=0x4ca4;
		WORD sid=0x41b3;
		WORD hipid=0x0;
		WORD lopid=0x0;	
		LONG last_shiny_rng;	
		
		last_shiny_rng=rng;

		do
		{
			rng=last_shiny_rng;
			r[0]=(DWORD)rng>>0x10;			
				
			do
			{
				lopid=r[0];			
				function_0201d2e8(); //sets the next rng
				hipid=r[0];			
				r[1]=hipid xor lopid xor tid xor sid;				
			} while (!(r[1]<0x8));
			
			pid=(hipid<<0x10) | lopid;
			last_shiny_rng=rng;		
			function_0201d2e8();										
		
		}while(!validate_rng());
		
		reverse_function_0201d2e8();  			
	}
	
	bool validate_rng()
	{
		reverse_function_0201d2e8(); 
		r[5]=(DWORD)r[0]<<0x10;
		reverse_function_0201d2e8(); 
		r[0]=r[0] | r[5];			
		r[1]=0x19;			
		function_020e2178();//sets nature from pid
		r[4]=r[1] & 0xff;
		
		do
		{	
			reverse_function_0201d2e8();
			r[5]=(WORD)r[0]<<0x10;	
			r[1]=0xa3e;
			function_020e1f6c();//sets nature from rng
			r[0]=r[0] & 0xff;
			if (r[0]==nature) break;
				
			reverse_function_0201d2e8(); 
			r[5]=r[5] | r[0];
			r[0]=r[5];
			r[1]=0x19;				
			function_020e2178();//sets nature from pid
			r[0]=r[1] & 0xff;
			if (r[0]==nature) return false;
				
		}while(1);	
		
		return true;	
	}	
	
};

#endif //PKMN_DPP_H
