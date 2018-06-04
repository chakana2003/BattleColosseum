// Fill out your copyright notice in the Description page of Project Settings.

#include "C_BCGI.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu/C_MainMenuWidget.h"
#include "MainMenu/C_CreatePlayerWidget.h"


UC_BCGI::UC_BCGI() {
	SAVEGAME = "SAVEGAME";

}

void UC_BCGI::SaveGameCheck()
{
	if (UGameplayStatics::DoesSaveGameExist(SAVEGAME, 0)) {
		ShowMainMenu();
	}
	else {
		ShowCreateMenu();
	}
}

void UC_BCGI::ShowMainMenu()
{
	FStringClassReference MainMenuClass(TEXT("WidgetBlueprint'/Game/UI/MainMenu/WB_CreatePlayer.WB_CreatePlayer'"));
	if (UClass* WidgetClass = MainMenuClass.TryLoadClass<UUserWidget>()) {
		MainMenuWidget = Cast<UC_MainMenuWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClass));
		MainMenuWidget->AddToViewport();
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	}
}

void UC_BCGI::ShowCreateMenu()
{
	FStringClassReference CreatePlayerClass(TEXT("WidgetBlueprint'/Game/UI/MainMenu/WB_CreatePlayer.WB_CreatePlayer'"));
	if (UClass* WidgetClass = CreatePlayerClass.TryLoadClass<UUserWidget>()) {
		CreatePlayerWidget = Cast<UC_CreatePlayerWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClass));
		CreatePlayerWidget->AddToViewport();
		CreatePlayerWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	}
}
