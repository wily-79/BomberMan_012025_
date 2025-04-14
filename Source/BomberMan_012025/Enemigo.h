// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

UCLASS()
class BOMBERMAN_012025_API AEnemigo : public ACharacter
{
	GENERATED_BODY()
    
    FVector CurrentDirection;

    UFUNCTION()
    void ElegirNuevaDireccion();
public:
	AEnemigo();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
    UMaterialInterface* Material;
    
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMesh;
    
    UPROPERTY(EditAnywhere, Category = "Movimiento")
    float MoveSpeed = 0.3f;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
