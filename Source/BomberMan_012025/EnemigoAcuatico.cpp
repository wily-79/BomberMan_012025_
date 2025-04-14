// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAcuatico.h"

AEnemigoAcuatico::AEnemigoAcuatico()
{
    // Carga el material
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(TEXT("Material'/Game/StarterContent/Shapes/Ediciones/ColorEnemigoAcuatico.ColorEnemigoAcuatico'"));
    Material = MaterialFinder.Object;
}

void AEnemigoAcuatico::BeginPlay()
{
    Super::BeginPlay();

    // Asigna el material al mesh
    if (StaticMesh)
    {
        StaticMesh->SetMaterial(0, Material);
    }
}
