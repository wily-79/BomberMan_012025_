// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueGrava.h"

ABloqueGrava::ABloqueGrava()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Ground_Gravel.M_Ground_Gravel'"));
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

void ABloqueGrava::BeginPlay()
{
    Super::BeginPlay();

}