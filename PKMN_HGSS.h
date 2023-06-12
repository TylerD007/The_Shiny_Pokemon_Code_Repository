#ifndef PKMN_HGSS_H
#define PKMN_HGSS_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

#include <windows.h>
#include <stdio.h>

#include "PKMN_GEN4.h"

/*
POKEMON HEARTGOLD/SOULSILVER
rng: 			021d15a8
seed:			021d15ac
seed table:		021d15b0
seed index:		0210f6cc
offset:			02111880
TID/SID:		offset+0x84
Johto badges:	offset+0x8e
Kanto badges:	offset+0x93
*/

class PKMN_HGSS : public PKMN_GEN4
{
	protected:
		
	inline void function_0201fd44() //sets the next rng
	{
		rng=((DWORD)rng*0x41c64e6d)+0x6073;
		r[0]=(DWORD)rng>>0x10;		
	}
	
	inline void reverse_function_0201fd44() 
	{
		rng=(rng*0xeeb9eb65)+0xa3561a1;	
		r[0]=(DWORD)rng>>0x10;
	}
	
	void frame_advance(int frames=1)
	{
		for (DWORD count=1;count<frames;count++)
		{
			function_0201fd44();	
		}		
	}
	
	void frame_reverse(int frames=1)
	{
		for (DWORD count=1;count<frames;count++)
		{
			reverse_function_0201fd44();	
		}		
	}	
	
	void function_020f2998()//extracts encounter slot and nature from rng
	{
		r[12]=r[0]^r[1];
		r[12]=r[12] & 0x80000000;
		if (r[0]<0){r[0]=-r[0]; r[12]++;}
		if (r[1]<0){r[1]=-r[1];}
		if (r[1]==0){goto instruction_020f2b90;}
		if (cmp_cc(r[0],r[1])){r[1]=r[0]; r[0]=0;goto instruction_020f2b90;}
		
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
		
		instruction_020f2b90:	
		r[3]=r[12] & 0x80000000;
		if (r[3]!=0) {r[0]=-r[0];}
		r[3]=r[12] & 0x1;	
		if (r[3]!=0) r[1]=-r[1];
	}
	
	void function_02247890()//sets the nature
	{
		function_0201fd44();//sets the next rng
		r[1]=0x19;			
		function_020f2998();//sets parameters after rng call

		//0224789a
		r[0]=r[1] & 0xff;		
		nature=r[0];				

		//02247b34
		r[0]=0x22aa224;
		r[3]=0x20;
		function_0206e108();//finds the pid that matches the nature; function_02247b2e calls function_02247b2e, which calls function_0206e108;
	}
		
	void function_0206e108()//finds the pid that matches the nature
	{
		//0206e110
		r[4]=nature;	
			
		do
		{
			function_0201fd44();//sets the next rng
			r[5]=r[0];			
			function_0201fd44();//sets the next rng		
			r[0]=(DWORD)r[0]<<0x10;
			r[5]=r[5] | r[0];
			r[0]=r[5];				
					
			function_0206fe2c();//calls function that extracts nature from pid					
		}while (r[4]!=r[0]);	
		
		pid=r[5];		
	}
	
	inline void function_0206fe2c()//calls function that extracts nature from pid
	{
		r[1]=0x19;
		function_020f2ba4();//extracts nature from pid
		r[0]=r[1] & 0xff;		
	}
	
	void function_020f2ba4()//extracts nature from pid
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
	
	void function_0206e00a()//sets the ivs
	{
		function_0201fd44(); //sets the next rng
		
		iv[HP]=r[0] & 0x1f;
		iv[ATK]=(r[0] & (0x3e<<0x4))>>0x5;
		iv[DEF]=(r[0] & (0x1f<<0xa))>>0xa;
		
		function_0201fd44(); //sets the next rng

		iv[SPD]=r[0] & 0x1f;
		iv[SATK]=(r[0] & (0x3e<<0x4))>>0x5;
		iv[SDEF]=(r[0] & (0x1f<<0xa))>>0xa;	
	}	
};

