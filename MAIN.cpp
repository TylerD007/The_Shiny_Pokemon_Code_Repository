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

#include <windows.h>
#include <stdio.h>
#include "PKMN_HGSS.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HGSS_Method_K_Grass method_grass;
	method_grass.SetPKMN();
	
	HGSS_Method_K_Stationary method_stationary;	
	method_stationary.SetPKMN();
	
	HGSS_Method_1 method_1;
	method_1.SetPKMN();
	
	HGSS_Egg method_egg;
	method_egg.SetPKMN();
	
	return 0;
}



	
