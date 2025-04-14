// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueArena.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueArena : public ABloque
{
	GENERATED_BODY()

public:
	ABloqueArena();

	//virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	
};
