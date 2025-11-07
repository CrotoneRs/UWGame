#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UwGameMode.generated.h"

UCLASS()
class AUwGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AUwGameMode();

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
};