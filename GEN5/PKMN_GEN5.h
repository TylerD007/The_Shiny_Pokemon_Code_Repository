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

#ifndef PKMN_GEN5_H
#define PKMN_GEN5_H

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

#include "ARM_CONSOLE.h"

class PKMN_GEN5 : public ARM_CONSOLE
{
	protected:
	LONG64 rng;//02216224
	WORD tid;
	WORD sid;
	BYTE encounter_slot;
	BYTE nature;
	DWORD pid;
	BYTE pid_type;
	BYTE iv[6];
	
	public:
	PKMN_GEN5():rng(0), tid(0), sid(0), pid_type(2){}
	virtual void SetPKMN()=0;	
};

#endif //PKMN_GEN5_H
