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

    UPROPERTY(ReplicatedUsing = OnTimeRemainingCallback, BlueprintReadOnly, Category = "Game State")
    float RemainingTime;

    UFUNCTION()
    void OnTimeRemainingCallback();

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
