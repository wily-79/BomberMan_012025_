// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo.h"

AEnemigoAereo::AEnemigoAereo()
{
    // Carga el material
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("Material'/Game/StarterContent/Shapes/Ediciones/ColorEnemigoAereo.ColorEnemigoAereo'"));
    Material = MaterialFinder.Object;
}

void AEnemigoAereo::BeginPlay()
{
    Super::BeginPlay();

    // Asigna el material al mesh
    if (StaticMesh)
    {
        StaticMesh->SetMaterial(0, Material);
    }
}
