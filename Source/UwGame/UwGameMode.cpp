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

    UwGameState->RemainingTime;

    // LOGs
}