class HGSS_Method_K_Grass : public PKMN_HGSS
{
	public:	
	void SetPKMN()
	{
		function_0224768e();//sets the encounter slot
		function_02247890();//sets the nature and pid
		function_0206e00a();//sets the ivs
	}
	
	void function_0224768e() //sets the encounter slot
	{
		function_0201fd44(); //sets the next rng
		r[1]=0x64;		
		function_020f2998();//sets the encounter value
		
		r[0]=r[1] & 0xff;				
				
		//022476a2
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
		WORD tid=0x0616;
		WORD sid=0xa1f8;
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
				function_0201fd44(); //sets the next rng
				hipid=r[0];			
				r[1]=hipid xor lopid xor tid xor sid;				
			} while (!(r[1]<0x8));
			
			pid=(hipid<<0x10) | lopid;
			last_shiny_rng=rng;		
			function_0201fd44();										
		
		}while(!validate_rng());	
		
		reverse_function_0201fd44();  			
	}
	
	bool validate_rng()
	{
		reverse_function_0201fd44(); 
		r[5]=(DWORD)r[0]<<0x10;
		reverse_function_0201fd44(); 
		r[0]=r[0] | r[5];			
		r[1]=0x19;				
		function_020f2ba4();//sets nature from pid
		r[4]=r[1] & 0xff;
		
		do
		{	
			reverse_function_0201fd44();
			r[5]=(WORD)r[0]<<0x10;	
			r[1]=0x19;
			function_020f2998();//sets nature from rng
			r[0]=r[1] & 0xff;
			if (r[0]==nature) break;
				
			reverse_function_0201fd44(); 
			r[5]=r[5] | r[0];
			r[0]=r[5];
			r[1]=0x19;				
			function_020f2ba4();
			r[0]=r[1] & 0xff;
			if (r[0]==nature) return false;
				
		}while(1);	
		
		return true;	
	}

};

class HGSS_Method_K_Stationary : public PKMN_HGSS
{
	public:
	void SetPKMN()
	{
		function_02247890();//sets the nature and pid
		function_0206e00a();//sets the ivs	
	}
};

class HGSS_Method_1 : public PKMN_HGSS
{
	public:	
	void SetPKMN()
	{		
		function_0206deea();//sets the pid
		function_0206e00a();//sets the ivs
		function_0206fe24();//sets the nature
	}
	
	void function_0206deea()
	{
		function_0201fd44();
		r[4]=r[0];
		function_0201fd44();
		r[0]=(DWORD)r[0]<<0x10;
		r[0]=r[0] | r[4];
		pid=r[0];
	}
	
	void function_0206fe24()
	{
		r[0]=pid;
		function_0206fe2c(); 
	}
	
};

class HGSS_Method_K_Bug_Catching : public PKMN_HGSS
{
	public:	
	void SetPKMN()
	{	
		function_02259b5e();//sets the encounter slot		
		
		for (int count=0;count<4;count++)//02247af6
		{
			function_02247890();//sets the nature and pid
			function_0201fd44();//sets the next rng
			function_0206e00a();//sets the ivs	
			if (function_02247af6()) break;	//checks if any iv is equal to 31		
		}
	} 
	
	void function_02259b5e()//sets the encounter slot
	{
		function_0201fd44();
		r[1]=0x64;
		function_020f2998();
		r[0]=(DWORD)r[1]<<0x10;
		r[3]=(DWORD)r[0]>>0x10;

		if (r[3]<0x5){encounter_slot=0x9;return;}
		else if (r[3]<0xa){encounter_slot=0x8;return;}
		else if (r[3]<0xf){encounter_slot=0x7;return;}
		else if (r[3]<0x14){encounter_slot=0x6;return;}
		else if (r[3]<0x1e){encounter_slot=0x5;return;}
		else if (r[3]<0x28){encounter_slot=0x4;return;}
		else if (r[3]<0x32){encounter_slot=0x3;return;}
		else if (r[3]<0x3c){encounter_slot=0x2;return;}
		else if (r[3]<0x50){encounter_slot=0x1;return;}
		else{encounter_slot=0;return;}					
	}
	
