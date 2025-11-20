#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UwBoidSystem.generated.h"

class UUwBoidComponent;

UCLASS()
class UWGAME_API UUwBoidSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:

    UUwBoidSubsystem();

    void RegisterBoid(UUwBoidComponent* BoidComponent);
    void UnRegisterBoid(UUwBoidComponent* BoidComponent);

    virtual void Tick(float DeltaTime) override;

    virtual bool IsTickable() const override { return true; }

    virtual TStatId GetStatId() const override
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(UBoidSubsystem, STATGROUP_Tickables);
    }

private:

    FVector ApplyAlignment(uint32 BoidID);
    FVector ApplyCohesion(uint32 BoidID);
    FVector ApplySeparation(uint32 BoidID);

private:

    float GroupRadius;

    float AlignmentWeight;
    float CohesionWeight;
    float SeparationWeight;

    UPROPERTY()
    TArray<UUwBoidComponent*> CurrentBoids;
};
