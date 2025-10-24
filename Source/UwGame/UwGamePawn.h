#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UwGamePawn.generated.h"

UCLASS()
class AUwGamePawn : public APawn
{
    GENERATED_BODY()

protected:

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
};
