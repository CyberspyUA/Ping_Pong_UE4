// Fill out your copyright notice in the Description page of Project Settings.


#include "Score_Widget.h"

void UScore_Widget::UpdateScore(FString PlayerId, int NewScore) {
	if (PlayerId.Equals(SFirstPlayerId)) {
		FirstPlayerScore->SetText(FText::AsNumber(NewScore));
	}
	else {
		SecondPlayerScore->SetText(FText::AsNumber(NewScore));
	}
}