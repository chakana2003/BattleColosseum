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
#include "Play/King/C_KingPawn.h"
#include "Play/Warrior/C_WarriorCharacter.h"


AC_PlayGM::AC_PlayGM()
{
	bUseSeamlessTravel = false;
}

void AC_PlayGM::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);

	// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("InitGame Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	
	TArray<AActor*> outer;	// AActor 배열 임시 저장
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("FirstSpawn"), outer);
	if (outer[0]) {
		// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("1. Create SpawnBox"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
		
		// 맨 처음 스폰박스 배정.
		SpawnBox = Cast<ATriggerBox>(outer[0]);
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("1-1. Not Create SpawnBox"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}

	// UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("StartBox"), outer);
	
	// 시작 위치 지정 박스 스폰 및 할당.
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

	// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SwapPlayerControllers Call"), true, true, FLinearColor(1.f, 1.f, 1.f, 1.f), 10.f);
	
	// 이전에 썼던 컨트롤러를 캐스트
	AC_LobbyPC* LobbyPC = Cast<AC_LobbyPC>(OldPC);
	if (LobbyPC) {
		// 현재 쓰고있는 컨트롤러를 캐스트
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(NewPC);
		if (PlayPC) {
			// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. MyInfo Coppy"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			// Info 옮김.
			// PlayPC->MyInfo = LobbyPC->MyInfo;	//원래코드. 서버에서도 바꿔줘야하니까 해야하지않을까.
			PlayPC->CopyInfo(LobbyPC->MyInfo);		// 수정 코드.
			// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. Load Call"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			ConnectedPlayerControllers.Add(NewPC);
			// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2. ConnectedPlayer Array Add"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
			SendCurrentPC(NewPC);		// PC들의 위젯을 생성하기 위해 생성한 블루프린트 이벤트.
			// PlayPC->PassCharacterToServer(PlayPC->MyInfo);  // 첨부터 스폰하면 안됨..
		}
		else {
			// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2-1. NewPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
		}
	}
	else {
		// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("2-2. OldPC Cast Error"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);
	}
}

void AC_PlayGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(StartTimeHandle, this, &AC_PlayGM::CountdownTimer, 1.0f, true, 0);

	// 5초후 카운트다운 위젯이 나타나기 위해 생성한 블루프린트 이벤트를 호출.
	GetWorldTimerManager().SetTimer(CountdownTimeHandle, this, &AC_PlayGM::BeginStartTimer, 5.0f, false);
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

void AC_PlayGM::CountdownTimer()
{
	auto GS = GetGameState<AC_PlayGS>();

	if (GS)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%f"),GS->LeftStartTime));
		// PopStartTimer() 의 원래자리.

		// LeftStartTimer 가 변경되면 자동으로 호출되는 함수인데 이게 여기 없어도 되지않을까.
		GS->OnRep_LeftTime();

		if (GS->LeftStartTime < 0 && !(GS->DoesStart))
		{
			// 캐릭터 스폰을 위해 남은시간 초기화.
			GS->LeftStartTime = 30.f;
			for (auto PC : ConnectedPlayerControllers) {
				
				// Pawn 변수 저장.
				AC_WarriorCharacter* TempWarrior = Cast<AC_WarriorCharacter>(PC->GetPawn());
				AC_KingPawn* TempKing = Cast<AC_KingPawn>(PC->GetPawn());
				
				// 왕과 워리어를 저장해줌.
				if (TempWarrior) {
					Warriors.Add(TempWarrior);
				}
				else if (TempKing) {
					King = TempKing;
				}
			}
		}

		// 게임 캐릭터가 생성되면 타이머가 초기화됨.
		if (GS->DoesStart) {
			GetWorldTimerManager().ClearTimer(StartTimeHandle);
			EndStartTimer();
		}

		PopStartTimer();		// 수정된 자리.
		GS->LeftStartTime--;	// LeftStartTimer 가 변경되면 GS->OnRep_LeftTime() 이 호출될까.
	}

	
}

