// Fill out your copyright notice in the Description page of Project Settings.
#include "Bloque.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ABloque::ABloque()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;
    MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
    //RootComponent = MeshComp;
    MallaBloque->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    if (ObjetoMallaBloque.Succeeded())
    {
        MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);
        MallaBloque->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    TipoMovimiento = -1;
    FloatSpeed = 100.0f;
    bPuedeMoverse = false;
    DireccionMovimientoX = 1;
    DireccionMovimientoY = 1;
    DireccionMovimientoZ = 1;
    AlturaMaxima = 200.0f;
}

void ABloque::BeginPlay()
{
    Super::BeginPlay();
    PosicionInicial = GetActorLocation();
    // Guardar específicamente la posición Z inicial
    PosicionInicialZ = PosicionInicial.Z;
}

void ABloque::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bPuedeMoverse)
    {
        FVector Pos = GetActorLocation();
        float Movimiento = FloatSpeed * DeltaTime;

        // Para el movimiento en eje Z de los bloques de ladrillo
        if (TipoMovimiento == 2) // Movimiento en Z
        {
            // Si está subiendo y alcanza la altura máxima
            if (DireccionMovimientoZ > 0 && Pos.Z >= PosicionInicialZ + AlturaMaxima)
            {
                DireccionMovimientoZ = -1; // Cambiar dirección a bajar
            }
            // Si está bajando y llega a la posición inicial
            else if (DireccionMovimientoZ < 0 && Pos.Z <= PosicionInicialZ)
            {
                DireccionMovimientoZ = 1;  // Cambiar dirección a subir
            }

            // Aplicar el movimiento en Z
            Pos.Z += DireccionMovimientoZ * Movimiento;
            SetActorLocation(Pos);
        }
        // Para otros tipos de movimiento (no ladrillo)
        else
        {
            float RangoMax = 200.0f;
            bool AjustarDireccion = false;

            // Verificar si alcanzó el rango máximo en cualquier eje
            if (FMath::Abs(Pos.X - PosicionInicial.X) >= RangoMax && DireccionMovimientoX != 0)
            {
                DireccionMovimientoX *= -1;
                AjustarDireccion = true;
            }
            if (FMath::Abs(Pos.Y - PosicionInicial.Y) >= RangoMax && DireccionMovimientoY != 0)
            {
                DireccionMovimientoY *= -1;
                AjustarDireccion = true;
            }
            if (FMath::Abs(Pos.Z - PosicionInicial.Z) >= RangoMax && DireccionMovimientoZ != 0)
            {
                DireccionMovimientoZ *= -1;
                AjustarDireccion = true;
            }

            // Aplicar movimiento en cada eje según corresponda DESPLAZAMIENTO
            if (DireccionMovimientoX != 0)
                Pos.X += DireccionMovimientoX * Movimiento;
            if (DireccionMovimientoY != 0)
                Pos.Y += DireccionMovimientoY * Movimiento;
            if (DireccionMovimientoZ != 0)
                Pos.Z += DireccionMovimientoZ * Movimiento;

            SetActorLocation(Pos);
        }
    }
}