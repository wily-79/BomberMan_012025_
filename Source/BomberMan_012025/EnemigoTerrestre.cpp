// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTerrestre.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
    // Carga el material
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("Material'/Game/StarterContent/Shapes/Ediciones/ColorEnemigoTerrestre.ColorEnemigoTerrestre'"));
    Material = MaterialFinder.Object;
}

void AEnemigoTerrestre::BeginPlay()
{
    Super::BeginPlay();

    // Asigna el material al mesh
    if (StaticMesh)
    {
        StaticMesh->SetMaterial(0, Material);
    }
}
