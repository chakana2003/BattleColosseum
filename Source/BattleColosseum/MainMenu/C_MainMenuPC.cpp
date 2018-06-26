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
		if (CamOrder == 0) {
			CamOrder++;
			if (Cameras[0]) {
				SetViewTargetWithBlend(Cameras[0], 1.f, EViewTargetBlendFunction::VTBlend_EaseIn, 1.f);
			}
		}
		else if (CamOrder == 1) {
			CamOrder++;
			if (Cameras[1]) {
				SetViewTargetWithBlend(Cameras[1], 1.f, EViewTargetBlendFunction::VTBlend_EaseIn, 1.f);
			}
		}
		else if (CamOrder == 2) {
			CamOrder = 0;
			if (Cameras[2]) {
				SetViewTargetWithBlend(Cameras[2], 1.f, EViewTargetBlendFunction::VTBlend_EaseIn, 1.f);
			}
		}
		else {
			CamOrder = 0;
		}
	}
}