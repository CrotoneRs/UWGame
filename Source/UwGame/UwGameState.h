#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UwGameState.generated.h"

UCLASS()
class AUwGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AUwGameState() { bReplicates = false; }

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Game State")
    float RemainingTime;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
