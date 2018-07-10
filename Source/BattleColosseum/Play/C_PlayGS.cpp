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

	PreStart = false;
	DoesStart = false;
	ms = 0.f;
	sec = 0;
	min = 0;
	hour = 0;

	LeftStartTime = 10.f;

	WaitForDeleteArea = false;
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

	DOREPLIFETIME(AC_PlayGS, LeftStartTime);
	DOREPLIFETIME(AC_PlayGS, DoesStart);
	DOREPLIFETIME(AC_PlayGS, PreStart);
	DOREPLIFETIME(AC_PlayGS, ms);
	DOREPLIFETIME(AC_PlayGS, sec);
	DOREPLIFETIME(AC_PlayGS, min);
	DOREPLIFETIME(AC_PlayGS, hour);
	DOREPLIFETIME(AC_PlayGS, WaitForDeleteArea);
}

void AC_PlayGS::OnRep_LeftTime()
{
	if (HasAuthority()) {
		AC_PlayGM* GM = Cast<AC_PlayGM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM) {
			if (LeftStartTime < 0.f) {
				if(!PreStart)			// 맨 처음 캐릭터 스폰할 때
				{
					GM->YesSpawn();
					PreStart = true;
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("PreStart Turn True!")));
				}
				else if (!DoesStart)	// 진짜 게임 시작.
				{
					GM->RealStartGame();
					DoesStart = true;

					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("DoesStart  Trun True!")));
				}
			}
		}
	}
}

void AC_PlayGS::TimeIncrese() {
	if (ms >= 100.f) {
		ms = 0;
		sec++;
		if (sec >= 60) {
			sec = 0;
			min++;
			if (min >= 60) {
				min = 0;
				hour++;
			}
		}
	}

	// 지역 제한 확인
	if (HasAuthority()) {
		AC_PlayGM* GM = Cast<AC_PlayGM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM) {
			// 0분째가 아닐 때, 4분마다 지역 제한.
			if (min != 0 && min % 4 == 0) {
				GM->StartBurning();
			}
		}
	}
	
	
}