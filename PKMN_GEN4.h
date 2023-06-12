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
	
