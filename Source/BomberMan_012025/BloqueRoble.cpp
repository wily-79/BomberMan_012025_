// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueRoble.h"

ABloqueRoble::ABloqueRoble()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));
        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
        }
    }
}

//void ABloqueLadrillo::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

void ABloqueRoble::BeginPlay()
{
    Super::BeginPlay();

}