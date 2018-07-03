// Fill out your copyright notice in the Description page of Project Settings.

#include "C_MainMenuPC.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu/C_MainMenuWidget.h"
#include "MainMenu/C_CreatePlayerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void AC_MainMenuPC::BeginPlay() {
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	TArray<AActor*> outer;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("StartCam"), outer);
	for (AActor* temp : outer) {
		ACameraActor* Cam = Cast<ACameraActor>(temp);
		if (Cam) {
			Cameras.Add(Cam);
		}
	}
	if (outer[0]) {
		ACameraActor* StartCam = Cast<ACameraActor>(outer[0]);
		SetViewTarget(StartCam);
	}

	CamOrder = 1;
	loopFloat = 0.01f;
}

void AC_MainMenuPC::Tick(float DeltaSecond) {
	Super::Tick(DeltaSecond);
	loopFloat = loopFloat + loopFloat*DeltaSecond;
	if (loopFloat > 3.f) {
		loopFloat = 0.01f;
		if (Cameras.Num() > CamOrder) {
			SetViewTargetWithBlend(Cameras[CamOrder], 2.f, EViewTargetBlendFunction::VTBlend_EaseInOut, 5.f);
			CamOrder++;
		}
		else {
			CamOrder = 0;
			SetViewTargetWithBlend(Cameras[CamOrder], 2.f, EViewTargetBlendFunction::VTBlend_EaseInOut, 5.f);
			CamOrder++;
		}
	}
}