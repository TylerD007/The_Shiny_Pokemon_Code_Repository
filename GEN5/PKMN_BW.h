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

#ifndef PKMN_BW_H
#define PKMN_BW_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

/*
POKEMON BLACK/WHITE
rng: 			02216224
offset:			02000024
TID/SID:		offset+0x3464c
*/

/*
RNG ROUTINE : GRASS/DUNGEON ENCOUNTERS
021a98ee 			 : battle prep
021aa41a bl 021aa6e0 : battle trigger
021a9de2 bl 021a9dc8 : set species
*/


/*
RNG ROUTINE : STATIONARY ENCOUNTERS
021a98ee 			 : battle prep
020186d8 bl 020056ec : PID
*/

#include "PKMN_GEN5.h"

class PKMN_BW : public PKMN_GEN5
{
	protected:
		
	void function_020056ec()//sets the next rng
	{
		r[5]=r[0];	
		rng=(DWORD64)(rng*(DWORD64)0x5D588B656C078965) + 0x0000000000269EC3;
		
		r[0]=rng>>0x20;
		r[3]=rng;
		
		if (r[5]==0)
		{
			r[1]=rng>>0x20;
		}else
		{
			r[1]=(((DWORD64)rng>>0x20)*r[5])>>0x20;				
		}
		r[0]=r[1];			
	}
	
	void reverse_function_020056ec()//sets the previous rng
	{
		rng=0xdedcedae9638806d*rng+0x9b1ae6e9a384e6f9;
	}
	
	void function_0209c054()//dword64 multiplication
	{
		//(r[0]+r[1]*2^32)*(r[2]+r[3]*2^32)
		r[0]=((DWORD64)r[0]*r[2])>>0x20;
		r[1]=(r[0]*r[2])+(r[0]*r[3])+(r[1]*r[2]);		
	}
	
	public:
	
	
	void function_0209c2b0()//sets the encounter slot from rng
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
		
		r[1]=r[3];	
	}
	
	void function_021a9d8e()//sets the pid
	{
		r[6]=((DWORD)sid<<0x10) | tid;
		function_020186c8();//checks the pid type
		r[1]=0x0;//[02fe36ca]
		if (r[1]!=0x2)
		{
			r[4]=0x03f1137a;//[02fe36b8]
			r[1]=(DWORD)r[0]<<0x10;
			r[3]=(DWORD)r[1]>>0x10;
			r[1]=(DWORD)r[4]<<0x10;
			r[2]=(DWORD)r[4]>>0x10;
			r[1]=(DWORD)r[1]>>0x10;
			r[1]=r[1] xor r[2];
			r[2]=r[3];
			r[2]=r[1] xor r[2];
			r[1]=0x1;
			if ( (r[1] & r[2]) !=0)
			{
				r[1]=0x2;
				r[1]=(DWORD)r[1]<<0x1e;
				r[0]=r[0] | r[1];
			}
			else
			{
				r[1]=0x7fffffff;	
				r[0]=r[0] & r[1];				
			}
		}
		
		pid=r[0];
		
	}
	
	void function_020186c8()//checks the pid type
	{
		r[0]=0x0;
		function_020056ec();//sets the next rng	
		r[4]=r[0];
		
		//0201872a: PID decision
		if (pid_type==0){goto instruction_02018764;}//PID TYPE 0 (SHINY-LOCKED PID): Celebi, Arceus, Victini, Reshiram, Zekrom, Keldeo, Meloetta
		else if (pid_type==1){goto instruction_0201873a;}
		else if (pid_type==2){goto instruction_02018776;}//PID TYPE 2 (REGULAR PID): grass/dungeon, stationary, surf, fishing encounters
		else{goto instruction_02018788;}		
		
		instruction_0201873a://PID TYPE 1 
		//TODO
		
		instruction_02018764://PID TYPE 0 (SHINY-LOCKED PID): Celebi, Arceus, Victini, Reshiram, Zekrom, Keldeo, Meloetta
		r[0]=r[6];
		r[1]=r[4];
		if (!function_02017ed8()){goto instruction_02018776;}//checks if pokémon is shiny
		r[0]=0x1;
		r[0]=(DWORD)r[0]<<0x1c;
		r[4]=r[4] xor r[0];		
		
		instruction_02018776://PID TYPE 2 (REGULAR PID): grass/dungeon, stationary, surf, fishing encounters
		r[0]=0x1;
		r[1]=0x2;//[02fe3600]
		r[0]=(DWORD)r[0]<<0x10;
		r[2]=r[4];
		r[2]=r[2] & r[0];
		r[1]=(DWORD)r[1]<<0x10;				
		if (r[1]!=r[2]){r[4]=r[4] xor r[0];}
		
		instruction_02018788:
		r[0]=r[4];		
	}
	
	bool function_02017ed8()//checks if pokémon is shiny
	{
		r[3]=0xffff0000;
		r[2]=(DWORD)r[1]<<0x10;
		r[1]=r[1] & r[3];
		r[3]=r[3] & r[0];
		r[0]=(DWORD)r[0]<<0x10;
		r[3]=(DWORD)r[3]>>0x10;
		r[0]=(DWORD)r[0]>>0x10;
		r[1]=(DWORD)r[1]>>0x10;
		r[0]=r[0] xor r[3];
		r[2]=(DWORD)r[2]>>0x10;
		r[0]=r[0] xor r[1];
		r[0]=r[0] xor r[2];
		return (r[0]<0x8);
	}
	
	void function_020178a2()//sets the nature
	{
		r[0]=0x19;
		function_020056ec();//sets the next rng	
		nature=r[0];
	}
	
};

class BW_PIDRNG_Grass : public PKMN_BW
{
	public:
	void SetPKMN()
	{		
		//rng=0xbe111b461f3c37f9;//slot:1, quirky, ivs: 13,9,24,0,1,22
		//rng=0x2f862bf88682e86d;//slot:9, hardy(0), ivs:6,30,14,23,7,17
		//rng=0x7b2decc748516654;//slot:9, careful(23)
		
		function_020056ec();//sets the next rng
		function_021a9de0();//sets the encounter slot
		function_020056ec();//sets the next rng
		function_021a9d8e();//sets the pid
		function_020178a2();//sets the nature
	}
	
	void function_021a9de0()
	{
		function_021a9dc8();//sets encounter slot parameters
	
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
	
	void function_021a9dc8()//sets encounter slot parameters
	{
		r[0]=0xffff;
		function_020056ec();//sets the next rng
		r[1]=0x29;
		r[1]=(DWORD)r[1]<<0x4;		
		function_0209c2b0();//sets the encounter slot from rng
	}
		
};

class BW_PIDRNG_Stationary : public PKMN_BW
{
	public:
	void SetPKMN()
	{		
		function_020056ec();//sets the next rng
		function_021a9d8e();//sets the pid
		function_020178a2();//sets the nature
	}	
};

class BW_PIDRNG_Starters : public PKMN_BW
{
	public:
	void SetPKMN()
	{		
		function_021a9d8e();//sets the pid
		function_020178a2();//sets the nature
	}	
};

class BW_PIDRNG_Roamers : public PKMN_BW
{
	public:
	void SetPKMN()
	{		
		function_02017660();//sets the pid
		function_020178a2();//sets the nature
	}
	
	void function_02017660()
	{
		r[0]=0x0;
		function_020056ec();//sets the next rng
		pid=r[0];
	}
};


#endif //PKMN_BW_H
