// Fill out your copyright notice in the Description page of Project Settings.

#include "C_BurningArea.h"
#include "UnrealNetwork.h"


AC_BurningArea::AC_BurningArea() {
	bReplicates = true;
	bReplicateMovement = true;

	DamagePerSec = 0.f;
	bPainCausing = false;
	Strong = 1;
}

void AC_BurningArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AC_BurningArea, Strong);
	DOREPLIFETIME(AC_BurningArea, IsBurning);
	DOREPLIFETIME(AC_BurningArea, MyOrder);
}

bool AC_BurningArea::SetActivate_Validate() {
	return true;
}
void AC_BurningArea::SetActivate_Implementation() {
	bPainCausing = true;
	DamagePerSec = 2.f;

	// 내려왔을때 Z 값 17840.0
}

bool AC_BurningArea::MoreStrog_Validate() {
	return true;
}
void AC_BurningArea::MoreStrog_Implementation() {
	Strong++;
	switch (Strong)
	{
	case 1:
		DamagePerSec = 2.f;
		break;
	case 2:
		DamagePerSec = 5.f;
		break;
	case 3:
		DamagePerSec = 10.f;
		break;
	case 4:
		DamagePerSec = 20.f;
		break;
	case 5:
		DamagePerSec = 30.f;
		break;
	case 6:
		DamagePerSec = 40.f;
		break;
	case 7:
		DamagePerSec = 50.f;
		break;
	default:
		break;
	}
}