	bool function_02247af6()//checks if any iv is equal to 31
	{
			r[5]=0;
			
			do
			{
				r[0]=iv[r[5]];
				if (r[0]==0x1f) return true;
				r[5]++;
			}while(r[5]<0x6);					
			
			return false;
	}
	
	void Set_Shiny_PKMN()
	{
		WORD tid=0x0616;
		WORD sid=0xa1f8;
		WORD hipid=0x0;
		WORD lopid=0x0;	
		LONG shiny_rng;	

		shiny_rng=rng;

		do
		{
			rng=shiny_rng;
			r[0]=(DWORD)rng>>0x10;			
				
			do
			{
				lopid=r[0];			
				function_0201fd44(); //sets the next rng
				hipid=r[0];			
				r[1]=hipid xor lopid xor tid xor sid;				
			} while (!(r[1]<0x8));			
			
			pid=(hipid<<0x10) | lopid;
			shiny_rng=rng;
			function_0201fd44();
			function_0201fd44();
			function_0201fd44();
		}while(!validate_rng());
		
		reverse_function_0201fd44(); 			
	}
	
	bool validate_rng()
	{
		BOOL is_iv;
		int count=0;	
		
		do
		{
			
			is_iv=false;
			
			for (int iv_count=0;iv_count<2;iv_count++)
			{
				reverse_function_0201fd44(); 
				r[1]=r[0] & 0x1f;
				r[2]=(r[0] & (0x3e<<0x4))>>0x5;
				r[3]=(r[0] & (0x1f<<0xa))>>0xa;	
				
				if ((r[1]==0x1f) || (r[2]==0x1f) || (r[3]==0x1f)){is_iv=true;}
			}
			
			reverse_function_0201fd44(); 
			r[5]=(DWORD)r[0]<<0x10;
			reverse_function_0201fd44(); 
			r[0]=r[0] | r[5];			
			r[1]=0x19;				
			function_020f2ba4();//sets nature from pid
			r[4]=r[1] & 0xff;

					
			do
			{	
				reverse_function_0201fd44();
				r[5]=(DWORD)r[0]<<0x10;	
				r[1]=0x19;
				function_020f2998();//sets nature from rng
				r[0]=r[1] & 0xff;				
				if (r[0]==r[4]){break;}
				
				reverse_function_0201fd44(); 
				r[0]=r[5] | r[0];			
				r[1]=0x19;				
				function_020f2ba4();
				r[0]=r[1] & 0xff;
				if (r[0]==r[4]){return false;}
				
			}while(1);
			
			count++;
			
		}while( (count<4) && (is_iv==false) );

		return ((count==1) || (is_iv==false));
	}
	
};

class HGSS_Egg : public PKMN_HGSS
{
	private:
	LONG seed[0x270];
	WORD seed_index;

	public:
	HGSS_Egg() : seed_index(0){}
	void SetPKMN()
	{	
		function_0201fdb8();//sets the egg pid
		nature=pid%0x19;
	}
		
