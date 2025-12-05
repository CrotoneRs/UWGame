#include "UwGamePawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AUwGamePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUwGamePawn::Move);
        EnhancedInputComponent->BindAction(CameraAction, ETriggerEvent::Triggered, this, &AUwGamePawn::Camera);
    }
    else
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &AUwGamePawn::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &AUwGamePawn::MoveRight);
    }
}

void AUwGamePawn::MoveForward(float Value)
{
    if (AController* PawnController = GetController())
    {
        const FRotator Rotation = PawnController->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);

        const FVector ForwarVector = RotationMatrix.GetUnitAxis(EAxis::X);

        AddActorWorldOffset(/* DeltaSeconds */ Value * ForwarVector);
    }
}

void AUwGamePawn::MoveRight(float Value)
{
    if (AController* PawnController = GetController())
    {
        const FRotator Rotation = PawnController->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);

        const FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);

        AddActorWorldOffset(/* DeltaSeconds */ Value * RightVector);
    }
}

void AUwGamePawn::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (AController* PawnController = GetController())
    {
        const FRotator Rotation = PawnController->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);

        const FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
        const FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardVector, MovementVector.X);
        AddMovementInput(RightVector, MovementVector.Y);
    }
}

void AUwGamePawn::Camera(const struct FInputActionValue& Value)
{
    FVector2D CameraVector = Value.Get<FVector2D>();

    if (AController* PawnController = GetController())
    {
        AddControllerYawInput(CameraVector.X);
        AddControllerPitchInput(CameraVector.Y);
    }
}
