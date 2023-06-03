// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayersScoreWidget.h"

void UPlayersScoreWidget::UpdateScore(FString PlayerId, int NewScore) {
	if (PlayerId.Equals(SThisPlayerId)) {
		ThisPlayerScore->SetText(FText::AsNumber(NewScore));
	}
	else {
		OtherPlayerScore->SetText(FText::AsNumber(NewScore));
	}
}