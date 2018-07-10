// Fill out your copyright notice in the Description page of Project Settings.

#include "C_BurningArea.h"
#include "UnrealNetwork.h"


AC_BurningArea::AC_BurningArea() {
	bReplicates = true;
	bReplicateMovement = true;

	DamagePerSec = 0.f;
	// Pain Causing Volume 에 내장되어있는 데미지주는 Bool 값.
	bPainCausing = false;
	Strong = 0;

	MoveComplete = true;
}

void AC_BurningArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AC_BurningArea, Strong);
	DOREPLIFETIME(AC_BurningArea, MyOrder);
	DOREPLIFETIME(AC_BurningArea, MoveComplete);
}

void AC_BurningArea::BeginPlay()
{
}

void AC_BurningArea::Tick(float DeltaSeconds)
{
	// bPainCausing 이 true 가 되거나 MoveComplete 가 true 가 아닐때(!)

	if (bPainCausing && !MoveComplete) {
		SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, DeltaSeconds*MoveingRate));

		// 불이 밑에서 올라오기때문에 >= 를 씀.
		if (GetActorLocation().Z >= 17840.f) {
			FVector NewVector = GetActorLocation();
			NewVector.Z = 17840.f;
			SetActorLocation(NewVector);
			MoveComplete = true;
		}
	}
	
}

bool AC_BurningArea::SetActivate_Validate() {
	return true;
}
void AC_BurningArea::SetActivate_Implementation() {
	bPainCausing = true;
	DamagePerSec = 2.f;
	MoveComplete = false;

	// 내려왔을때 Z 값 17840.0
	// 어떻게 부드럽게 액터가 움직이게 만들까? 꼭 Tick 을 써야하나?
}

bool AC_BurningArea::MoreStrog_Validate() {
	return true;
}
void AC_BurningArea::MoreStrog_Implementation() {
	// bPainCausing 으로 활성화 여부를 체크.
	if (bPainCausing) {
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
}