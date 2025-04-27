// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberMan_012025GameMode.h"
#include "BomberMan_012025Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Bloque.h"
#include "BloqueBurbuja.h"
#include "BloqueAcero.h"
#include "BloqueConcreto.h"
#include "BloqueLadrillo.h"
#include "BloqueMadera.h"
#include "BloquePasto.h"
#include "BloqueArena.h"
#include "BloqueGrava.h"
#include "BloqueCobre.h"
#include "BloqueRoble.h"
#include "BloqueOro.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.h"
#include "EnemigoAcuatico.h"
#include "EnemigoAereo.h"
#include "EnemigoSubterraneo.h"
#include "Kismet/GameplayStatics.h"

ABomberMan_012025GameMode::ABomberMan_012025GameMode()
{
    int32 IndiceBloqueMadera = 0;
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

}

void ABomberMan_012025GameMode::BeginPlay()
{
    Super::BeginPlay();
    //int valor2;

    // Recorremos la matriz para generar los bloques
    // Recorremos la matriz para generar los bloques
    for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
    {
        for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
        {
            int32 valor = aMapaBloques[fila][columna];
            // Calculamos la posiciÛn del bloque
            FVector posicionBloque = FVector(
                XInicial + columna * AnchoBloque,
                YInicial + fila * LargoBloque,
                20.0f); // Z queda en 0 (altura del bloque)
            // Llamamos a la funcion para generar un bloque
            SpawnBloque(posicionBloque, valor);
          

			//Se genera solo el 20% de los bloques
            /*
            if (columna == 0 || columna == 49 || fila == 0 || fila == 49) {
               
            }
            else if (FMath::RandRange(0, 10) < 2) {
                valor2 = FMath::RandRange(1, 10);
                SpawnBloque(posicionBloque, valor2);
            }*/
            
        }
    }
    


    if (aposicionesLibresMadera.Num() > 0) {
        FVector posicionMasCercana;
        float distanciaMinima = FLT_MAX;
        TArray<FVector> bloquesCandidatos; // Guardar bloques elegibles

        // Parámetro para alternar entre centro y borde
        bool bSpawnCercaDelCentro = true; // Cambia a 'false' para *spawnear* cerca de los bordes

        if (bSpawnCercaDelCentro) {
            // *** Lógica para aparecer cerca del centro ***
            FVector centroMapa = FVector(
                XInicial + (aMapaBloques[0].Num() * AnchoBloque) / 2.0f, // Coordenada X del centro
                YInicial + (aMapaBloques.Num() * LargoBloque) / 2.0f,     // Coordenada Y del centro
                20.0f                                                    // Coordenada Z base
            );

            float radioMaximo = 500.0f; // Ajusta el radio alrededor del centro

            for (const FVector& posicion : aposicionesLibresMadera) {
                float distanciaActual = FVector::Dist(centroMapa, posicion);

                if (distanciaActual <= radioMaximo) {
                    bloquesCandidatos.Add(posicion); // Agregar posiciones dentro del radio
                }
            }
        }
        else {
            // *** Lógica para aparecer cerca del borde ***
            for (const FVector& posicion : aposicionesLibresMadera) {
                // Calcular las distancias a los bordes del mapa
                float distanciaSuperior = FMath::Abs(posicion.Y - YInicial);
                float distanciaInferior = FMath::Abs(posicion.Y - (YInicial + (aMapaBloques.Num() * LargoBloque)));
                float distanciaIzquierda = FMath::Abs(posicion.X - XInicial);
                float distanciaDerecha = FMath::Abs(posicion.X - (XInicial + (aMapaBloques[0].Num() * AnchoBloque)));

                // Calcular la distancia mínima a cualquier borde
                float distanciaActual = FMath::Min(
                    FMath::Min(distanciaSuperior, distanciaInferior),
                    FMath::Min(distanciaIzquierda, distanciaDerecha)
                );

                // Verificar si esta distancia es menor o igual al mínimo
                if (distanciaActual <= distanciaMinima) {
                    distanciaMinima = distanciaActual;
                    bloquesCandidatos.Add(posicion); // Agregar bloques cercanos al borde
                }
            }
        }

        // Seleccionar un bloque aleatorio de los candidatos
        if (bloquesCandidatos.Num() > 0) {
            int indiceAleatorio = FMath::RandRange(0, bloquesCandidatos.Num() - 1);
            posicionMasCercana = bloquesCandidatos[indiceAleatorio];
        }

        // Ajustar la posición para que el personaje esté encima del bloque de madera
        posicionMasCercana.Z += 400.0f;

        // Obtener al personaje
        APawn* personaje = UGameplayStatics::GetPlayerPawn(this, 0);
        if (personaje) {
            // Teletransportar al personaje a la posición calculada
            personaje->SetActorLocation(posicionMasCercana);
        }
    }

    AsignarMovimientosAleatorios();

    // Iniciar el timer para desaparecer los bloques
    //GetWorldTimerManager().SetTimer(MaderaTimerHandle, this, &ABomberMan_012025GameMode::DesaparecerBloquesMadera, 5.0f, true, 10.0f);

}


