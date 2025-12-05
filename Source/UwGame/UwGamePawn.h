#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "UwGamePawn.generated.h"

UCLASS()
class AUwGamePawn : public ADefaultPawn
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* CameraAction;

protected:

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);

    void Move(const struct FInputActionValue& Value);
    void Camera(const struct FInputActionValue& Value);
};
