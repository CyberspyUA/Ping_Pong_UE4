// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PingPongGameInstance.h"
#include "BoardPlayerController.h"

void UMainMenuWidget::NativeOnInitialized() {
	if (StartSessionButton != nullptr) {
		StartSessionButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Server_StartSession);
	}

	if (JoinSessionButton != nullptr) {
		JoinSessionButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Server_JoinSession);
	}

	if (ExitGameButton != nullptr) {
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
	}
}

void UMainMenuWidget::Client_StartSession_Implementation() {
	this->RemoveFromViewport();

	// add waiting area to viewport
	ABoardPlayerController* PlayerController = Cast<ABoardPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->ShowWaitingArea();
}

void UMainMenuWidget::Server_StartSession_Implementation() {
	// start session
	UPingPongGameInstance* PPGameInst = Cast<UPingPongGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PPGameInst->StartGame();

	Client_StartSession();
}

void UMainMenuWidget::Client_JoinSession_Implementation() {
	this->RemoveFromViewport();

	ABoardPlayerController* PlayerController = Cast<ABoardPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->ShowWaitingArea(FString("Searching for an active game..."));
}


void UMainMenuWidget::Server_JoinSession_Implementation() {
	// join session

	UPingPongGameInstance* PPGameInst = Cast<UPingPongGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PPGameInst->JoinGame();

	Client_JoinSession();
	// start game
}

void UMainMenuWidget::ExitGame() {
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}