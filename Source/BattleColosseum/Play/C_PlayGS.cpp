// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayGS.h"
#include "Play/C_PlayGM.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Play/C_PlayGM.h"


AC_PlayGS::AC_PlayGS() {
	start = false;
	ms = 0.f;
	sec = 0;
	min = 0;
	hour = 0;

	leftTime = 10.f;
}

void AC_PlayGS::Tick(float DeltaSeconds){
	GetServerWorldTimeSeconds();

	if (ms >= 1.f) {
		ms = 0.f;
		sec++;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("%d is CurrentTime"), sec));
	}

	if (sec >= 60) {
		sec = 0;
		min++;
	}

	if (min >= 60) {
		min = 0;
		hour++;
	}
}

void AC_PlayGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AC_PlayGS, leftTime);
}

void AC_PlayGS::OnRep_LeftTime()
{
	AC_PlayGM* GM = Cast<AC_PlayGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM) {
		if (leftTime < 0.f) {
			if (HasAuthority())
			{
				GM->YesSpawn();
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("StartGame Call In PlayGS")));
			}
		}
	}
}

