// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueRoble.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueRoble : public ABloque
{
	GENERATED_BODY()

public:
	ABloqueRoble();

	//virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

};
