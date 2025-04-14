// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bloque.generated.h"

class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_012025_API ABloque : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    ABloque();

protected:
    // Componente de malla estática
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
    UStaticMeshComponent* MallaBloque;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    float RotationSpeed;
    
    // Posici—n inicial del bloque al comenzar el juego
    FVector PosicionInicial;

    // Control de movimiento
    int TipoMovimiento;            // 0=X, 1=Y, 2=Z, -1=sin movimiento
    float FloatSpeed;              // Velocidad de movimiento
    bool bPuedeMoverse;            // ÀDebe moverse?

    // Direcciones para alternar cuando llegue a los extremos
    int DireccionMovimientoX;
    int DireccionMovimientoY;
    int DireccionMovimientoZ;

	float AlturaMaxima; // Altura máxima que alcanzarán los bloques (200 unidades)
	float PosicionInicialZ; // Posición Z inicial del bloque
};

/*
 Bloque.h
 #pragma once

 #include "CoreMinimal.h"
 #include "GameFramework/Actor.h"
 #include "Bloque.generated.h"

 UCLASS()
 class BOMBERMAN_012025_API ABloque : public AActor
 {
     GENERATED_BODY()

 public:
     ABloque();

 protected:
     virtual void BeginPlay() override;

 public:
     virtual void Tick(float DeltaTime) override;

     UPROPERTY()
     UStaticMeshComponent* MallaBloque;

     // Posici—n inicial del bloque al comenzar el juego
     FVector PosicionInicial;

     // Control de movimiento
     int TipoMovimiento;            // 0=X, 1=Y, 2=Z, -1=sin movimiento
     float FloatSpeed;              // Velocidad de movimiento
     bool bPuedeMoverse;            // ÀDebe moverse?

     // Direcciones para alternar cuando llegue a los extremos
     int DireccionMovimientoX;
     int DireccionMovimientoY;
     int DireccionMovimientoZ;
 };
 */
