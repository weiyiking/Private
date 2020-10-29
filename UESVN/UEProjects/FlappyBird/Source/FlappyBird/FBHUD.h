// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FBHUD.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFBHUD : public AHUD
{
	GENERATED_BODY()
	

protected:

	virtual void DrawHUD() override;

};
