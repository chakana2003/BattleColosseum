// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayGS.h"
#include "Play/C_PlayGM.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"


AC_PlayGS::AC_PlayGS() {
	start = false;
	ms = 0.f;
	sec = 0;
	min = 0;
	hour = 0;
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
