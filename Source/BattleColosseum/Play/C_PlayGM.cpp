// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayGM.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Lobby/C_LobbyPC.h"
#include "Play/C_PlayPC.h"
#include "UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Engine/TriggerBox.h"
#include "Math/Box.h"
#include "Play/C_PlayGS.h"
#include "Play/C_PlayGS.h"
#include "TimerManager.h"
#include "Play/C_SpawnBox.h"


AC_PlayGM::AC_PlayGM()
{
	bUseSeamlessTravel = false;
}

void AC_PlayGM::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("InitGame Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	TArray<AActor*> outer;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("FirstSpawn"), outer);
	if (outer[0]) {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("1. Create SpawnBox"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		SpawnBox = Cast<ATriggerBox>(outer[0]);
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("1-1. Not Create SpawnBox"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("StartBox"), outer);	// 시작 위치 지정 박스 스폰 및 할당.
	if (outer[0]) {
		for (AActor* out : outer) {
			ATriggerBox* TB = Cast<ATriggerBox>(out);
			if (TB) {
				StartBoxes.Add(TB);
			}
		}
	}
}

void AC_PlayGM::SwapPlayerControllers(APlayerController * OldPC, APlayerController * NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SwapPlayerControllers Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	AC_LobbyPC* LobbyPC = Cast<AC_LobbyPC>(OldPC);
	if (LobbyPC) {
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(NewPC);
		if (PlayPC) {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. MyInfo Coppy"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			PlayPC->MyInfo = LobbyPC->MyInfo;
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. Load Call"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			ConnectedPlayerControllers.Add(NewPC);
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. ConnectedPlayer Array Add"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			// PlayPC->PassCharacterToServer(PlayPC->MyInfo);  // 첨부터 스폰하면 안됨..
		}
		else {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2-1. NewPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2-2. OldPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}
}

void AC_PlayGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(StartTimeHandle,
		this,
		&AC_PlayGM::StartTimer,
		1.0f,
		true,
		0);
}

void AC_PlayGM::CallSpawn()
{
	if (ConnectedPlayerControllers.IsValidIndex(0)) {
		for (APlayerController* PC : ConnectedPlayerControllers) {
			AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
			PlayPC->PassCharacterToServer(PlayPC->MyInfo);
		}
	}
}

void AC_PlayGM::StartTimer()
{
	auto GS = GetGameState<AC_PlayGS>();

	if (GS)
	{
		GS->leftTime--;
		if (HasAuthority())
		{
			GS->OnRep_LeftTime();
			if (GS->leftTime < 0 && !(GS->DoesStart))
			{
				GS->leftTime = 30.f;
			}
		}
		if (GS->DoesStart) {
			GetWorldTimerManager().ClearTimer(StartTimeHandle);
		}
	}
}

void AC_PlayGM::YesSpawn()
{
	for (APlayerController* PC : ConnectedPlayerControllers) {
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
		if (PlayPC) {
			if (PlayPC->GetPawn())
			{
				PlayPC->GetPawn()->Destroy();
			}
			FVector RandPos = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBox->GetActorLocation(), SpawnBox->GetComponentsBoundingBox().GetExtent());
			float Rando = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);
			FQuat RandRot = FQuat(FRotator(0.f, Rando, 0.f));

			FTransform SpawnTransform;
			SpawnTransform.SetRotation(RandRot);
			SpawnTransform.SetLocation(RandPos);
			SpawnTransform.SetScale3D(FVector(1.f));
			AActor* SpawnedAct = GetWorld()->SpawnActor<APawn>(PlayPC->MyInfo.SelectCharacter.GameCharacter, SpawnTransform);
			
			APawn* Pawn = Cast<APawn>(SpawnedAct);
			if (Pawn) {
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4. YES DOIT!!!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
				PlayPC->PossessingPawn(Pawn);
			}
		}
	}
}

