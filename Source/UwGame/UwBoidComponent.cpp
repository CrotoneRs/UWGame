#include "UwBoidComponent.h"
#include "UwBoidSystem.h"

UUwBoidComponent::UUwBoidComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUwBoidComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UUwBoidSubsystem* BoidSystem = GetWorld()->GetSubsystem<UUwBoidSubsystem>())
	{
		BoidSystem->RegisterBoid(this);
	}
}

void UUwBoidComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UUwBoidSubsystem* BoidSystem = GetWorld()->GetSubsystem<UUwBoidSubsystem>())
	{
		BoidSystem->UnRegisterBoid(this);
	}

	Super::EndPlay(EndPlayReason);
}

