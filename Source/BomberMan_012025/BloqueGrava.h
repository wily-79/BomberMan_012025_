// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueGrava.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueGrava : public ABloque
{
	GENERATED_BODY()

public:
	ABloqueGrava();

	//virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

};