void AC_PlayGM::HandleSeamlessTravelPlayer(AController *& C)
{
	Super::HandleSeamlessTravelPlayer(C);

	/*UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandleSeamlessTravelPlayer Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%s is AController Class"), *(C->GetName())));
	APlayerController* PC = Cast<APlayerController>(C);
	if (PC) {
		ConnectedPlayerControllers.Add(PC);
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
		if (PlayPC) {
			SpawnCharacter_WaitTime(PlayPC, PlayPC->MyInfo.SelectCharacter.GameCharacter);
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("3. Wait Time Spawn Done!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		}
		else {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("3-1. PC to AC_PlayPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("3-2. New Controller Cast to PlayerController Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}*/
}

void AC_PlayGM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_PlayGM, ConnectedPlayerControllers);

}

void AC_PlayGM::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	/*
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("PostSeamlessTravel Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	if (ConnectedPlayerControllers.IsValidIndex(0)) {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Index of ConnectedPlayerControllers is Valid"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		for (APlayerController* PC : ConnectedPlayerControllers) {
			AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
			if (PlayPC) {
				SpawnCharacter_WaitTime(PlayPC, PlayPC->MyInfo.SelectCharacter.GameCharacter);
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("3. SpawnCharacter Function Called!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			}
			else {
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("3-1. Pc to PlayPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
			}
		}
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Index of ConnectedPlayerControllers is INVALID"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}*/
}

bool AC_PlayGM::SpawnCharacter_WaitTime_Validate(APlayerController* PC, TSubclassOf<APawn> Character) {
	return true;
}
void AC_PlayGM::SpawnCharacter_WaitTime_Implementation(APlayerController* PC, TSubclassOf<APawn> Character) {
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SpawnCharacter_WaitTime Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
	if (PlayPC) {
		if (PlayPC->GetPawn()) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%s is Possess Pawn Name of PlayPC - 10"), *(PC->GetPawn()->GetName())));
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4. Controlled Pawn Destroy Done!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			PlayPC->GetPawn()->Destroy();
		}
		else {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4-1. Not exist Controlled Pawn"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
		if (PlayPC->GetPawn()) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%s is Possess Pawn Name of PlayPC - 10"), *(PC->GetPawn()->GetName())));
		}
		if (SpawnBox) {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5. NewPawn Spawned!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			FVector RandPos = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBox->GetActorLocation(), SpawnBox->GetComponentsBoundingBox().GetExtent());
			float Rando = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);
			FQuat RandRot = FQuat(FRotator(0.f, Rando, 0.f));

			FTransform SpawnTransform;
			SpawnTransform.SetRotation(RandRot);
			SpawnTransform.SetLocation(RandPos);
			SpawnTransform.SetScale3D(FVector(1.f));

			AActor* SpawnedAct = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), Character, SpawnTransform, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (SpawnedAct) {
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5. SpawnedAct Cast To APawn!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
				APawn* Pawn = Cast<APawn>(SpawnedAct);
				if (Pawn) {
					UKismetSystemLibrary::PrintString(GetWorld(), TEXT("6. Possess Done"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
					PlayPC->PossessingPawn(Pawn);
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%s is Possess Pawn Name of PlayPC - 1"), *(PC->GetPawn()->GetName())));
				}
				else
				{
					UKismetSystemLibrary::PrintString(GetWorld(), TEXT("6-1. Possess Error Because Pawn does not exist(not spawn)"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
				}
			}
			else {
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5-2. SpawnedAct is Invalid"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
			}
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%s is Possess Pawn Name of PlayPC - 2"), *(PC->GetPawn()->GetName())));
		}
		else {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5-1. Pawn does not Spawn(Because SpawnBox not Exist"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%s is Possess Pawn Name of PlayPC - 3"), *(PC->GetPawn()->GetName())));
}

bool AC_PlayGM::RealStartGame_Validate() {
	return true;
}
void AC_PlayGM::RealStartGame_Implementation() {
	// 캐릭터 위치 변경.
}

void AC_PlayGM::SetSpawnLocation() {

}