// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueAcero.h"

ABloqueAcero::ABloqueAcero()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel'"));
        
            if (MaterialBase.Succeeded())
            {
                MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
            }
    }
}

void ABloqueAcero::BeginPlay()
{
}