void AC_PlayGM::YesSpawn()
{
	for (APlayerController* PC : ConnectedPlayerControllers) {
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
		if (PlayPC) {
			if (PlayPC->GetPawn())
			{
				// 이미 빙의되어있는 Panw 을 제거.
				PlayPC->GetPawn()->Destroy();
			}

			// 랜덤한 위치, 방향 생성.
			FVector RandPos = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBox->GetActorLocation(), SpawnBox->GetComponentsBoundingBox().GetExtent());
			float Rando = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);
			FQuat RandRot = FQuat(FRotator(0.f, Rando, 0.f));

			// 트랜스폼 생성.
			FTransform SpawnTransform;
			SpawnTransform.SetRotation(RandRot);
			SpawnTransform.SetLocation(RandPos);
			SpawnTransform.SetScale3D(FVector(1.f));
			
			// 캐릭터 스폰.
			AActor* SpawnedAct = GetWorld()->SpawnActor<APawn>(PlayPC->MyInfo.SelectCharacter.LobbyCharacter, SpawnTransform);
			
			// 스폰된 액터 빙의.
			APawn* Pawn = Cast<APawn>(SpawnedAct);
			if (Pawn) {
				// KismetSystemLibrary::PrintString(GetWorld(), TEXT("4. YES DOIT!!!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
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
	// 캐릭터 랜덤위치배열 얻기.
	TArray<int> SuffleIndex = SetSpawnLocation();
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("5-1. Pawn does not Spawn(Because SpawnBox not Exist"), true, true, FLinearColor(1.f, 0.1f, 0.1f, 1.f), 10.f);

	for (APlayerController* PC : ConnectedPlayerControllers) {
		if (PC->GetPawn()) {
			// 원래 생성된 캐릭터 삭제.
			PC->GetPawn()->Destroy();
		}
	}

	int yes = 0;		// 배열을 가르키는 변수.
	for (APlayerController* PC : ConnectedPlayerControllers) {
		AC_PlayPC* PlayPC = Cast<AC_PlayPC>(PC);
		if (PlayPC) {
			// 먼저 스폰한 다음에.
			AActor* SpawnedAct = GetWorld()->SpawnActor<APawn>(PlayPC->MyInfo.SelectCharacter.GameCharacter, SpawnBox->GetActorTransform());
			AC_WarriorCharacter* SpawnWarrior = Cast<AC_WarriorCharacter>(SpawnedAct);
			AC_KingPawn* SpawnKing = Cast<AC_KingPawn>(SpawnedAct);
			
			// 용병인지.
			if (SpawnWarrior) {
				// StartBox 트랜스폼 생성.
				FVector RandPos = UKismetMathLibrary::RandomPointInBoundingBox(StartBoxes[SuffleIndex[yes]]->GetActorLocation(), StartBoxes[SuffleIndex[yes]]->GetComponentsBoundingBox().GetExtent());
				float Rando = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);
				FQuat RandRot = FQuat(FRotator(0.f, Rando, 0.f));

				FTransform SpawnTransform;
				SpawnTransform.SetRotation(RandRot);
				SpawnTransform.SetLocation(RandPos);
				SpawnTransform.SetScale3D(FVector(1.f));

				// 새로운 위치에 플레이어가 선택한 용병 Pawn 스폰
				SpawnWarrior->SetActorTransform(SpawnTransform);

				APawn* Pawn = Cast<APawn>(SpawnedAct);
				if (Pawn) {
				// 빙의
					UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4. YES DOIT!!!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
					PlayPC->PossessingPawn(Pawn);
					SendWarriorFromCode(PC);
				}
			}	// 왕인지
			else if(SpawnKing) {
				// 가운데 왕 Pawn 스폰

				// 빙의
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("4. YES DOIT!!!"), true, true, FLinearColor(0.3f, 1.f, 0.3f, 1.f), 10.f);
				PlayPC->PossessingPawn(SpawnKing);
			}
			yes++;
		}
	}

	// 초 증가 타이머함수 실행.
	GetWorldTimerManager().SetTimer(GameTimeHandle, this, &AC_PlayGM::GameTime, 0.01f, true);
}

TArray<int> AC_PlayGM::SetSpawnLocation() {
	TArray<int> TempSuffle;
	if (StartBoxes[0]) {
		for (int i = 0; i < StartBoxes.Num(); i++) {
			TempSuffle.Add(i);
		}

		for (int i = 0; i < 100; i++) {
			int First = (int)FMath::FRandRange(0.f,(float)StartBoxes.Num());
			int Second = (int)FMath::FRandRange(0.f, (float)StartBoxes.Num());
			
			int temp = TempSuffle[First];
			
			TempSuffle[First] = TempSuffle[Second];
			TempSuffle[Second] = temp;
		}

		for (int i = 0; i < TempSuffle.Num(); i++) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("TempSuffle[%d] : %d"), i,TempSuffle[i]));
		}
		return TempSuffle;
		//int yes = 0;										// 배열을 가르키는 변수.
		//for (AC_WarriorCharacter* Warri : Warriors) {		// 워리어들의 위치를 지정하는 변수.
		//	FVector RandPos = UKismetMathLibrary::RandomPointInBoundingBox(StartBoxes[TempSuffle[yes]]->GetActorLocation(), StartBoxes[TempSuffle[yes]]->GetComponentsBoundingBox().GetExtent());
		//	float Rando = UKismetMathLibrary::RandomFloatInRange(0.f, 360.f);
		//	FQuat RandRot = FQuat(FRotator(0.f, Rando, 0.f));

		//	FTransform SpawnTransform;
		//	SpawnTransform.SetRotation(RandRot);
		//	SpawnTransform.SetLocation(RandPos);
		//	SpawnTransform.SetScale3D(FVector(1.f));

		//	Warri->SetActorTransform(SpawnTransform);
		//	++yes;
		//}
	}
	return TempSuffle;
}

void AC_PlayGM::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	ErrorMessage = TEXT("Nop"); // 중도 참여 막기
}

void AC_PlayGM::GameTime() {
	AC_PlayGS* GS = GetGameState<AC_PlayGS>();

	if (GS) {
		GS->ms++;
	}
}