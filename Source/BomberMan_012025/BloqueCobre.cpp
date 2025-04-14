// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueCobre.h"

ABloqueCobre::ABloqueCobre()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Copper.M_Metal_Copper'"));
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

void ABloqueCobre::BeginPlay()
{
    Super::BeginPlay();

}