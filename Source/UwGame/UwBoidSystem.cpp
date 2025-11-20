#include "UwBoidSystem.h"
#include "UwBoidComponent.h"

UUwBoidSubsystem::UUwBoidSubsystem()
{
    GroupRadius = 300.0f;

    AlignmentWeight = 1.2f;
    CohesionWeight = 1.2f;
    SeparationWeight = 1.0f;
}

void UUwBoidSubsystem::RegisterBoid(UUwBoidComponent* BoidComponent)
{
    if (BoidComponent && !CurrentBoids.Contains(BoidComponent))
    {
        CurrentBoids.Add(BoidComponent);

        BoidComponent->Position = BoidComponent->GetOwner()->GetActorLocation();
        BoidComponent->Velocity = FVector(FMath::RandRange(-100.0f, 100.f),
            FMath::RandRange(-100.0f, 100.f), 0.0f);
    }
}

void UUwBoidSubsystem::UnRegisterBoid(UUwBoidComponent* BoidComponent)
{
    if (BoidComponent && CurrentBoids.Contains(BoidComponent))
    {
        CurrentBoids.Remove(BoidComponent);
    }
}

void UUwBoidSubsystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (int32 Index = 0; Index < CurrentBoids.Num(); Index++)
    {
        UUwBoidComponent* CurrentBoid = CurrentBoids[Index];

        FVector AlignmentForce = ApplyAlignment(Index);
        FVector CohesionForce = ApplyCohesion(Index);
        FVector SeparationForce = ApplySeparation(Index);

        FVector AccelerationVector = AlignmentForce + CohesionForce + SeparationForce;

        CurrentBoid->Velocity += AccelerationVector * DeltaTime;
        CurrentBoid->Position += CurrentBoid->Velocity * DeltaTime;
    }

    for (int32 Index = 0; Index < CurrentBoids.Num(); Index++)
    {
        const UUwBoidComponent* CurrentBoid = CurrentBoids[Index];
        AActor* OwnerActor = CurrentBoid->GetOwner();

        OwnerActor->SetActorLocation(CurrentBoid->Position);
        OwnerActor->SetActorRotation(CurrentBoid->Velocity.Rotation());
    }
}

FVector UUwBoidSubsystem::ApplyAlignment(uint32 BoidID)
{
    FVector AverageVelocity = FVector::ZeroVector; int32 GroupCount = 0;

    const UUwBoidComponent* CurrentBoid = CurrentBoids[BoidID];

    for (int32 Index = 0; Index < CurrentBoids.Num(); Index++)
    {
        if (Index != BoidID)
        {
            const UUwBoidComponent* OtherBoid = CurrentBoids[Index];

            float Distance = FVector::Distance(CurrentBoid->Position, OtherBoid->Position);

            if (Distance < GroupRadius)
            {
                AverageVelocity += OtherBoid->Velocity; GroupCount++;
            }
        }
    }

    if (GroupCount > 0)
    {
        AverageVelocity /= GroupCount;

        return AverageVelocity - CurrentBoid->Velocity;
    }

    return FVector::ZeroVector;
}

FVector UUwBoidSubsystem::ApplyCohesion(uint32 BoidID)
{
    FVector CenterOfMass = FVector::ZeroVector; int32 GroupCount = 0;

    const UUwBoidComponent* CurrentBoid = CurrentBoids[BoidID];

    for (int32 Index = 0; Index < CurrentBoids.Num(); Index++)
    {
        if (Index != BoidID)
        {
            const UUwBoidComponent* OtherBoid = CurrentBoids[Index];

            float Distance = FVector::Distance(CurrentBoid->Position, OtherBoid->Position);

            if (Distance < GroupRadius)
            {
                CenterOfMass += OtherBoid->Position; GroupCount++;
            }
        }
    }

    if (GroupCount > 0)
    {
        CenterOfMass /= GroupCount;

        return (CenterOfMass - CurrentBoid->Position) - CurrentBoid->Velocity;
    }

    return FVector::ZeroVector;
}

FVector UUwBoidSubsystem::ApplySeparation(uint32 BoidID)
{
    FVector SeparationVelocity = FVector::ZeroVector; int32 GroupCount = 0;

    const UUwBoidComponent* CurrentBoid = CurrentBoids[BoidID];
     
    for (int32 Index = 0; Index < CurrentBoids.Num(); Index++)
    {
        if (Index != BoidID)
        {
            const UUwBoidComponent* OtherBoid = CurrentBoids[Index];

            float Distance = FVector::Distance(CurrentBoid->Position, OtherBoid->Position);

            if (Distance < GroupRadius)
            {
                FVector RepulsionDirection = CurrentBoid->Position - OtherBoid->Position;
                RepulsionDirection *= (GroupRadius / FMath::Max(Distance, 1.0f));

                SeparationVelocity += RepulsionDirection;

                GroupCount++;
            }
        }
    }

    if (GroupCount > 0)
    {
        SeparationVelocity /= GroupCount;

        return SeparationVelocity - CurrentBoid->Velocity;
    }

    return FVector::ZeroVector;
}