	void function_0201fdb8()//sets the egg pid
	{
		r[1]=seed_index;//[0210f6cc]
		r[0]=0x27;
		r[0]=(DWORD)r[0]<<0x4;
		if (r[1]<r[0]) {goto instruction_0201fe70;}		
		r[0]++;
		
		if (r[1]==r[0])	//r[1]=0x271	
		{
			r[0]=0x1571;
			function_0201fd74();	
		}
		
		r[4]=0x0;
		r[5]=0x7fffffff;
		r[6]=(DWORD)0x634>>0x2;
		r[0]=0x0;
				
		do
		{
			r[2]=0x2;
			r[3]=seed[r[4]];						
			r[2]=(DWORD)r[2]<<0x1e;
			r[3]=r[3] & r[2];
			r[2]=seed[r[4]+0x1];						
			r[0]++;
			r[2]=r[2] & r[5];
			r[3]=r[3] | r[2];
			r[7]=(DWORD)r[3]>>0x1;
			r[3]=(DWORD)r[3]<<0x1f;
			r[2]=seed[r[4]+r[6]];			
			r[3]=(DWORD)r[3]>>0x1d;			
			r[3]=(r[3]==0) ? 0 : 0x9908b0df;//[0210f6d0]
			r[2]=r[2] xor r[7];
			r[2]=r[2] xor r[3];						
			seed[r[4]++]=r[2];	
		}while(r[0]<0xe3);
		
		if (r[0]>=0x26f) {goto instruction_0201fe3c;}
		
		r[1]=r[0];
		//r[1]=r[2]+r[1];
		r[2]=0xe3;
		r[3]=0x26f;
		//r[2]=(DWORD)r[2]<<0x2;
		
		do
		{
			r[5]=0x2;
			r[6]=seed[r[1]];
			r[5]=(DWORD)r[5]<<0x1e;
			r[5]=r[5] & r[6];
			r[7]=seed[r[1]+0x1];			
			r[6]=0x7fffffff;
			r[0]++;
			r[6]=r[6] & r[7];
			r[6]=r[6] | r[5];
			r[5]=(DWORD)r[6]>>0x1;
			r[7]=r[1]-r[2];
			r[6]=(DWORD)r[6]<<0x1f;
			r[7]=seed[r[7]];			
			r[6]=(DWORD)r[6]>>0x1d;
			r[6]=(r[6]==0) ? 0 : 0x9908b0df;//[0210f6d0]
			r[5]=r[5] xor r[7];
			r[5]=r[5] xor r[6];			
			seed[r[1]++]=r[5];			
		}while(r[0]<r[3]);		
		
		instruction_0201fe3c:
		r[0]=0x2;
		r[1]=seed[0x26f];		
		r[0]=(DWORD)r[0]<<0x1e;
		r[3]=r[1];
		r[3]=r[3] & r[0];
		r[1]=seed[0];
		r[0]=r[0]-0x1;
		r[0]=r[0] & r[1];
		r[4]=r[3];
		r[4]=r[4] | r[0];
		r[1]=seed[0x18c];
		r[0]=(DWORD)r[4]>>0x1;
		r[3]=r[1];
		r[3]=r[3] xor r[0];
		r[0]=(DWORD)r[4]<<0x1f;
		r[1]=(DWORD)r[0]>>0x1d;
		r[0]=(r[1]==0) ? 0 : 0x9908b0df;//[0210f6d0]
		r[1]=0x0;
		r[0]=r[0] xor r[3];
		seed[0x26f]=r[0];
		seed_index=r[1];		
		
		instruction_0201fe70:		
		r[2]=seed_index;//[0210f6cc]
		seed_index++;		
		r[1]=seed[r[2]];//0x3d83ecf0;//[021d15b4]
		r[0]=(DWORD)r[1]>>0xb;
		r[2]=r[1];
		r[2]=r[2] xor r[0];
		r[0]=0x9d2c5680;
		r[1]=(DWORD)r[2]<<0x7;
		r[0]=r[0] & r[1];
		r[2]=r[2] xor r[0];
		r[0]=0xefc60000;
		r[1]=(DWORD)r[2]<<0xf;
		r[0]=r[0] & r[1];
		r[1]=r[2];
		r[1]=r[1] xor r[0];
		r[0]=(DWORD)r[1]>>0x12;
		r[0]=r[0] xor r[1];
		
		pid=r[0];		
	}
	
	void function_0201fd74()//initialize the seeds (0x021d15ac)
	{
		r[4]=0x27;
		seed[0]=r[0];
		r[0]=0x0;
		seed_index=r[0];
		r[0]++;
		r[1]=0x1;
		r[3]=0x6c078965;
		r[4]=(DWORD)r[4]<<0x4;
		
		do
		{
			r[2]=r[1]-0x1;
			r[5]=seed[r[2]];
			r[2]=(DWORD)r[5]>>0x1e;
			r[2]=r[2] xor r[5];
			r[5]=r[2];
			r[5]=r[5]*r[3];			
			r[2]=r[0]+r[5];		
			r[0]++;			
			seed[r[1]++]=r[2];			
		}while(r[0]<r[4]);
		
		seed_index=r[0];	
	}
		
};

#endif //PKMN_HGSS_H
