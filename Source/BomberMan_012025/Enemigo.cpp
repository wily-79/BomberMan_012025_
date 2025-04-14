// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemigo.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemigo::AEnemigo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
   // Crear el componente de mesh
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(RootComponent); // Lo pegamos al capsule del Character

    // Cargar la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));
    if (MeshAsset.Succeeded())
    {
        StaticMesh->SetStaticMesh(MeshAsset.Object);
        StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); // Posición del mesh
        StaticMesh->SetRelativeRotation(FRotator(0.0f, -31.0f, 0.0f)); // Rotación del mesh
        StaticMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
    }
    
    // Dirección inicial al azar
    ElegirNuevaDireccion();
    
    //
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass(); // o tu clase propia si tenés una

}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
    

}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
    //Dibujar una línea en la dirección actual(debug)
    DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + CurrentDirection * 50.0f, FColor::Red, false, 0.1f);
    //Deteccion de paredes
    if (!CurrentDirection.IsNearlyZero())
    {
        AddMovementInput(CurrentDirection, MoveSpeed);
    }

    // Checar si hay algo adelante con un raycast
    FHitResult Hit;
    FVector Start = GetActorLocation();
    FVector End = Start + CurrentDirection * 75.0f; // Distancia para detectar pared

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    if (bHit)
    {
        ElegirNuevaDireccion(); // Cambia de dirección si choca
    }
}

// Called to bind functionality to input
void AEnemigo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{       
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

// Elegir una nueva dirección
void AEnemigo::ElegirNuevaDireccion()
{
    //Se crea un array con las direcciones adelante,detras,derecha e izquierda
    TArray<FVector> Direcciones;
    Direcciones.Add(FVector::ForwardVector);   // +X
    Direcciones.Add(-FVector::ForwardVector);  // -X
    Direcciones.Add(FVector::RightVector);     // +Y
    Direcciones.Add(-FVector::RightVector);    // -Y
    //
    int32 Index = FMath::RandRange(0, Direcciones.Num() - 1);
    CurrentDirection = Direcciones[Index];
    // Actualizar la rotación
    if (!CurrentDirection.IsNearlyZero())
    {
        FRotator NewRotation = CurrentDirection.Rotation();
        SetActorRotation(NewRotation);
    }
}
