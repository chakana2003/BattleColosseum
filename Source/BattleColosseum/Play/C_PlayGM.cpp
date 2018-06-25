// Fill out your copyright notice in the Description page of Project Settings.

#include "C_PlayGM.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "C_SpawnBox.h"
#include "Lobby/C_LobbyPC.h"
#include "Play/C_PlayPC.h"
#include "UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AC_PlayGM::AC_PlayGM()
{
	bUseSeamlessTravel = true;
}

void AC_PlayGM::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	TArray<AActor*> outer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_SpawnBox::StaticClass(), outer);
	if (outer.GetData()) {
		SpawnBox = Cast<AC_SpawnBox>(outer.Pop());
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("1. Create SpawnBox"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("1-1. Not Create SpawnBox"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("InitGame Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
}

void AC_PlayGM::SwapPlayerControllers(APlayerController * OldPC, APlayerController * NewPC)
{
	if (Cast<AC_LobbyPC>(OldPC)) {
		if (Cast<AC_PlayPC>(NewPC)) {
			Cast<AC_PlayPC>(NewPC)->MyInfo = Cast<AC_LobbyPC>(OldPC)->MyInfo;
			ConnectedPlayerControllers.Add(NewPC);
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. MyInfo Coppy"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		}
		else {
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2-1. NewPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2-2. OldPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SwapPlayerControllers Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
}

void AC_PlayGM::HandleSeamlessTravelPlayer(AController *& C)
{
	/*APlayerController* PC = Cast<APlayerController>(C);
	if (PC) {
		ConnectedPlayerControllers.Add(PC);
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
		if (PC) {
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
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandleSeamlessTravelPlayer Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
}

void AC_PlayGM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AC_PlayGM, ConnectedPlayerControllers);
}

void AC_PlayGM::PostSeamlessTravel()
{
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
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("PostSeamlessTravel Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
}

bool AC_PlayGM::SpawnCharacter_WaitTime_Validate(APlayerController* PC, TSubclassOf<APawn> Character) {
	return true;
}
void AC_PlayGM::SpawnCharacter_WaitTime_Implementation(APlayerController* PC, TSubclassOf<APawn> Character) {
	if (PC->GetPawn()) {
		PC->GetPawn()->Destroy();
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4. Controlled Pawn Destroy Done!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4-1. Not exist Controlled Pawn"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}
	if (SpawnBox) {
		FVector RandPos = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBox->GetActorLocation(), SpawnBox->BoxCompo->GetScaledBoxExtent());
		float Rando = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);
		FQuat RandRot = FQuat(FRotator(0.f, Rando, 0.f));
		
		FTransform SpawnTransform;
		SpawnTransform.SetRotation(RandRot);
		SpawnTransform.SetLocation(RandPos);
		SpawnTransform.SetScale3D(FVector(1.f));

		AActor* SpawnedAct = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), Character, SpawnTransform, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		APawn* Pawn = Cast<APawn>(SpawnedAct);
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5. NewPawn Spawned!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		if (Pawn) {
			PC->Possess(Pawn);
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("6. Possess Done"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("6-1. Possess Error Because Pawn does not exist(not spawn)"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5-1. Pawn does not Spawn(Because SpawnBox not Exist"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SpawnCharacter_WaitTime Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
}