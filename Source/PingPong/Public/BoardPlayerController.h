// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuWidget.h"
#include "WaitingAreaWidget.h"
#include "PlayersScoreWidget.h"
#include "BoardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API ABoardPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MovePawnLeftRight(float Value);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWaitingAreaWidget> WaitingAreaWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPlayersScoreWidget> PlayersScoreWidgetClass;

	UPROPERTY(EditAnywhere)
	class UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere)
	class UWaitingAreaWidget* WaitingAreaWidget;

	UPROPERTY(EditAnywhere)
	class UPlayersScoreWidget* PlayersScoreWidget;

public:
	void ShowWaitingArea(FString UIText = FString("Waiting for another player to join..."));

	virtual void OnPossess(APawn* Pawn) override;

	FString PlayerId;
};
