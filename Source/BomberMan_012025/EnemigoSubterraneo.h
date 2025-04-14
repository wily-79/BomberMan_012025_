// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoSubterraneo.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API AEnemigoSubterraneo : public AEnemigo
{
	GENERATED_BODY()
    
public:
    AEnemigoSubterraneo();

protected:
    virtual void BeginPlay() override;

};
