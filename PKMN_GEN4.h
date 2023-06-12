
#ifndef PKMN_GEN4_H
#define PKMN_GEN4_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

#include "ARM_CONSOLE.h"

#define HP 0
#define ATK 1
#define DEF 2
#define SATK 3
#define SDEF 4
#define SPD 5

class PKMN_GEN4 : public ARM_CONSOLE
{
	protected:
	LONG rng;	
	
	BYTE encounter_slot;
	BYTE nature;
	DWORD pid;
	BYTE iv[6];

	public:
	PKMN_GEN4():rng(0){}
	virtual void SetPKMN()=0;	
};

#endif //PKMN_GEN4_H
	
