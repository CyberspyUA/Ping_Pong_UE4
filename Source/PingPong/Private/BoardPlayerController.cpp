// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPlayerController.h"
#include "BoardPawn.h"
#include "GameFramework/PlayerInput.h"

void ABoardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	this->InputComponent->BindAxis("MoveLeftRight", this, &ABoardPlayerController::MovePawnLeftRight);
}

void ABoardPlayerController::BeginPlay() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("StartMenu")) {
		if (MainMenuWidgetClass && MainMenuWidget == nullptr) {
			MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		}

		if (WaitingAreaWidgetClass && WaitingAreaWidget == nullptr) {
			WaitingAreaWidget = CreateWidget<UWaitingAreaWidget>(GetWorld(), WaitingAreaWidgetClass);
		}

		if (PlayersScoreWidgetClass && PlayersScoreWidget == nullptr) {
			PlayersScoreWidget = CreateWidget<UPlayersScoreWidget>(GetWorld(), PlayersScoreWidgetClass);
		}

		if (MainMenuWidget != nullptr) {
			MainMenuWidget->AddToViewport();
			this->SetShowMouseCursor(true);
			this->SetInputMode(FInputModeUIOnly());
		}
	}
	else {
		if (this == GetWorld()->GetFirstPlayerController()) {
			this->PlayerId = FString("Player 1");
		}
		else {
			this->PlayerId = FString("Player 2");
		}

		this->SetShowMouseCursor(false);
		this->SetInputMode(FInputModeGameOnly());

		if (PlayersScoreWidget != nullptr) {
			PlayersScoreWidget->AddToViewport();
		}
	}
}

void ABoardPlayerController::OnPossess(APawn* NewPawn) {
	ABoardPawn* BPawn = Cast<ABoardPawn>(NewPawn);
	if (BPawn != nullptr) {
		FVector Start = GetPawn()->GetActorLocation();
		FVector Forward = GetPawn()->GetActorForwardVector();

		TArray<FHitResult> OutHits;
		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

		TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(),Start,Start - Forward * 2000.f,FVector(0.5f, 0.5f, 100.f),FRotator(),
			TraceObjectTypes,false,TArray<AActor*>(),EDrawDebugTrace::None,OutHits,true);

		for (FHitResult& HitResult : OutHits) {
			if (HitResult.Actor != nullptr) {
				AGateActor* Gate = Cast<AGateActor>(HitResult.Actor);

				if (Gate != nullptr) {
					Gate->PlayerId = this->PlayerId;
					break;
				}
			}
		}
	}
}

void ABoardPlayerController::MovePawnLeftRight(float Value) {
	if (Value != 0.f) {
		ABoardPawn* ControlledPawn = GetPawn<ABoardPawn>();

		if (ControlledPawn != nullptr) {
			ControlledPawn->Multicast_MoveLeftRight(Value);
		}
	}
}

void ABoardPlayerController::ShowWaitingArea(FString UIText) {
	if(WaitingAreaWidget != nullptr) {
		WaitingAreaWidget->Text->SetText(FText::FromString(UIText));
		WaitingAreaWidget->AddToViewport();

		this->SetShowMouseCursor(true);
		this->SetInputMode(FInputModeUIOnly());
	}
}