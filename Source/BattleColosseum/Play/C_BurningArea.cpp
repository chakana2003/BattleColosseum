// Fill out your copyright notice in the Description page of Project Settings.

#include "C_BurningArea.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"


AC_BurningArea::AC_BurningArea() {
	bReplicates = true;
	bReplicateMovement = true;

	DamagePerSec = 0.f;
	// Pain Causing Volume �� ����Ǿ��ִ� �������ִ� Bool ��.
	bPainCausing = false;
	Strong = 0;

	MoveComplete = true;

	Tags.Add(TEXT("BurningArea"));
}

void AC_BurningArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AC_BurningArea, Strong);
	DOREPLIFETIME(AC_BurningArea, MyOrder);
	DOREPLIFETIME(AC_BurningArea, MoveComplete);
}

void AC_BurningArea::BeginPlay()
{
	GetWorldTimerManager().SetTimer(CheckTimeHandler, this, &AC_BurningArea::CheckRaise, 0.1f,true);
}

bool AC_BurningArea::CheckRaise_Validate() {
	return true;
}
void AC_BurningArea::CheckRaise_Implementation()
{
	// bPainCausing �� true �� �ǰų� MoveComplete �� true �� �ƴҶ�(!)
	if (bPainCausing && !MoveComplete) {
		SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, MoveingRate));

		// ���� �ؿ��� �ö���⶧���� >= �� ��.
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
}

bool AC_BurningArea::MoreStrog_Validate() {
	return true;
}
void AC_BurningArea::MoreStrog_Implementation() {
	// bPainCausing ���� Ȱ��ȭ ���θ� üũ.
	if (bPainCausing) {
		Strong++;
		switch (Strong)
		{
		case 1:
			DamagePerSec = 0.2f;
			break;
		case 2:
			DamagePerSec = 0.5f;
			break;
		case 3:
			DamagePerSec = 1.f;
			break;
		case 4:
			DamagePerSec = 1.8f;
			break;
		case 5:
			DamagePerSec = 2.5f;
			break;
		case 6:
			DamagePerSec = 3.f;
			break;
		case 7:
			DamagePerSec = 5.f;
			break;
		default:
			break;
		}
	}
}