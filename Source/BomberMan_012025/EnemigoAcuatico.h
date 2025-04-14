// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAcuatico.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API AEnemigoAcuatico : public AEnemigo
{
	GENERATED_BODY()
public:
    AEnemigoAcuatico();

protected:
    virtual void BeginPlay() override;
};
