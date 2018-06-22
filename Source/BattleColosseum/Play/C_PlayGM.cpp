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

}

void AC_PlayGM::SwapPlayerControllers(APlayerController * OldPC, APlayerController * NewPC)
{
	if (Cast<AC_LobbyPC>(OldPC)) {
		if (Cast<AC_PlayPC>(NewPC)) {
			Cast<AC_PlayPC>(NewPC)->MyInfo = Cast<AC_LobbyPC>(OldPC)->MyInfo;
		}
	}
}

void AC_PlayGM::HandleSeamlessTravelPlayer(AController *& C)
{
	if (ConnectedPlayerControllers.IsValidIndex(0)) {
		for (APlayerController* TempPC : ConnectedPlayerControllers) {
			AC_PlayPC* PC = Cast<AC_PlayPC>(TempPC);
			if (PC) {
				SpawnCharacter_WaitTime(PC, PC->MyInfo.SelectCharacter.GameCharacter);
			}
		}
	}
	
}

void AC_PlayGM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AC_PlayGM, ConnectedPlayerControllers);
}

bool AC_PlayGM::SpawnCharacter_WaitTime_Validate(APlayerController* PC, TSubclassOf<APawn> Character) {
	return true;
}
void AC_PlayGM::SpawnCharacter_WaitTime_Implementation(APlayerController* PC, TSubclassOf<APawn> Character) {
	if (PC->GetPawn()) {
		PC->GetPawn()->Destroy();
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
		if (Pawn) {
			PC->Possess(Pawn);
		}
	}
	
}