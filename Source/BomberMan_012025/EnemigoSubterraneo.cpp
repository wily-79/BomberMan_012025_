// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoSubterraneo.h"

AEnemigoSubterraneo::AEnemigoSubterraneo()
{
    // Carga el material
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("Material'/Game/StarterContent/Shapes/Ediciones/ColorEnemigoSubterraneo.ColorEnemigoSubterraneo'"));
    Material = MaterialFinder.Object;
}

void AEnemigoSubterraneo::BeginPlay()
{
    Super::BeginPlay();

    // Asigna el material al mesh
    if (StaticMesh)
    {
        StaticMesh->SetMaterial(0, Material);
    }
}
