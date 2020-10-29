// Fill out your copyright notice in the Description page of Project Settings.

#include "FBHUD.h"
#include <Kismet/GameplayStatics.h>
#include "FBGameState.h"

void AFBHUD::DrawHUD()
{
	Super::DrawHUD();
	if (AFBGameState* Gs = Cast<AFBGameState>(UGameplayStatics::GetGameState(this)))
	{
		DrawText(FString::FromInt(Gs->GetScore()), FLinearColor::Red, 20, 50);
	}
}
