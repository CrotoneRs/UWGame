#include "UwGamePawn.h"

void AUwGamePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveForward", this, &AUwGamePawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AUwGamePawn::MoveRight);
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