// Funcion para generar un bloque
void ABomberMan_012025GameMode::SpawnBloque(FVector posicionBloque, int32 tipoBloque)
{
    ABloque* BloqueGenerado = nullptr;

    // Elegir tipo de bloque basado en el valor
    if (tipoBloque == 10)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueOro>(ABloqueOro::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 9)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueRoble>(ABloqueRoble::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 8)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueCobre>(ABloqueCobre::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 7)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueGrava>(ABloqueGrava::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 6)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueArena>(ABloqueArena::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 5)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloquePasto>(ABloquePasto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 4)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueAcero>(ABloqueAcero::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 3)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueConcreto>(ABloqueConcreto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 2)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueLadrillo>(ABloqueLadrillo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
    }
    else if (tipoBloque == 1)
    {
        BloqueGenerado = GetWorld()->SpawnActor<ABloqueMadera>(ABloqueMadera::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));

        //Almacenar posiciones libres
        aposicionesLibresMadera.Add(posicionBloque);
    }
    else if (tipoBloque == 0)
    {

      

        float probabilidad = FMath::RandRange(0.0f, 1.0f);
        if (probabilidad < 0.1f) // 10% de probabilidad de spawnear
        {
            float probabilidad2 = FMath::RandRange(0.0f, 1.0f);
            if (probabilidad2 < 0.25f)
                GetWorld()->SpawnActor<AEnemigoAereo>(AEnemigoAereo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
            else if (probabilidad2 < 0.5f)
                GetWorld()->SpawnActor<AEnemigoTerrestre>(AEnemigoTerrestre::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
            else if (probabilidad2 < 0.75f)
                GetWorld()->SpawnActor<AEnemigoAcuatico>(AEnemigoAcuatico::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
            else
                GetWorld()->SpawnActor<AEnemigoSubterraneo>(AEnemigoSubterraneo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
        }
    }

    // Agregar el bloque al TArray si fue generado
    if (BloqueGenerado)
    {
        // Ajustar la escala
        FVector EscalaActual = BloqueGenerado->GetActorScale3D();
        EscalaActual.Z *= 2.0f; // Aumenta la altura 2 veces
        BloqueGenerado->SetActorScale3D(EscalaActual);

        // Agregar el bloque al array aBloques
        aBloques.Add(BloqueGenerado);
    }
}


void ABomberMan_012025GameMode::AsignarMovimientosAleatorios()
{

    
    // Arrays para almacenar los diferentes tipos de bloques
    TArray<ABloque*> Ladrillos, Maderas, Aceros, Concretos, Pastos, Arenas, Gravas, Cobres, Robles, Oros;

    // Clasificar los bloques según su tipo
    for (ABloque* Bloque : aBloques)
    {
        if (Bloque->IsA(ABloqueLadrillo::StaticClass())) Ladrillos.Add(Bloque);
        else if (Bloque->IsA(ABloqueMadera::StaticClass())) Maderas.Add(Bloque);
        else if (Bloque->IsA(ABloqueAcero::StaticClass())) Aceros.Add(Bloque);
        else if (Bloque->IsA(ABloqueConcreto::StaticClass())) Concretos.Add(Bloque);
        else if (Bloque->IsA(ABloquePasto::StaticClass())) Pastos.Add(Bloque);
        else if (Bloque->IsA(ABloqueArena::StaticClass())) Arenas.Add(Bloque);
        else if (Bloque->IsA(ABloqueGrava::StaticClass())) Gravas.Add(Bloque);
        else if (Bloque->IsA(ABloqueCobre::StaticClass())) Cobres.Add(Bloque);
        else if (Bloque->IsA(ABloqueRoble::StaticClass())) Robles.Add(Bloque);
        else if (Bloque->IsA(ABloqueOro::StaticClass())) Oros.Add(Bloque);
    }
    /*
    // Asignar movimiento solo en Z a todos los bloques de ladrillo
    for (ABloque* Bloque : Ladrillos)
    {
        Bloque->TipoMovimiento = 2;         // 2 = movimiento en eje Z
        Bloque->DireccionMovimientoX = 0;   // Sin movimiento en X
        Bloque->DireccionMovimientoY = 0;   // Sin movimiento en Y
        Bloque->DireccionMovimientoZ = 1;   // Movimiento hacia arriba en Z
        Bloque->FloatSpeed = 80.0f;         // Velocidad de movimiento
        Bloque->bPuedeMoverse = true;       // Activar movimiento
        Bloque->AlturaMaxima = 200.0f;      // Altura máxima que alcanzarán los bloques (200 unidades)

        // Asegurarnos de guardar la posición Z inicial si no se hizo al spawnear
        if (Bloque->PosicionInicialZ == 0)
        {
            Bloque->PosicionInicialZ = Bloque->GetActorLocation().Z;
        }
    }

    // Desactivar movimiento para todos los demás tipos de bloques
    for (ABloque* Bloque : aBloques)
    {
        if (!Bloque->IsA(ABloqueLadrillo::StaticClass()))
        {
            Bloque->bPuedeMoverse = false;
        }
    }
    */

    // Función para asignar movimiento a 4 bloques aleatorios de un tipo
    auto AsignarMovimiento = [](TArray<ABloque*>& Lista, int Tipo, int DirX, int DirY, int DirZ, float Velocidad = 100.0f)
        {
            if (Lista.Num() >= 4)
            {
                // Mezclar el array para selección aleatoria
                for (int32 i = 0; i < Lista.Num(); i++)
                {
                    int32 j = FMath::RandRange(0, Lista.Num() - 1);
                    if (i != j)
                    {
                        Lista.Swap(i, j);
                    }
                }

                // Seleccionar los primeros 4 bloques después de mezclar
                for (int32 i = 0; i < 4 && i < Lista.Num(); i++)
                {
  

                    ABloque* Bloque = Lista[i];
                    Bloque->TipoMovimiento = Tipo;
                    Bloque->DireccionMovimientoX = DirX;
                    Bloque->DireccionMovimientoY = DirY;
                    Bloque->DireccionMovimientoZ = DirZ;
                    Bloque->FloatSpeed = Velocidad;
                    Bloque->bPuedeMoverse = true;
                }

                // Temporizador para actualizar movimientos cada 10 segundos
                static FTimerHandle TimerHandle; // Static para persistencia entre llamados
                if (GWorld) // Verifica que el mundo esté disponible
                {
                    GWorld->GetTimerManager().SetTimer(
                        TimerHandle,
                        FTimerDelegate::CreateLambda([=]() {
                            for (int32 i = 0; i < 4 && i < Lista.Num(); i++)
                            {
                                ABloque* Bloque = Lista[i];
                                Bloque->TipoMovimiento = FMath::RandRange(0, 2);
                                // Elegir una dirección aleatoria única
                                int Direccion = FMath::RandRange(0, 2); // 0 para X, 1 para Y, 2 para Z
                                Bloque->DireccionMovimientoX = (Direccion == 0) ? FMath::RandRange(-1, 1) : 0; // Solo X si se selecciona 0
                                Bloque->DireccionMovimientoY = (Direccion == 1) ? FMath::RandRange(-1, 1) : 0; // Solo Y si se selecciona 1
                                Bloque->DireccionMovimientoZ = (Direccion == 2) ? FMath::RandRange(-1, 1) : 0; // Solo Z si se selecciona 2


                                Bloque->FloatSpeed = FMath::RandRange(50.0f, 130.0f); // Actualizar velocidad
                                Bloque->bPuedeMoverse = true;
                            }
                            }),
                        10.0f, // Tiempo en segundos
                        true // Repetir el temporizador
                    );
                }


            }
        };



    // Asignar movimientos específicos para cada tipo de bloque
    AsignarMovimiento(Ladrillos,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Maderas,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Aceros,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Concretos,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Pastos,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Arenas,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Gravas,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Cobres,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Robles,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));

    AsignarMovimiento(Oros,
        FMath::RandRange(0, 2),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(-1, 1),
        FMath::RandRange(50.0f, 130.0f));


}

void ABomberMan_012025GameMode::DesaparecerBloquesMadera()
{
    for (int32 i = aBloques.Num() - 1; i >= 0; --i)
    {
        if (aBloques[i]->IsA(ABloqueMadera::StaticClass()))
        {
            aBloques[i]->Destroy();
            aBloques.RemoveAt(i);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bloque de madera destruido"));
            break; // Elimina solo uno por llamada

        }
    }

    // Si ya no hay más bloques de madera, limpiar el timer
    bool bQuedanMaderas = false;
    for (ABloque* Bloque : aBloques)
    {
        if (Bloque->IsA(ABloqueMadera::StaticClass()))
        {
            bQuedanMaderas = true;
            break;
        }
    }

    if (!bQuedanMaderas)
    {
        GetWorldTimerManager().ClearTimer(MaderaTimerHandle);
    }
}