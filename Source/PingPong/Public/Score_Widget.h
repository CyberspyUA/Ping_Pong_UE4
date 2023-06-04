// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Score_Widget.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UScore_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* FirstPlayerId;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* FirstPlayerScore;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* SecondPlayerId;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* SecondPlayerScore;

public:
	FString SFirstPlayerId;

	void UpdateScore(FString PlayerId, int NewScore);
};
