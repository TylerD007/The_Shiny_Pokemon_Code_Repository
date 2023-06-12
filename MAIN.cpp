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



	
