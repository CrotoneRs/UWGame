#include "UwGameState.h"
#include "Net/UnrealNetwork.h"

void AUwGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AUwGameState, RemainingTime);
}

void AUwGameState::OnTimeRemainingCallback()
{
    // UE_LOG(...);
}
