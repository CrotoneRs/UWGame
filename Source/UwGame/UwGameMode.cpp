#include "UwGameMode.h"
#include "UwGameState.h"
#include "UwGamePawn.h"
#include "UObject/ConstructorHelpers.h"

AUwGameMode::AUwGameMode()
{
    DefaultPawnClass = AUwGamePawn::StaticClass();
    GameStateClass = AUwGameState::StaticClass();

    //static ConstructorHelpers::FClassFinder<AHUD> HUDClassBP(TEXT("/Game/Game/BP_UwHUD"));
    //if (HUDClassBP.Class != nullptr) { HUDClass = HUDClassBP.Class; }
}

void AUwGameMode::BeginPlay()
{
    Super::BeginPlay();

    AUwGameState* UwGameState = GetGameState<AUwGameState>();

    if (UwGameState)
    {
        UwGameState->RemainingTime = 60.0f;
    }

    // LOGs
}

void AUwGameMode::Tick(float DeltaTime)
{
    AUwGameState* UwGameState = GetGameState<AUwGameState>();

    if (UwGameState)
    {
        if (UwGameState->RemainingTime > 0.0f)
        {
            UwGameState->RemainingTime -= DeltaTime;

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Yellow, "Remaining Time Update.");
            }

            if (UwGameState->RemainingTime <= 0.0f)
            {
                //UE_LOG(LogTemp, Info, TEXT("RemainingTime: %f"), UwGameState->RemainingTime);

                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, "Remaining Time Finished.");
                }
            }
        }
    }
}
