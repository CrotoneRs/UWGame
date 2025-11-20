#include "UwSheepActor.h"
#include "UwBoidComponent.h"

AUwSheepActor::AUwSheepActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoidComponent = CreateDefaultSubobject<UUwBoidComponent>(TEXT("BoidComponent"));
}
