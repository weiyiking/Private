// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FBGameState.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFBGameState : public AGameStateBase
{
	GENERATED_BODY()
	

public:

	void AddScore(int32 Score = 1) { this->Score += Score; };
	int32 GetScore() { return Score; }

protected:

	int32 Score;
};
