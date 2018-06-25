// Fill out your copyright notice in the Description page of Project Settings.

#include "C_ChatingWindow.h"
#include "Components/EditableTextBox.h"

void UC_ChatingWindow::NativeConstruct() {
	ChattingInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChatEnter")));
}

void UC_ChatingWindow::SetFocusTextbox(APlayerController* A) {
	if (ChattingInput) {
		ChattingInput->SetUserFocus(A);
		UE_LOG(LogClass, Warning, TEXT("Cast Done!"));
	}
	else {
		UE_LOG(LogClass, Warning, TEXT("Not Cast!"));
	}
	
}
