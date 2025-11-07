#include "UwBoidSystem.h"
#include "UwBoidComponent.h"

void UUwBoidSubsystem::RegisterBoid(UUwBoidComponent* BoidComponent)
{
    if (!CurrentBoids.Contains(BoidComponent))
    {
        CurrentBoids.Add(BoidComponent);
    }
}

void UUwBoidSubsystem::UnRegisterBoid(UUwBoidComponent* BoidComponent)
{
    CurrentBoids.Remove(BoidComponent);
}

void UUwBoidSubsystem::Tick(float DeltaTime)
{
    // Boid Simulation ..
}
