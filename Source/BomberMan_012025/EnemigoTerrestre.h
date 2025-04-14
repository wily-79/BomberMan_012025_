// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API AEnemigoTerrestre : public AEnemigo
{
	GENERATED_BODY()
	
public:
    AEnemigoTerrestre();

protected:
    virtual void BeginPlay() override;
};
